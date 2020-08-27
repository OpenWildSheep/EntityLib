#include "SchemaLoader.h"
#include "Tools.h"

#pragma warning(push, 0)
#include <sstream>
#pragma warning(pop)

/// \cond PRIVATE

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

void Ent::SchemaLoader::parseSchema(
    json const& _fileRoot, json const& _data, Visitor const& vis, int depth)
{
    if (_data.count("$ref"))
    {
        auto ref = _data["$ref"].get<std::string>();
        vis.openRef(ref.c_str());
        if (parsedRef.count(ref)) // Was already parsed
        {
            vis.closeRef();
            return;
        }
        parsedRef.insert(ref);
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
        objectPath.make_preferred();
        for (auto const& token :
             split(objectPath.string(), std::filesystem::path::preferred_separator))
        {
            node = &((*node).at(token));
        }
        parseSchemaNoRef(*refRoot, *node, vis, depth);
        vis.closeRef();
    }
    else
    {
        vis.openSubschema();
        parseSchemaNoRef(_fileRoot, _data, vis, depth);
        vis.closeSubschema();
    }
}

void Ent::SchemaLoader::parseSchemaNoRef(
    json const& _rootFile, json const& _data, Visitor const& vis, int depth)
{
    // type
    if (_data.count("type"))
    {
        auto type = _data["type"].get<std::string>();
        if (type == "anyOf")
        {
            ENTLIB_ASSERT("Unexpected JSON schema type : Any");
        }
        else if (type == "array")
        {
            vis.setType(Ent::DataType::array);
        }
        else if (type == "boolean")
        {
            vis.setType(Ent::DataType::boolean);
        }
        else if (type == "integer")
        {
            vis.setType(Ent::DataType::integer);
        }
        else if (type == "null")
        {
            vis.setType(Ent::DataType::null);
        }
        else if (type == "number")
        {
            vis.setType(Ent::DataType::number);
        }
        else if (type == "object")
        {
            vis.setType(Ent::DataType::object);
        }
        else if (type == "string")
        {
            vis.setType(Ent::DataType::string);
        }
        else
            ENTLIB_LOGIC_ERROR("Unknown type %s", type.c_str());
    }
    // properties
    if (_data.count("properties"))
    {
        vis.setType(Ent::DataType::object);
        for (auto&& name_prop : _data["properties"].items())
        {
            auto const& propName = name_prop.key();
            auto const& prop = name_prop.value();
            vis.openProperty(propName.c_str());
            parseSchema(_rootFile, prop, vis, depth + 1);
            vis.closeProperty();
        }
    }
    // default
    if (_data.count("default"))
    {
        vis.setDefaultValue(Null{});
        json const& def = _data.at("default");
        switch (def.type())
        {
        case nlohmann::detail::value_t::null: vis.setType(Ent::DataType::null); break;
        case nlohmann::detail::value_t::object: vis.setType(Ent::DataType::object); break;
        case nlohmann::detail::value_t::array: vis.setType(Ent::DataType::array); break;
        case nlohmann::detail::value_t::discarded: break;
        case nlohmann::detail::value_t::string:
            vis.setType(Ent::DataType::string);
            vis.setDefaultValue(def.get<std::string>());
            break;
        case nlohmann::detail::value_t::boolean:
            vis.setType(Ent::DataType::boolean);
            vis.setDefaultValue(def.get<bool>());
            break;
        case nlohmann::detail::value_t::number_integer:
        case nlohmann::detail::value_t::number_unsigned:
            vis.setType(Ent::DataType::integer);
            vis.setDefaultValue(def.get<int64_t>());
            break;
        case nlohmann::detail::value_t::number_float:
            vis.setType(Ent::DataType::number);
            vis.setDefaultValue(def.get<float>());
            break;
        }
    }
    if (_data.count("const"))
    {
        vis.setConstValue(Null{});
        json const& def = _data.at("const");
        switch (def.type())
        {
        case nlohmann::detail::value_t::null: vis.setType(Ent::DataType::null); break;
        case nlohmann::detail::value_t::object: vis.setType(Ent::DataType::object); break;
        case nlohmann::detail::value_t::array: vis.setType(Ent::DataType::array); break;
        case nlohmann::detail::value_t::discarded: break;
        case nlohmann::detail::value_t::string:
            vis.setType(Ent::DataType::string);
            vis.setConstValue(def.get<std::string>());
            break;
        case nlohmann::detail::value_t::boolean:
            vis.setType(Ent::DataType::boolean);
            vis.setConstValue(def.get<bool>());
            break;
        case nlohmann::detail::value_t::number_integer:
        case nlohmann::detail::value_t::number_unsigned:
            vis.setType(Ent::DataType::integer);
            vis.setConstValue(def.get<int64_t>());
            break;
        case nlohmann::detail::value_t::number_float:
            vis.setType(Ent::DataType::number);
            vis.setConstValue(def.get<float>());
            break;
        }
    }
    if (_data.count("items"))
    {
        vis.setType(Ent::DataType::array);
        auto const& items = _data["items"];
        // items linear
        if (items.type() == nlohmann::detail::value_t::array)
        {
            vis.setLinearItem(items.size());
            for (size_t index = 0; index < items.size(); ++index)
            {
                vis.openLinearItem(index);
                parseSchema(_rootFile, items[index], vis, depth + 1);
                vis.closeLinearItem();
            }
        }
        // items singular
        else if (items.type() == nlohmann::detail::value_t::object)
        {
            vis.openSingularItem();
            parseSchema(_rootFile, items, vis, depth + 1);
            vis.closeSingularItem();
        }
        else
            ENTLIB_LOGIC_ERROR("Unexpected json items type : %s", items.type_name());
    }
    if (_data.count("oneOf"))
    {
        auto const& items = _data["oneOf"];
        ENTLIB_ASSERT(vis.setOneOf != nullptr);
        vis.setOneOf(items.size());
        for (size_t index = 0; index < items.size(); ++index)
        {
            vis.openOneOfItem(index);
            parseSchema(_rootFile, items[index], vis, depth + 1);
            vis.closeOneOfItem();
        }
    }
    if (_data.count("maxItems"))
    {
        vis.setMaxItems(_data["maxItems"].get<size_t>());
    }
    if (_data.count("minItems"))
    {
        vis.setMinItems(_data["minItems"].get<size_t>());
    }
    if (_data.count("enum"))
    {
        for (json const& enmNode : _data["enum"])
        {
            vis.addEnumValue(enmNode.get<std::string>().c_str());
        }
    }
    if (_data.count("required"))
    {
        // TODO required
    }
}

void Ent::SchemaLoader::readSchema(Schema* globalSchema, json const& _fileRoot, json const& _data)
{
    Ent::SubschemaRef& schema = globalSchema->root;
    Visitor vis;
    std::vector<Ent::SubschemaRef*> stack{ &schema };
    stack.reserve(1000);
    vis.addEnumValue = [&](char const* val) {
        stack.back()->get().enumValues.push_back(val);
    };
    vis.closeLinearItem = [&] {
        ENTLIB_ASSERT(
            stack.back()->get().type != DataType::array or stack.back()->get().singularItems != nullptr
            or stack.back()->get().linearItems.has_value());
        stack.pop_back();
    };
    vis.closeProperty = [&] {
        ENTLIB_ASSERT(
            stack.back()->get().type != DataType::array or stack.back()->get().singularItems != nullptr
            or stack.back()->get().linearItems.has_value());
        stack.pop_back();
    };
    vis.closeSingularItem = [&] {
        ENTLIB_ASSERT(
            stack.back()->get().type != DataType::array or stack.back()->get().singularItems != nullptr
            or stack.back()->get().linearItems.has_value());
        stack.pop_back();
    };
    vis.openLinearItem = [&](size_t index) {
        Ent::SubschemaRef& lin = stack.back()->get().linearItems->at(index);
        stack.push_back(&lin);
    };
    vis.openProperty = [&](char const* propName) {
        Ent::SubschemaRef& subSchema = stack.back()->get().properties[propName];
        stack.push_back(&subSchema);
    };
    vis.openSingularItem = [&]() {
        stack.back()->get().singularItems = std::make_unique<Ent::SubschemaRef>();
        stack.push_back(&(*stack.back()->get().singularItems));
    };
    vis.setConstValue = [&](Subschema::DefaultValue val) {
        stack.back()->get().constValue = val;
    };
    vis.setDefaultValue = [&](Subschema::DefaultValue val) {
        stack.back()->get().defaultValue = val;
    };
    vis.setLinearItem = [&](size_t size) {
        stack.back()->get().linearItems = std::vector<Ent::SubschemaRef>();
        stack.back()->get().linearItems->resize(size);
    };
    vis.setMaxItems = [&](size_t val) {
        stack.back()->get().maxItems = val;
    };
    vis.setMinItems = [&](size_t val) {
        stack.back()->get().minItems = val;
    };
    vis.setType = [&](DataType type) {
        stack.back()->get().type = type;
    };
    vis.setOneOf = [&](size_t size) {
        stack.back()->get().oneOf = std::vector<Ent::SubschemaRef>();
        stack.back()->get().oneOf->resize(size);
    };
    vis.openOneOfItem = [&](size_t index) {
        Ent::SubschemaRef& lin = stack.back()->get().oneOf->at(index);
        stack.push_back(&lin);
    };
    vis.closeOneOfItem = [&] {
        stack.pop_back();
    };

    vis.openRef = [&](char const* link) {
        globalSchema->allDefinitions[link]; // Force to create the definition (do nothing if already exist)
        stack.back()->subSchemaOrRef = SubschemaRef::Ref{ globalSchema, link };
    };
    vis.closeRef = [&]() {
    };
    vis.openSubschema = [&]() {
        stack.back()->subSchemaOrRef = Subschema{};
    };
    vis.closeSubschema = [&]() {
    };

    parseSchema(_fileRoot, _data, vis, 0);
}

/// \endcond
