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
    std::string const& _filename, json const& _fileRoot, json const& _data, Visitor const& vis, int depth)
{
    ENTLIB_ASSERT(not _filename.empty());

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
        // Use absolute path to avoid name collision
        auto absRef = (ref.front() == '#') ? ("file://" + _filename + ref) : ref;
        vis.openRef(absRef.c_str());
        if (parsedRef.count(absRef) != 0) // Was already parsed
        {
            vis.closeRef();
            return;
        }
        parsedRef.insert(absRef);
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
            fileName = _filename;
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
        parseSchemaNoRef(fileName, *refRoot, *node, vis, depth);
        vis.closeRef();
    }
    else
    {
        vis.openSubschema();
        parseSchemaNoRef(_filename, _fileRoot, _data, vis, depth);
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
    const auto setUnionMetas = [&](Ent::Subschema::UnionMeta& _meta) {
        if (_data.count("unionDataField") != 0u)
        {
            _meta.dataField = _data["unionDataField"].get<std::string>();
        }
        if (_data.count("unionTypeField") != 0u)
        {
            _meta.typeField = _data["unionTypeField"].get<std::string>();
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
    case Ent::DataType::oneOf:
    {
        Ent::Subschema::UnionMeta meta;
        setBaseMetas(&meta);
        setUnionMetas(meta);
        return meta;
    }
    case Ent::DataType::null:
    case Ent::DataType::COUNT:
    default: ENTLIB_ASSERT_MSG(false, "Invalid DataType when parsing meta"); return {};
    }
}

void Ent::SchemaLoader::parseSchemaNoRef(
    std::string const& _filename, json const& _rootFile, json const& _data, Visitor const& vis, int depth)
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
            parseSchema(_filename, _rootFile, prop, vis, depth + 1);
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
                parseSchema(_filename, _rootFile, items[index], vis, depth + 1);
                vis.closeLinearItem();
            }
        }
        // items singular
        else if (items.type() == nlohmann::json::value_t::object)
        {
            vis.openSingularItem();
            parseSchema(_filename, _rootFile, items, vis, depth + 1);
            vis.closeSingularItem();
        }
        else
        {
            ENTLIB_LOGIC_ERROR("Unexpected json items type : %s", items.type_name());
        }
    }
    if (_data.count("oneOf") != 0u)
    {
        setType(Ent::DataType::oneOf);
        auto const& items = _data["oneOf"];
        ENTLIB_ASSERT(vis.setOneOf != nullptr);
        vis.setOneOf(items.size());
        for (size_t index = 0; index < items.size(); ++index)
        {
            vis.openOneOfItem(index);
            parseSchema(_filename, _rootFile, items[index], vis, depth + 1);
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

// TODO Loïc : (Low prio) It could be good to use a real logger system. (like spdlog for example)
#ifdef ENTLIB_DEBUG_READSCHEMA
#define ENTLIB_DEBUG_PRINTF(message, ...) printf(message, __VA_ARGS__);
#else
#define ENTLIB_DEBUG_PRINTF(message, ...)
#endif

void Ent::SchemaLoader::readSchema(
    Schema* globalSchema, std::string const& _filename, json const& _fileRoot, json const& _data)
{
    Ent::SubschemaRef& schema = globalSchema->root;
    Visitor vis;
    std::vector<Ent::SubschemaRef*> stack{ &schema };
    stack.reserve(1000);
    vis.addEnumValue = [&](char const* val) {
        stack.back()->get().enumValues.emplace_back(val);
    };
    auto checkAllStack = [&stack] {
        for (Ent::SubschemaRef* ref : stack)
        {
            ENTLIB_ASSERT(ref->deleteCheck.state_ == DeleteCheck::State::VALID);
        }
    };
    auto getTab = [&stack] {
        return std::string(stack.size() * 4, ' ').c_str();
    };
    vis.closeLinearItem = [&] {
        checkAllStack();
        ENTLIB_ASSERT(
            stack.back()->get().type != DataType::array or stack.back()->get().singularItems != nullptr
            or stack.back()->get().linearItems.has_value());
        stack.pop_back();
        checkAllStack();
        ENTLIB_DEBUG_PRINTF("%sloseLinearItem\n", getTab());
    };
    vis.closeProperty = [&] {
        checkAllStack();
        ENTLIB_ASSERT(
            stack.back()->get().type != DataType::array or stack.back()->get().singularItems != nullptr
            or stack.back()->get().linearItems.has_value());
        stack.pop_back();
        checkAllStack();
        ENTLIB_DEBUG_PRINTF("%scloseProperty\n", getTab());
    };
    vis.closeSingularItem = [&] {
        checkAllStack();
        ENTLIB_ASSERT(
            stack.back()->get().type != DataType::array or stack.back()->get().singularItems != nullptr
            or stack.back()->get().linearItems.has_value());
        stack.pop_back();
        checkAllStack();
        ENTLIB_DEBUG_PRINTF("%scloseSingularItem\n", getTab());
    };
    vis.openLinearItem = [&](size_t index) {
        checkAllStack();
        ENTLIB_DEBUG_PRINTF("%sopenLinearItem %zu\n", getTab(), index);
        Ent::SubschemaRef& lin = stack.back()->get().linearItems->at(index);
        stack.push_back(&lin);
        checkAllStack();
    };
    vis.openProperty = [&](char const* propName) {
        checkAllStack();
        ENTLIB_DEBUG_PRINTF("%sopenProperty %s\n", getTab(), propName);
        Ent::SubschemaRef& subSchema = stack.back()->get().properties[propName];
        stack.push_back(&subSchema);
        checkAllStack();
    };
    vis.openSingularItem = [&]() {
        checkAllStack();
        ENTLIB_DEBUG_PRINTF("%sopenSingularItem\n", getTab());
        stack.back()->get().singularItems = std::make_unique<Ent::SubschemaRef>();
        checkAllStack();
        stack.push_back(&(*stack.back()->get().singularItems));
        checkAllStack();
    };
    vis.setConstValue = [&](const Subschema::DefaultValue& val) {
        checkAllStack();
        stack.back()->get().constValue = val;
    };
    vis.setDefaultValue = [&](Subschema::DefaultValue val) {
        checkAllStack();
        stack.back()->get().defaultValue = std::move(val);
    };
    vis.setLinearItem = [&](size_t size) {
        checkAllStack();
        stack.back()->get().linearItems = std::vector<Ent::SubschemaRef>();
        stack.back()->get().linearItems->resize(size);
    };
    vis.setMaxItems = [&](size_t val) {
        checkAllStack();
        stack.back()->get().maxItems = val;
    };
    vis.setMinItems = [&](size_t val) {
        checkAllStack();
        stack.back()->get().minItems = val;
    };
    vis.setType = [&](DataType type) {
        ENTLIB_DEBUG_PRINTF("%ssetType %d\n", getTab(), (int)type);
        checkAllStack();
        stack.back()->get().type = type;
    };
    vis.setOneOf = [&](size_t size) {
        ENTLIB_DEBUG_PRINTF("%ssetOneOf %zu\n", getTab(), size);
        checkAllStack();
        stack.back()->get().type = Ent::DataType::oneOf;
        stack.back()->get().oneOf = std::vector<Ent::SubschemaRef>();
        stack.back()->get().oneOf->resize(size);
    };
    vis.openOneOfItem = [&](size_t index) {
        ENTLIB_DEBUG_PRINTF("%sopenOneOfItem %zu\n", getTab(), index);
        checkAllStack();
        Ent::SubschemaRef& lin = stack.back()->get().oneOf->at(index);
        stack.push_back(&lin);
        checkAllStack();
    };
    vis.closeOneOfItem = [&] {
        checkAllStack();
        stack.pop_back();
        checkAllStack();
        ENTLIB_DEBUG_PRINTF("%scloseOneOfItem\n", getTab());
    };

    vis.openRef = [&](char const* link) {
        checkAllStack();
        ENTLIB_DEBUG_PRINTF("%sopenRef %s\n", getTab(), link);
        char const* typeName = getRefTypeName(link);
        // Force to create the definition (do nothing if already exist)
        ENTLIB_ASSERT_MSG(typeName != nullptr, "Can't get type name in '%s'!!", link);
        globalSchema->allDefinitions[link].name = typeName;
        auto& ref = stack.back()->subSchemaOrRef;
        ENTLIB_ASSERT(ref.is<Null>());
        ref = SubschemaRef::Ref{ globalSchema, link };
    };
    vis.closeRef = [&]() {
        checkAllStack();
        ENTLIB_DEBUG_PRINTF("%scloseRef\n", getTab());
    };
    vis.openSubschema = [&]() {
        ENTLIB_DEBUG_PRINTF("%sopenSubschema\n", getTab());
        checkAllStack();
        ENTLIB_ASSERT(stack.back()->subSchemaOrRef.is<Null>());
        stack.back()->subSchemaOrRef = Subschema{};
        ENTLIB_DEBUG_PRINTF("%sopenSubschema2\n", getTab());
        checkAllStack();
    };
    vis.closeSubschema = [&]() {
        ENTLIB_DEBUG_PRINTF("%scloseSubschema\n", getTab());
    };
    vis.setMeta = [&](Subschema::Meta meta) {
        checkAllStack();
        auto&& subSchema = stack.back()->get();
        subSchema.meta = std::move(meta);
    };
    vis.setName = [&](std::string name) {
        ENTLIB_DEBUG_PRINTF("%ssetName %s\n", getTab(), name.c_str());
        checkAllStack();
        auto&& subSchema = stack.back()->get();
        ENTLIB_ASSERT_MSG(
            subSchema.name.empty(),
            "Subschema is already named '%s' (new name: '%s')",
            subSchema.name.c_str(),
            name.c_str());
        subSchema.name = std::move(name);
    };
    parseSchema(_filename, _fileRoot, _data, vis, 0);
}

/// \endcond
