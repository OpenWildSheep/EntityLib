#include "SchemaLoader.h"
#include "Tools.h"

#pragma warning(push, 0)
#include <sstream>
#include <utility>
#pragma warning(pop)

/// \cond PRIVATE

using namespace nlohmann;

Ent::SchemaLoader::SchemaLoader(std::filesystem::path _schemaPath)
    : m_schemaPath(std::move(_schemaPath))
{
}

static char const* entityRefSchemaName = "#/definitions/EntityRef";

void Ent::SchemaLoader::parseSchema(
    json const& _fileRoot, json const& _data, Visitor const& vis, int depth)
{
    if (_data.count("$ref") != 0)
    {
        auto ref = _data["$ref"].get<std::string>();
        // special EntityRef handling
        if (ref == entityRefSchemaName)
        {
            // EntityRef are not parsed but handled as primitive type
            vis.openSubschema();
            vis.setName("EntityRef");
            vis.setType(DataType::entityRef);
            vis.closeSubschema();
            return;
        }
        vis.openRef(ref.c_str());
        if (parsedRef.count(ref) != 0) // Was already parsed
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
        auto sharp = ref.find('#');
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
             splitString(objectPath.string(), std::filesystem::path::preferred_separator))
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

Ent::Subschema::Meta parseMetaForType(json const& _data, Ent::DataType _type)
{
    const auto setBaseMetas = [&](Ent::Subschema::BaseMeta* _meta) {
        if (_data.count("editor") != 0u)
        {
            _meta->usedInEditor = _data["editor"].get<bool>();
        }
        if (_data.count("runtime") != 0u)
        {
            _meta->usedInRuntime = _data["runtime"].get<bool>();
        }
        if (_data.count("deprecated") != 0u)
        {
            _meta->deprecated = _data["deprecated"].get<bool>();
        }
    };

    const auto setNumberMetas = [&](Ent::Subschema::NumberMeta& _meta) {
        if (_data.count("bitdepth") != 0u)
        {
            _meta.bitDepth = _data["bitdepth"].get<uint32_t>();
        }
        if (_data.count("signed") != 0u)
        {
            _meta.isSigned = _data["signed"].get<bool>();
        }
    };
    switch (_type)
    {
    case Ent::DataType::integer:
    case Ent::DataType::number:
    {
        Ent::Subschema::NumberMeta meta;
        setBaseMetas(&meta);
        setNumberMetas(meta);
        return meta;
    }
    case Ent::DataType::string:
    case Ent::DataType::object:
    case Ent::DataType::array:
    case Ent::DataType::boolean:
    case Ent::DataType::entityRef:
    {
        Ent::Subschema::GenericMeta meta;
        setBaseMetas(&meta);
        return meta;
    }
    case Ent::DataType::null:
    default:
        ENTLIB_ASSERT_MSG(false, "Invalid current type (null) when parsing meta");
        return Ent::Subschema::GenericMeta{};
    }
}

void Ent::SchemaLoader::parseSchemaNoRef(
    json const& _rootFile, json const& _data, Visitor const& vis, int depth)
{
    DataType currentType = DataType::null;
    const auto setType = [&](DataType _type) {
        currentType = _type;
        vis.setType(_type);
    };
    // type
    if (_data.count("type") != 0u)
    {
        auto type = _data["type"].get<std::string>();
        if (type == "anyOf")
        {
            ENTLIB_ASSERT("Unexpected JSON schema type : Any");
        }
        else if (type == "array")
        {
            setType(Ent::DataType::array);
        }
        else if (type == "boolean")
        {
            setType(Ent::DataType::boolean);
        }
        else if (type == "integer")
        {
            setType(Ent::DataType::integer);
        }
        else if (type == "null")
        {
            setType(Ent::DataType::null);
        }
        else if (type == "number")
        {
            setType(Ent::DataType::number);
        }
        else if (type == "object")
        {
            setType(Ent::DataType::object);
        }
        else if (type == "string")
        {
            setType(Ent::DataType::string);
        }
        else
        {
            ENTLIB_LOGIC_ERROR("Unknown type %s", type.c_str());
        }
    }
    // properties
    if (_data.count("properties") != 0u)
    {
        setType(Ent::DataType::object);
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
    if (_data.count("default") != 0u)
    {
        vis.setDefaultValue(Null{});
        json const& def = _data.at("default");
        switch (def.type())
        {
        case nlohmann::json::value_t::null: setType(Ent::DataType::null); break;
        case nlohmann::json::value_t::object: setType(Ent::DataType::object); break;
        case nlohmann::json::value_t::array: setType(Ent::DataType::array); break;
        case nlohmann::json::value_t::discarded: break;
        case nlohmann::json::value_t::string:
            setType(Ent::DataType::string);
            vis.setDefaultValue(def.get<std::string>());
            break;
        case nlohmann::json::value_t::boolean:
            setType(Ent::DataType::boolean);
            vis.setDefaultValue(def.get<bool>());
            break;
        case nlohmann::json::value_t::number_integer:
        case nlohmann::json::value_t::number_unsigned:
            setType(Ent::DataType::integer);
            vis.setDefaultValue(def.get<int64_t>());
            break;
        case nlohmann::json::value_t::number_float:
            setType(Ent::DataType::number);
            vis.setDefaultValue(def.get<float>());
            break;
        }
    }
    if (_data.count("const") != 0u)
    {
        vis.setConstValue(Null{});
        json const& def = _data.at("const");
        switch (def.type())
        {
        case nlohmann::json::value_t::null: setType(Ent::DataType::null); break;
        case nlohmann::json::value_t::object: setType(Ent::DataType::object); break;
        case nlohmann::json::value_t::array: setType(Ent::DataType::array); break;
        case nlohmann::json::value_t::discarded: break;
        case nlohmann::json::value_t::string:
            setType(Ent::DataType::string);
            vis.setConstValue(def.get<std::string>());
            break;
        case nlohmann::json::value_t::boolean:
            setType(Ent::DataType::boolean);
            vis.setConstValue(def.get<bool>());
            break;
        case nlohmann::json::value_t::number_integer:
        case nlohmann::json::value_t::number_unsigned:
            setType(Ent::DataType::integer);
            vis.setConstValue(def.get<int64_t>());
            break;
        case nlohmann::json::value_t::number_float:
            setType(Ent::DataType::number);
            vis.setConstValue(def.get<float>());
            break;
        }
    }
    if (_data.count("items") != 0u)
    {
        setType(Ent::DataType::array);
        auto const& items = _data["items"];
        // items linear
        if (items.type() == nlohmann::json::value_t::array)
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
        else if (items.type() == nlohmann::json::value_t::object)
        {
            vis.openSingularItem();
            parseSchema(_rootFile, items, vis, depth + 1);
            vis.closeSingularItem();
        }
        else
        {
            ENTLIB_LOGIC_ERROR("Unexpected json items type : %s", items.type_name());
        }
    }
    if (_data.count("oneOf") != 0u)
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
    if (_data.count("maxItems") != 0u)
    {
        vis.setMaxItems(_data["maxItems"].get<size_t>());
    }
    if (_data.count("minItems") != 0u)
    {
        vis.setMinItems(_data["minItems"].get<size_t>());
    }
    if (_data.count("enum") != 0u)
    {
        for (json const& enmNode : _data["enum"])
        {
            vis.addEnumValue(enmNode.get<std::string>().c_str());
        }
    }
    if (_data.count("required") != 0u)
    {
        // TODO required
    }
    if (_data.count("meta") != 0u)
    {
        if (!_data["meta"].is_object())
        {
            ENTLIB_LOGIC_ERROR(
                "Unexpected json items type for \"meta\" : %s", _data["meta"].type_name());
        }
        else
        {
            if (currentType == DataType::null)
            {
                std::string name = "Unnamed definition";
                if (_data.count("name") != 0u)
                {
                    name = _data["name"].get<std::string>();
                }
                ENTLIB_LOGIC_ERROR("Unexpected json definition type (\"%s\")", name.c_str());
            }
            vis.setMeta(parseMetaForType(_data["meta"], currentType));
        }
    }
    if (_data.count("name") != 0u)
    {
        // manually specified type name (typically used for enums properties that are inlined)
        vis.setName(_data["name"].get<std::string>());
    }
}

void Ent::SchemaLoader::readSchema(Schema* globalSchema, json const& _fileRoot, json const& _data)
{
    Ent::SubschemaRef& schema = globalSchema->root;
    Visitor vis;
    std::vector<Ent::SubschemaRef*> stack{ &schema };
    stack.reserve(1000);
    vis.addEnumValue = [&](char const* val) {
        stack.back()->get().enumValues.emplace_back(val);
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
    vis.setConstValue = [&](const Subschema::DefaultValue& val) {
        stack.back()->get().constValue = val;
    };
    vis.setDefaultValue = [&](Subschema::DefaultValue val) {
        stack.back()->get().defaultValue = std::move(val);
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
        char const* typeName = getRefTypeName(link);
        // Force to create the definition (do nothing if already exist)
        ENTLIB_ASSERT_MSG(typeName != nullptr, "Can't get type name in '%s'!!", link);
        globalSchema->allDefinitions[link].name = typeName;
        stack.back()->subSchemaOrRef = SubschemaRef::Ref{ globalSchema, link };
    };
    vis.closeRef = [&]() {
    };
    vis.openSubschema = [&]() {
        stack.back()->subSchemaOrRef = Subschema{};
    };
    vis.closeSubschema = [&]() {
    };
    vis.setMeta = [&](Subschema::Meta meta) {
        auto&& subSchema = stack.back()->get();
        subSchema.meta = std::move(meta);
    };
    vis.setName = [&](std::string name) {
        auto&& subSchema = stack.back()->get();
        ENTLIB_ASSERT_MSG(
            subSchema.name.empty(),
            "Subschema is already named '%s' (new name: '%s')",
            subSchema.name.c_str(),
            name.c_str());
        subSchema.name = std::move(name);
    };
    parseSchema(_fileRoot, _data, vis, 0);
}

/// \endcond
