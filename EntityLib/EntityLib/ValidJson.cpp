#include "ValidJson.h"

#pragma warning(push, 0)
#pragma warning(disable : 4702)
#include <valijson/adapters/nlohmann_json_adapter.hpp>
#include <valijson/utils/nlohmann_json_utils.hpp>
#include <valijson/schema.hpp>
#include <valijson/schema_parser.hpp>
#include <valijson/validator.hpp>
#include <regex>
#pragma warning(pop)

#include "Tools.h"
#include "include/EntityLibCore.h"
#include "include/Schema.h"

/// \cond PRIVATE

using namespace nlohmann;

static char schemaPath[1024] = {};

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

struct SetDefault
{
    char const* fieldName;
    json* instSchema;
    template <typename T>
    void operator()(T const& val, std::enable_if_t<std::is_arithmetic<T>::value>* = nullptr) const
    {
        instSchema->emplace(fieldName, val);
    }

    void operator()(std::string const& val) const
    {
        instSchema->emplace(fieldName, val);
    }

    template <typename T>
    void operator()(T const&, std::enable_if_t<not std::is_arithmetic<T>::value>* = nullptr) const
    {
    }
};

static std::string convertLink(std::string link)
{
    std::replace(begin(link), end(link), '#', '_');
    std::replace(begin(link), end(link), '/', '_');
    std::replace(begin(link), end(link), ':', '_');
    std::replace(begin(link), end(link), '.', '_');
    std::replace(begin(link), end(link), '-', '_');
    return link;
}

static json convertToInstanceSchema(Ent::Subschema const& tmplSchema);

static json convertToInstanceSchema(Ent::SubschemaRef const& tmplSchemaRef)
{
    if (tmplSchemaRef.subSchemaOrRef.is<Ent::SubschemaRef::Ref>())
    {
        json instSchema;
        std::string link = tmplSchemaRef.subSchemaOrRef.get<Ent::SubschemaRef::Ref>().ref;
        instSchema.emplace("$ref", "#/definitions/" + convertLink(link));
        return instSchema;
    }
    return convertToInstanceSchema(*tmplSchemaRef);
}

static json convertToInstanceSchema(Ent::Subschema const& tmplSchema)
{
    json instSchema;
    mapbox::util::apply_visitor(SetDefault{ "default", &instSchema }, tmplSchema.defaultValue);
    if (tmplSchema.constValue.has_value())
    {
        mapbox::util::apply_visitor(SetDefault{ "const", &instSchema }, *tmplSchema.constValue);
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

    std::array<char const*, static_cast<size_t>(Ent::DataType::COUNT)> typeToStr = {
        "null", "string", "number", "integer", "object", "array", "boolean", "string"
    };
    instSchema["type"] = typeToStr[size_t(tmplSchema.type)];
    std::vector<char const*> requiredList;
    for (auto&& name_prop : tmplSchema.properties)
    {
        instSchema["properties"][name_prop.first] = convertToInstanceSchema(name_prop.second);
        if (name_prop.second->required)
        {
            requiredList.push_back(name_prop.first.c_str());
        }
    }
    json nullType;
    nullType["type"] = "null";
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
            instSchema["oneOf"].push_back(convertToInstanceSchema(prop));
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
        instSchema["definitions"][convertLink(name_def.first)] =
            convertToInstanceSchema(name_def.second);
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
        uri.find("file://") == 0 ? uri.c_str() + 7 : uri.c_str());
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

static std::string createMessageFromValidationResult(valijson::ValidationResults const& result)
{
    std::string fullMessage;
    for (valijson::ValidationResults::Error const& err : result)
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
    Schema const& schema, std::filesystem::path const& toolsDir, nlohmann::json const& scene)
{
    // valid the scene using schema
    strcpy_s(schemaPath, sizeof(schemaPath), (toolsDir / "WildPipeline/Schema").u8string().c_str());

    json schemaDocument = loadJsonFile(toolsDir, toolsDir / sceneSchemaPath);

    json fullEntityInstanceSchema = convertToInstanceSchema(schema, *schema.root);

    // Parse the json schema into an internal schema format
    valijson::Schema vjSchema;
    valijson::SchemaParser parser;
    parser.populateSchema(
        valijson::adapters::NlohmannJsonAdapter(fullEntityInstanceSchema),
        vjSchema,
        fetchDocument,
        freeDocument);

    valijson::Validator validator;
    valijson::adapters::NlohmannJsonAdapter myTargetAdapter(scene);
    valijson::ValidationResults result;
    if (!validator.validate(vjSchema, myTargetAdapter, &result))
    {
        /// @todo un-comment soon
        std::string message = createMessageFromValidationResult(result);
        throw Ent::JsonValidation(filterError(message.c_str()));
    }
}

void Ent::validateEntity(
    Schema const& schema, std::filesystem::path const& toolsDir, nlohmann::json const& entity)
{
    // valid the scene using schema
    strcpy_s(schemaPath, sizeof(schemaPath), (toolsDir / "WildPipeline/Schema").u8string().c_str());

    json schemaDocument = loadJsonFile(toolsDir, toolsDir / entitySchemaPath);

    json fullSceneInstanceSchema =
        convertToInstanceSchema(schema, schema.allDefinitions.at("#/definitions/Object"));

    // Parse the json schema into an internal schema format
    valijson::Schema vjSchema;
    valijson::SchemaParser parser;
    parser.populateSchema(
        valijson::adapters::NlohmannJsonAdapter(fullSceneInstanceSchema),
        vjSchema,
        fetchDocument,
        freeDocument);

    valijson::Validator validator;
    valijson::adapters::NlohmannJsonAdapter myTargetAdapter(entity);
    valijson::ValidationResults result;
    if (!validator.validate(vjSchema, myTargetAdapter, &result))
    {
        /// @todo un-comment soon
        std::string message = createMessageFromValidationResult(result);
        throw Ent::JsonValidation(filterError(message.c_str()));
    }
}

/// \endcond
