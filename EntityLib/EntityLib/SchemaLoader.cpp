#include "SchemaLoader.h"
#include "Tools.h"

#pragma warning(push, 0)
#include <sstream>
#pragma warning(pop)

using namespace nlohmann;

static std::vector<std::string> split(const std::string& _str, char _delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(_str);
    while (std::getline(tokenStream, token, _delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

Ent::SchemaLoader::SchemaLoader(std::filesystem::path _schemaPath)
    : m_schemaPath(std::move(_schemaPath))
{
}

Ent::Subschema Ent::SchemaLoader::readSchema(json const& _fileRoot, json const& _data)
{
    if (_data.count("$ref"))
    {
        auto ref = _data["$ref"].get<std::string>();
        // ref look like this : "file://EditionComponents.json#/definitions/HeightObj"
        if (ref.find("file://") == 0)
        {
            ref = ref.substr(strlen("file://"));
        }
        auto sharp = ref.find("#");
        auto fileName = ref.substr(0, sharp);
        std::filesystem::path objectPath = ref.substr(sharp + 2);

        json const* refRoot{};
        if (fileName.empty())
        {
            refRoot = &_fileRoot;
        }
        else
        {
            auto iter = m_schemaMap.find(fileName);
            if (iter == m_schemaMap.end())
            {
                m_schemaMap[fileName] = loadJsonFile(m_schemaPath / fileName);
            }
            refRoot = &m_schemaMap[fileName];
        }
        json const* node = refRoot;
        for (auto const& token : split(objectPath.string(), '\\'))
        {
            node = &((*node).at(token));
        }
        return readSchemaNoRef(*refRoot, *node);
    }
    else
    {
        return readSchemaNoRef(_fileRoot, _data);
    }
}

Ent::Subschema Ent::SchemaLoader::readSchemaNoRef(json const& _rootFile, json const& _data)
{
    Ent::Subschema schema;
    // type
    if (_data.count("type"))
    {
        auto type = _data["type"].get<std::string>();
        ENTLIB_ASSERT(
            (schema.type == Ent::DataType::null) && "Multiple type in Subschema is Unexpected");
        if (type == "anyOf")
        {
            ENTLIB_ASSERT("Unexpected JSON schema type : Any");
        }
        else if (type == "array")
        {
            schema.type = Ent::DataType::array;
        }
        else if (type == "boolean")
        {
            schema.type = Ent::DataType::boolean;
        }
        else if (type == "integer")
        {
            schema.type = Ent::DataType::integer;
        }
        else if (type == "null")
        {
            schema.type = Ent::DataType::null;
        }
        else if (type == "number")
        {
            schema.type = Ent::DataType::number;
        }
        else if (type == "object")
        {
            schema.type = Ent::DataType::object;
        }
        else if (type == "string")
        {
            schema.type = Ent::DataType::string;
        }
        else
            ENTLIB_LOGIC_ERROR("Unknown type %s", type.c_str());
    }
    // properties
    if (_data.count("properties"))
    {
        for (auto&& name_prop : _data["properties"].items())
        {
            auto const& propName = name_prop.key();
            auto const& prop = name_prop.value();
            Ent::Subschema sub = readSchema(_rootFile, prop);
            schema.properties.emplace(propName.c_str(), std::move(sub));
        }
    }
    // default
    if (_data.count("default"))
    {
        schema.defaultValue = _data["default"];
    }
    if (_data.count("items"))
    {
        auto const& items = _data["items"];
        // items linear
        if (items.type() == nlohmann::detail::value_t::array)
        {
            schema.linearItems = std::vector<Ent::Subschema>(items.size());
            for (size_t index = 0; index < items.size(); ++index)
            {
                (*schema.linearItems)[index] = readSchema(_rootFile, items[index]);
            }
        }
        // items singular
        else if (items.type() == nlohmann::detail::value_t::object)
        {
            schema.singularItems = std::make_unique<Ent::Subschema>(readSchema(_rootFile, items));
        }
        else
            ENTLIB_LOGIC_ERROR("Unexpected json items type : %s", items.type_name());
    }
    if (_data.count("maxItems"))
    {
        _data["maxItems"].get_to(schema.maxItems);
    }
    if (_data.count("minItems"))
    {
        _data["minItems"].get_to(schema.minItems);
    }
    if (_data.count("enum"))
    {
        for (json const& enmNode : _data["enum"])
        {
            schema.enumValues.push_back(enmNode.get<std::string>());
        }
    }
    if (_data.count("required"))
    {
        // TODO required
    }
    return schema;
}
