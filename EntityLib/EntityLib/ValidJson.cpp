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
#include "include/EntityLibCore.h"
#include "include/Schema.h"

/// \cond PRIVATE

using namespace nlohmann;

// Since the prototype of fetchDocument is fixed by valijson and is a C function,
// schemaPath can only be static
static thread_local char schemaPath[1024] = {};

static std::string filterError(char const* message)
{
    // Remove messages to say that all other components doesn't match
    std::regex r(R"regex(Failed to validate against schema associated with property name \'Type\'\.
In node \: \<root\>(\/\[Objects\]\/\[\d+\]|)\/\[Components\]\/\[\d+\]

Failed to validate against child schema #\d+.
In node : \<root\>(\/\[Objects\]\/\[\d+\]|)\/\[Components\]\/\[\d+\]

Failed to match expected value set by \'const\' constraint\.
In node : \<root\>(\/\[Objects\]\/\[\d+\]|)\/\[Components\]\/\[\d+\]\/\[Type\]

)regex");
    std::string const message2 = std::regex_replace(message, r, "");
    std::regex r2(R"regex(Failed to validate against schema associated with property name \'Type\'\.
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
    std::replace(begin(link), end(link), '#', '_');
    std::replace(begin(link), end(link), '/', '_');
    std::replace(begin(link), end(link), ':', '_');
    std::replace(begin(link), end(link), '.', '_');
    std::replace(begin(link), end(link), '-', '_');
    return link;
}

static json
convertToInstanceSchema(Ent::Subschema const& tmplSchema, char const* oneOfDataField = nullptr);

static json
convertToInstanceSchema(Ent::SubschemaRef const& tmplSchemaRef, char const* oneOfDataField = nullptr)
{
    if (tmplSchemaRef.subSchemaOrRef.is<Ent::SubschemaRef::Ref>())
    {
        json instSchema;
        std::string link = tmplSchemaRef.subSchemaOrRef.get<Ent::SubschemaRef::Ref>().ref;
        instSchema.emplace("$ref", "#/definitions/" + convertLink(link));
        return instSchema;
    }
    return convertToInstanceSchema(*tmplSchemaRef, oneOfDataField);
}

static json convertToInstanceSchema(Ent::Subschema const& tmplSchema, char const* oneOfDataField)
{
    json instSchema;
    instSchema["default"] = tmplSchema.defaultValue;
    if (tmplSchema.constValue.has_value())
    {
        instSchema["const"] = *tmplSchema.constValue;
    }
    if (not empty(tmplSchema.enumValues))
    {
        instSchema["enum"] = tmplSchema.enumValues;
    }
    if (tmplSchema.maxItems != size_t(-1))
    {
        instSchema["maxItems"] = tmplSchema.maxItems;
    }
    if (tmplSchema.minItems != 0)
    {
        instSchema["minItems"] = tmplSchema.minItems;
    }

    json nullType;
    nullType["type"] = "null";

    std::array<char const*, static_cast<size_t>(Ent::DataType::COUNT)> typeToStr = {
        "null", "string", "number", "integer", "object", "array", "boolean", "string", "object"};
    instSchema["type"] = typeToStr[size_t(tmplSchema.type)];
    std::vector<char const*> requiredList;
    for (auto&& name_prop : tmplSchema.properties)
    {
        if (oneOfDataField != nullptr and oneOfDataField == name_prop.first)
        {
            json oneOf;
            oneOf.push_back(convertToInstanceSchema(name_prop.second));
            oneOf.push_back(nullType);
            json items;
            items.emplace("oneOf", oneOf);
            instSchema["properties"][name_prop.first] = items;
        }
        else
            instSchema["properties"][name_prop.first] = convertToInstanceSchema(name_prop.second);
        if (name_prop.second->required)
        {
            requiredList.push_back(name_prop.first.c_str());
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
        for (auto&& prop : *tmplSchema.oneOf)
        {
            instSchema["oneOf"].push_back(
                convertToInstanceSchema(prop, tmplSchema.getUnionDataField()));
        }
    }
    if (not empty(requiredList))
    {
        instSchema["required"] = requiredList;
    }
    return instSchema;
}

static json convertToInstanceSchema(Ent::Schema const& schema, Ent::Subschema const& root)
{
    json instSchema = convertToInstanceSchema(root);
    for (auto&& name_def : schema.allDefinitions)
    {
        auto const link = convertLink(name_def.first);
        instSchema["definitions"][link] = convertToInstanceSchema(name_def.second);
    }
    return instSchema;
}

static json const* fetchDocument(const std::string& uri)
{
    std::unique_ptr<json> fetchedRoot = std::make_unique<json>();
    char buff[1024] = {};
    sprintf_s(
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

static char const* sceneSchemaPath = "WildPipeline/Schema/Scene-schema.json";
static char const* entitySchemaPath = "WildPipeline/Schema/Entity-schema.json";

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

void Ent::validateScene(
    Schema const& _schema, std::filesystem::path const& _toolsDir, nlohmann::json const& _scene)
{
    // valid the scene using schema
    strcpy_s(schemaPath, sizeof(schemaPath), (_toolsDir / "WildPipeline/Schema").u8string().c_str());

    json schemaDocument = loadJsonFile(_toolsDir / sceneSchemaPath);

    json fullEntityInstanceSchema = convertToInstanceSchema(_schema, *_schema.root);

    // Parse the json schema into an internal schema format
    valijson::Schema vjSchema;
    valijson::SchemaParser parser;
    parser.populateSchema(
        valijson::adapters::NlohmannJsonAdapter(fullEntityInstanceSchema),
        vjSchema,
        fetchDocument,
        freeDocument);

    valijson::Validator validator;
    valijson::adapters::NlohmannJsonAdapter myTargetAdapter(_scene);
    valijson::ValidationResults result;
    if (!validator.validate(vjSchema, myTargetAdapter, &result))
    {
        /// @todo un-comment soon
        std::string message = createMessageFromValidationResult(result);
        throw Ent::JsonValidation(filterError(message.c_str()));
    }
}

void Ent::validateEntity(
    Schema const& _schema, std::filesystem::path const& _toolsDir, nlohmann::json const& _entity)
{
    // valid the scene using schema
    strcpy_s(schemaPath, sizeof(schemaPath), (_toolsDir / "WildPipeline/Schema").u8string().c_str());

    json schemaDocument = loadJsonFile(_toolsDir / entitySchemaPath);

    json fullSceneInstanceSchema = convertToInstanceSchema(
        _schema, AT(_schema.allDefinitions, "./Scene-schema.json#/definitions/Object"));

    // Parse the json schema into an internal schema format
    valijson::Schema vjSchema;
    valijson::SchemaParser parser;
    parser.populateSchema(
        valijson::adapters::NlohmannJsonAdapter(fullSceneInstanceSchema),
        vjSchema,
        fetchDocument,
        freeDocument);

    valijson::Validator validator;
    valijson::adapters::NlohmannJsonAdapter myTargetAdapter(_entity);
    valijson::ValidationResults result;
    if (!validator.validate(vjSchema, myTargetAdapter, &result))
    {
        /// @todo un-comment soon
        std::string message = createMessageFromValidationResult(result);
        throw Ent::JsonValidation(filterError(message.c_str()));
    }
}

/// \endcond
