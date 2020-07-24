#include "ValidJson.h"
#include "Tools.h"

#pragma warning(push, 0)
#pragma warning(disable : 4702)
// TODO Add valid check
#include <valijson/adapters/nlohmann_json_adapter.hpp>
#include <valijson/utils/nlohmann_json_utils.hpp>
#include <valijson/schema.hpp>
#include <valijson/schema_parser.hpp>
#include <valijson/validator.hpp>
#pragma warning(pop)

using namespace nlohmann;

char schemaPath[1024] = {};

json const* fetchDocument(const std::string& uri)
{
    json* fetchedRoot = new json{};
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

    return fetchedRoot;
}

void freeDocument(json const* adapter)
{
    delete adapter;
}

char const* sceneSchemaPath = "WildPipeline/Schema/Scene-schema.json";

void Ent::validScene(std::filesystem::path toolsDir, nlohmann::json const& scene)
{
    // valid the scene using schema

    json schemaDocument = loadJsonFile(toolsDir / sceneSchemaPath);

    // Parse the json schema into an internal schema format
    strcpy(schemaPath, (toolsDir / "WildPipeline/Schema").u8string().c_str());
    valijson::Schema vjSchema;
    valijson::SchemaParser parser;
    parser.populateSchema(
        valijson::adapters::NlohmannJsonAdapter(schemaDocument), vjSchema, fetchDocument, freeDocument);

    valijson::Validator validator;
    valijson::adapters::NlohmannJsonAdapter myTargetAdapter(scene);
    if (!validator.validate(vjSchema, myTargetAdapter, NULL))
    {
        std::runtime_error("Validation failed.");
    }
}

void Ent::validEntity(std::filesystem::path toolsDir, nlohmann::json const& entity)
{
    // valid the scene using schema

    json schemaDocument = loadJsonFile(toolsDir / sceneSchemaPath);

    // Parse the json schema into an internal schema format
    strcpy(schemaPath, (toolsDir / "WildPipeline/Schema").u8string().c_str());
    valijson::Schema vjSchema;
    valijson::SchemaParser parser;
    parser.populateSchema(
        valijson::adapters::NlohmannJsonAdapter(schemaDocument), vjSchema, fetchDocument, freeDocument);

    valijson::Validator validator;
    valijson::adapters::NlohmannJsonAdapter myTargetAdapter(entity);
    if (!validator.validate(vjSchema, myTargetAdapter, NULL))
    {
        std::runtime_error("Validation failed.");
    }
}
