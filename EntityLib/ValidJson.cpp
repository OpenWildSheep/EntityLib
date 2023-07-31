#include "ValidJson.h"

#pragma warning(push, 0)
#pragma warning(disable : 4702)
#include <valijson/adapters/nlohmann_json_adapter.hpp>
#include <valijson/utils/nlohmann_json_utils.hpp>
#include <valijson/schema.hpp>
#include <valijson/schema_parser.hpp>
#include <valijson/validator.hpp>
#include <regex>
#include <ciso646>
#pragma warning(pop)

#include "Tools.h"
#include "include/EntityLib/EntityLibCore.h"
#include "include/EntityLib/Schema.h"

/// \cond PRIVATE

using namespace nlohmann;

namespace Ent
{

    // Since the prototype of fetchDocument is fixed by valijson and is a C function,
    // schemaPath can only be static
    static thread_local char schemaPath[1024] = {};

    static std::string filterError(char const* message)
    {
        // Remove messages to say that all other components doesn't match
        std::regex const r(
            R"regex(Failed to validate against schema associated with property name \'Type\'\.
In node \: \<root\>(\/\[Objects\]\/\[\d+\]|)\/\[Components\]\/\[\d+\]

Failed to validate against child schema #\d+.
In node : \<root\>(\/\[Objects\]\/\[\d+\]|)\/\[Components\]\/\[\d+\]

Failed to match expected value set by \'const\' constraint\.
In node : \<root\>(\/\[Objects\]\/\[\d+\]|)\/\[Components\]\/\[\d+\]\/\[Type\]

)regex");
        std::string const message2 = std::regex_replace(message, r, "");
        std::regex const r2(
            R"regex(Failed to validate against schema associated with property name \'Type\'\.
In node \: \<root\>(\/\[Objects\]\/\[\d+\]|\/\[Components\]\/\[\d+\]\/\[Data\]\/\[Embedded\]\/\[\d+\]|)\/\[Components\]\/\[\d+\]

Failed to validate against child schema #\d+.
In node \: \<root\>(\/\[Objects\]\/\[\d+\]|\/\[Components\]\/\[\d+\]\/\[Data\]\/\[Embedded\]\/\[\d+\]|)\/\[Components\]\/\[\d+\]

Failed to match expected value set by \'const\' constraint\.
In node \: \<root\>(\/\[Objects\]\/\[\d+\]|\/\[Components\]\/\[\d+\]\/\[Data\]\/\[Embedded\]\/\[\d+\]|)\/\[Components\]\/\[\d+\]\/\[Type\]

)regex");
        return std::regex_replace(message2, r2, "");
    }

    static std::string convertLink(std::string link)
    {
        if (auto const slash = link.find_last_of('/'); slash != std::string::npos)
        {
            link = link.substr(slash + 1);
        }
        return link;
    }

    static json
    convertToInstanceSchema(Subschema const& tmplSchema, char const* oneOfDataField = nullptr);

    static json
    convertToInstanceSchema(SubschemaRef const& tmplSchemaRef, char const* oneOfDataField = nullptr)
    {
        if (std::holds_alternative<SubschemaRef::Ref>(tmplSchemaRef.subSchemaOrRef))
        {
            json instSchema;
            auto&& ref = std::get<SubschemaRef::Ref>(tmplSchemaRef.subSchemaOrRef);
            instSchema.emplace("$ref", "#/definitions/" + convertLink(ref.ref));
            // Some fields are reference to other types ($ref)
            // but they are allowed to contains a title and a description
            // which override the linked type values.
            if (not ref.title.empty())
            {
                instSchema["title"] = ref.title;
            }
            if (not ref.description.empty())
            {
                instSchema["description"] = ref.description;
            }
            return instSchema;
        }
        return convertToInstanceSchema(*tmplSchemaRef, oneOfDataField);
    }

    static json convertToInstanceSchema(Subschema const& tmplSchema, char const* oneOfDataField)
    {
        json instSchema;
        if (not tmplSchema.defaultValue.is_null())
        {
            instSchema["default"] = tmplSchema.defaultValue;
        }
        if (tmplSchema.constValue.has_value())
        {
            instSchema["const"] = *tmplSchema.constValue;
        }
        if (not empty(tmplSchema.enumValues))
        {
            instSchema["enum"] = tmplSchema.enumValues;
        }
        if (tmplSchema.maxItems != static_cast<size_t>(-1))
        {
            instSchema["maxItems"] = tmplSchema.maxItems;
        }
        if (tmplSchema.minItems != 0)
        {
            instSchema["minItems"] = tmplSchema.minItems;
        }

        json nullType;
        nullType["type"] = "null";

        std::array<char const*, static_cast<size_t>(DataKind::COUNT)> typeToStr = {
            "string",
            "number",
            "integer",
            "object",
            "array",
            "boolean",
            "string",
            "object",
            "array",
            "array",
            "array",
            "array"};
        instSchema["type"] = typeToStr[static_cast<size_t>(tmplSchema.getDataKind())];
        std::vector<char const*> requiredList;
        for (auto&& [name, prop] : tmplSchema.properties)
        {
            if (oneOfDataField != nullptr and oneOfDataField == name)
            {
                // Allow Data field in OneOf to be "null"
                json oneOf;
                oneOf.push_back(convertToInstanceSchema(prop));
                oneOf.push_back(nullType);
                json items;
                items.emplace("oneOf", oneOf);
                instSchema["properties"][name] = items;
            }
            else
            {
                instSchema["properties"][name] = convertToInstanceSchema(prop);
                // Add property default values in the right place
                if (prop.getRefDefaultValues() != nullptr
                    and not prop.getRefDefaultValues()->is_null())
                {
                    instSchema["default"][name] = *prop.getRefDefaultValues();
                }
            }
            if (prop->required)
            {
                requiredList.push_back(name.c_str());
            }
        }
        if (tmplSchema.singularItems != nullptr)
        {
            json oneOf;
            oneOf.push_back(convertToInstanceSchema(*tmplSchema.singularItems));
            oneOf.push_back(nullType);
            json items;
            items.emplace("oneOf", oneOf);
            instSchema.emplace("items", items);
        }
        else if (tmplSchema.linearItems.has_value())
        {
            for (auto&& prop : *tmplSchema.linearItems)
            {
                json item;
                item["oneOf"].push_back(convertToInstanceSchema(prop));
                item["oneOf"].push_back(nullType);
                instSchema["items"].push_back(item);
            }
        }
        if (tmplSchema.oneOf.has_value())
        {
            // In Union, write nothing, or at least a NameField
            for (auto&& prop : *tmplSchema.oneOf)
            {
                instSchema["oneOf"].push_back(
                    convertToInstanceSchema(prop, tmplSchema.getUnionDataField()));
                instSchema["oneOf"].back()["required"] = {tmplSchema.getUnionNameField()};
                // If there is a DataField, the NameField is mandatory
                // because the validator need the NameField to validate the DataField
            }
            // Allow to write empty object for Union
            json emptyObject;
            emptyObject["type"] = "object";
            emptyObject["properties"][tmplSchema.getUnionNameField()] = false;
            emptyObject["properties"][tmplSchema.getUnionDataField()] = false;
            instSchema["oneOf"].push_back(emptyObject);
        }
        if (not empty(requiredList))
        {
            instSchema["required"] = requiredList;
        }
        if (instSchema.count("properties") != 0)
        {
            instSchema["properties"]["$schema"]["type"] = "string";
            instSchema["properties"]["InstanceOf"]["type"] = "string";
            instSchema["properties"]["__removed__"]["type"] = "boolean";
        }
        if (tmplSchema.getDataKind() == DataKind::object
            or tmplSchema.getDataKind() == DataKind::union_)
        {
            instSchema["additionalProperties"] = false;
        }
        if (not tmplSchema.title.empty())
        {
            instSchema["title"] = tmplSchema.title;
        }
        if (not tmplSchema.description.empty())
        {
            instSchema["description"] = tmplSchema.description;
        }
        return instSchema;
    }

    json createValidationSchema(Schema const& schema)
    {
        json instSchema;
        for (auto&& [name, def] : schema.allDefinitions)
        {
            auto const link = convertLink(name);
            instSchema["definitions"][link] = convertToInstanceSchema(def);
        }
        return instSchema;
    }

    static json const* fetchDocument(std::string const& uri)
    {
        auto fetchedRoot = std::make_unique<json>();
        char buff[1024] = {};
        snprintf(
            buff,
            std::size(buff),
            "%s/%s",
            schemaPath,
            uri.find("./") == 0 ? uri.c_str() + strlen("./") : uri.c_str());
        if (!valijson::utils::loadDocument(buff, *fetchedRoot))
        {
            return nullptr;
        }

        return fetchedRoot.release();
    }

    static void freeDocument(json const* adapter)
    {
        delete adapter; // NOLINT
    }

    static std::string createMessageFromValidationResult(valijson::ValidationResults const& _result)
    {
        std::string fullMessage;
        for (valijson::ValidationResults::Error const& err : _result)
        {
            fullMessage += err.description + "\n";
            fullMessage += "In node : ";
            for (std::string const& line : err.context)
            {
                fullMessage += line + '/';
            }
            fullMessage.pop_back();
            fullMessage += "\n\n";
        }
        return fullMessage;
    }

    void validateScene(Schema const& _schema, std::filesystem::path const& _toolsDir, json const& _scene)
    {
        validateJson(_schema, _toolsDir, _scene, "Scene");
    }

    void validateEntity(Schema const& _schema, std::filesystem::path const& _toolsDir, json const& _entity)
    {
        validateJson(_schema, _toolsDir, _entity, "Entity");
    }

    void validateJson(
        Schema const& _schema,
        std::filesystem::path const& _toolsDir,
        json const& _entity,
        char const* rootName)
    {
        // valid the scene using schema
        strncpy(
            schemaPath, (_toolsDir / "WildPipeline/Schema").u8string().c_str(), sizeof(schemaPath));

        json fullSceneInstanceSchema = createValidationSchema(_schema);
        fullSceneInstanceSchema["$ref"] = std::string("#/definitions/") + rootName;

        // Parse the json schema into an internal schema format
        valijson::Schema vjSchema;
        valijson::SchemaParser parser;
        parser.populateSchema(
            valijson::adapters::NlohmannJsonAdapter(fullSceneInstanceSchema),
            vjSchema,
            fetchDocument,
            freeDocument);

        valijson::Validator validator;
        valijson::adapters::NlohmannJsonAdapter const myTargetAdapter(_entity);
        valijson::ValidationResults result;
        if (!validator.validate(vjSchema, myTargetAdapter, &result))
        {
            /// @todo un-comment soon
            std::string const message = createMessageFromValidationResult(result);
            throw JsonValidation(filterError(message.c_str()));
        }
    }

} // namespace Ent
/// \endcond
