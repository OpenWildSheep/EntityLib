#include "include/EntityLib.h"

#include "Tools.h"
#include "SchemaLoader.h"
#include "include/ComponentMerge.h"

#pragma warning(push, 0)
#pragma warning(disable : 4702)
#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <utility>
#include <ciso646>

#include "external/json.hpp"
#include "ValidJson.h"
#pragma warning(pop)

/// \cond PRIVATE

using namespace nlohmann;

namespace Ent
{
    char const* actorStatesSchemaName = "./Scene-schema.json#/definitions/ActorStates";
    char const* colorSchemaName = "./RuntimeComponents.json#/definitions/Color";
    static Ent::Node makeDefaultColorField(EntityLib const& _entlib)
    {
        Ent::Subschema const& colorSchema = AT(_entlib.schema.schema.allDefinitions, colorSchemaName);
        return _entlib.loadNode(colorSchema, json(), nullptr);
    }

    // canonical or weakly_canonical find the original physic drive but we want to keep X:
    // We also want to add '/' if the path is a letter (X:)
    // We also want path with forward slashes
    static std::filesystem::path very_weakly_canonical(std::filesystem::path const& _path)
    {
        std::filesystem::path c;
        for (auto iter = _path.begin(), endIt = _path.end(); iter != endIt; ++iter)
        {
            if (iter->native() == L"..")
            {
                if (c.empty())
                {
                    c /= *iter;
                }
                else
                    c = c.parent_path();
            }
            else if (iter->native() != L".")
            {
                c /= *iter;
            }
        }
        if (c.native().back() == L':')
        {
            c = (c.native() + L'/');
        }
        return c.make_preferred();
    }

    EntityLib::EntityLib(std::filesystem::path _rootPath, bool _doMergeComponents)
        : rootPath(very_weakly_canonical(_rootPath)) // Read schema and dependencies
    {
        rawdataPath = getAbsolutePath(rootPath / "RawData");
        toolsDir = getAbsolutePath(rootPath / "Tools");
        auto schemaPath = toolsDir / "WildPipeline/Schema";

        SchemaLoader loader(toolsDir, schemaPath);

        if (_doMergeComponents)
        {
            // mergeComponents create the content of the "MergedComponents.json" file
            json mergedComps = mergeComponents(toolsDir);
            loader.addInCache("MergedComponents.json", std::move(mergedComps));
        }

        json schemaDocument = loadJsonFile(toolsDir, "WildPipeline/Schema/Scene-schema.json");

        loader.readSchema(&schema.schema, "Scene-schema.json", schemaDocument, schemaDocument);
        schema.schema.entityLib = this;

        auto&& compList =
            schema.schema.allDefinitions.at("./MergedComponents.json#/definitions/Component").oneOf;

        for (SubschemaRef& comp : *compList)
        {
            auto&& compName = AT(comp->properties, "Type")->constValue->get<std::string>();
            auto&& compSchema = *AT(comp->properties, "Data");
            compSchema.meta = comp->meta;
            schema.components.emplace(compName, &compSchema);
        }

        json dependencies = loadJsonFile(toolsDir, "WildPipeline/Schema/Dependencies.json");
        for (json const& comp : dependencies["Dependencies"])
        {
            auto name = comp["className"].get<std::string>();
            std::vector<std::string> deps;
            for (json const& dep : comp["dependencies"])
            {
                if (not dep["Optional"].get<bool>())
                {
                    deps.push_back(dep["Name"].get<std::string>());
                }
            }
            componentDependencies.emplace(std::move(name), std::move(deps));
        }
    }

    EntityLib::~EntityLib() = default;

    // ************************************ Union *************************************************

    bool Ent::Union::hasOverride() const
    {
        return wrapper->hasOverride();
    }

    Node* Union::getUnionData()
    {
        return wrapper->at(metaData->dataField.c_str());
    }

    Node const* Union::getUnionData() const
    {
        if (wrapper.has_value())
        {
            return wrapper->at(metaData->dataField.c_str());
        }
        else
        {
            return nullptr;
        }
    }

    char const* Union::getUnionType() const
    {
        if (wrapper.has_value())
        {
            ENTLIB_ASSERT_MSG(
                wrapper->count(metaData->typeField.c_str()),
                "Field %s not found in union",
                metaData->typeField.c_str());
            auto typeNode = wrapper->at(metaData->typeField.c_str());
            ENTLIB_ASSERT(typeNode);
            ENTLIB_ASSERT_MSG(
                not typeNode->hasDefaultValue(),
                "In Union, the type-field (%s) is expected to be set",
                metaData->typeField.c_str());
            return typeNode->getString();
        }
        else
        {
            return nullptr;
        }
    }

    Node* Union::setUnionType(EntityLib const& _entlib, char const* _type)
    {
        if (getUnionType() != _type)
        {
            Subschema const* subTypeSchema{};
            std::tie(subTypeSchema, typeIndex) = schema->getUnionTypeWrapper(_type);
            // TODO : Loïc - low prio - Find a way to get the super.
            //   It could be hard because we are no more in the loading phase, so the super is
            //   now delete.
            wrapper = _entlib.loadNode(*subTypeSchema, json(), nullptr);
            wrapper->at(metaData->typeField.c_str())->setString(_type);
        }
        return getUnionData();
    }

    void Union::computeMemory(MemoryProfiler& prof) const
    {
        if (wrapper)
        {
            wrapper->computeMemory(prof);
            prof.addMem("Union::wrapper", sizeof(Node));
        }
    }

    void Union::unset()
    {
        wrapper->unset();
        Subschema const* subTypeSchema{};
        std::tie(subTypeSchema, typeIndex) = schema->getUnionTypeWrapper(getUnionType());
    }

    void Union::applyAllValues(Union& _dest, CopyMode _copyMode) const
    {
        if (typeIndex != _dest.typeIndex)
        {
            _dest.setUnionType(*wrapper->getEntityLib(), getUnionType());
        }
        wrapper->applyAllValues(*_dest.wrapper, _copyMode);
    }

    // ************************************* Object ***********************************************

    void Ent::Object::unset()
    {
        for (auto&& name_node : nodes)
        {
            name_node.second->unset();
        }
    }

    // For Entity and Object. Decide to resetInstanceOf or not depending on \b _copyMode
    template <typename T>
    void applyInstanceOfField(T const& _source, T& _dest, Ent::CopyMode _copyMode)
    {
        auto sourcePrefabPath = _source.getInstanceOfValue().get().c_str();
        if (_source.getInstanceOfValue().get() != _dest.getInstanceOfValue().get())
        {
            _dest.resetInstanceOf(sourcePrefabPath == nullptr ? "" : sourcePrefabPath);
        }
        else if (_copyMode == CopyMode::CopyOverride)
        {
            if (_source.getInstanceOfValue().isSet() and not _dest.getInstanceOfValue().isSet())
            {
                _dest.resetInstanceOf(sourcePrefabPath == nullptr ? "" : sourcePrefabPath);
            }
        }
    }

    void Ent::Object::applyAllValues(Object& _dest, CopyMode _copyMode) const
    {
        applyInstanceOfField(*this, _dest, _copyMode);
        for (size_t i = 0; i < nodes.size(); ++i)
        {
            nodes[i].second->applyAllValues(*_dest.nodes[i].second, _copyMode);
        }
    }

    struct CompObject
    {
        bool operator()(
            std::pair<char const*, value_ptr<Node>> const& a,
            std::pair<char const*, value_ptr<Node>> const& b) const
        {
            return strcmp(a.first, b.first) < 0;
        }
    };

    Ent::Object Ent::Object::makeInstanceOf() const
    {
        Object out(schema);
        out.instanceOf = instanceOf.makeInstanceOf();
        out.nodes.reserve(size());
        for (auto&& name_node : *this)
        {
            out.nodes.emplace_back(std::get<0>(name_node), std::get<1>(name_node)->makeInstanceOf());
        }
        std::sort(begin(out), end(out), CompObject());
        return out;
    }

    Object Ent::Object::detach() const
    {
        Object out(schema);
        out.nodes.reserve(size());
        for (auto&& name_node : *this)
        {
            out.nodes.emplace_back(std::get<0>(name_node), std::get<1>(name_node)->detach());
        }
        std::sort(begin(out), end(out), CompObject());
        return out;
    }

    void Ent::Object::resetInstanceOf(char const* _prefabNodePath)
    {
        auto const* entlib = schema->rootSchema->entityLib;
        if (_prefabNodePath == nullptr or strlen(_prefabNodePath) == 0)
        {
            Node prefabNode = entlib->loadNode(*schema, json{}, nullptr);
            (*this) = prefabNode.GetRawValue().get<Object>().makeInstanceOf();
            instanceOf.set("");
        }
        else
        {
            auto relPath = entlib->getRelativePath(_prefabNodePath).generic_u8string();
            json nodeData = loadJsonFile(entlib->rawdataPath, _prefabNodePath);
            Node prefabNode = entlib->loadNode(*schema, nodeData, nullptr);
            (*this) = prefabNode.GetRawValue().get<Object>().makeInstanceOf();
            // TODO : Loïc - reset the keyField if there is one
            instanceOf.set(relPath);
        }
    }

    size_t count(Object const& obj, char const* key)
    {
        auto range = std::equal_range(
            begin(obj), end(obj), std::pair<char const*, value_ptr<Node>>{key, nullptr}, CompObject());
        return (size_t)std::distance(range.first, range.second);
    }
    void emplace(Object& obj, std::pair<char const*, Node> const& value)
    {
        auto range = std::equal_range(begin(obj), end(obj), value, CompObject());
        if (range.first == range.second)
        {
            obj.nodes.insert(range.first, value);
        }
    }
    Node const& at(Object const& obj, char const* key)
    {
        auto range = std::equal_range(
            begin(obj), end(obj), std::pair<char const*, value_ptr<Node>>{key, nullptr}, CompObject());
        if (range.first == range.second)
        {
            throw std::logic_error(std::string("Bad key : ") + key);
        }
        else
        {
            return *range.first->second;
        }
    }
    Node& at(Object& obj, char const* key)
    {
        auto range = std::equal_range(
            begin(obj),
            end(obj),
            std::pair<char const*, value_ptr<Node>>{key, value_ptr<Node>()},
            CompObject());
        if (range.first == range.second)
        {
            throw std::logic_error(std::string("Bad key : ") + key);
        }
        else
        {
            return *range.first->second;
        }
    }

    // ************************************* Node *************************************************

    Node::Node(Value val, Subschema const* _schema)
        : schema(_schema)
        , value(std::move(val))
    {
    }

    DataType Node::getDataType() const
    {
        return (DataType)value.which();
    }

    Node* Node::at(char const* _field)
    {
        if (value.is<Object>())
        {
            return &Ent::at(value.get<Object>(), _field);
        }
        throw BadType();
    }
    Node const* Node::at(char const* _field) const
    {
        if (value.is<Object>())
        {
            return &Ent::at(value.get<Object>(), _field);
        }
        throw BadType();
    }
    bool Node::count(char const* _field) const
    {
        if (value.is<Object>())
        {
            return Ent::count(value.get<Object>(), _field) != 0;
        }
        throw BadType();
    }
    Node* Node::at(size_t _index)
    {
        if (value.is<Array>())
        {
            return value.get<Array>().at(_index);
        }
        throw BadType();
    }
    Node const* Node::at(size_t _index) const
    {
        if (value.is<Object>())
        {
            auto iter = begin(value.get<Object>());
            std::advance(iter, _index);
            return &(*iter->second);
        }
        if (value.is<Array>())
        {
            return value.get<Array>().at(_index);
        }
        throw BadType();
    }
    size_t Node::size() const
    {
        if (value.is<Array>())
        {
            return value.get<Array>().size();
        }
        throw BadType();
    }

    tl::optional<size_t> Node::getRawSize(OverrideValueLocation _location) const
    {
        if (value.is<Array>())
        {
            return value.get<Array>().getRawSize(_location);
        }
        throw BadType();
    }

    Node const* Node::getUnionDataWrapper() const
    {
        if (value.is<Union>())
        {
            return value.get<Union>().wrapper.get();
        }
        throw BadType();
    }

    Node* Node::getUnionData()
    {
        if (value.is<Union>())
        {
            return value.get<Union>().getUnionData();
        }
        throw BadType();
    }
    Node const* Node::getUnionData() const
    {
        if (value.is<Union>())
        {
            return value.get<Union>().getUnionData();
        }
        throw BadType();
    }

    char const* Node::getUnionType() const
    {
        if (value.is<Union>())
        {
            return value.get<Union>().getUnionType();
        }
        throw BadType();
    }

    size_t Node::getUnionTypeIndex() const
    {
        if (value.is<Union>())
        {
            return value.get<Union>().typeIndex;
        }
        throw BadType();
    }

    Node* Node::setUnionType(char const* _type)
    {
        if (value.is<Union>())
        {
            return value.get<Union>().setUnionType(*getEntityLib(), _type);
        }
        throw BadType();
    }

    double Node::getFloat() const
    {
        if (value.is<Override<double>>())
        {
            return value.get<Override<double>>().get();
        }
        if (value.is<Override<int64_t>>())
        {
            return static_cast<double>(value.get<Override<int64_t>>().get());
        }
        throw BadType();
    }
    int64_t Node::getInt() const
    {
        if (value.is<Override<int64_t>>())
        {
            return value.get<Override<int64_t>>().get();
        }
        throw BadType();
    }
    char const* Node::getString() const
    {
        if (value.is<Override<String>>())
        {
            return value.get<Override<String>>().get().c_str();
        }
        throw BadType();
    }
    bool Node::getBool() const
    {
        if (value.is<Override<bool>>())
        {
            return value.get<Override<bool>>().get();
        }
        throw BadType();
    }

    EntityRef Node::getEntityRef() const
    {
        if (value.is<Override<EntityRef>>())
        {
            return value.get<Override<EntityRef>>().get();
        }
        throw BadType();
    }

    const Node::Value& Node::GetRawValue() const
    {
        return value;
    }

    void Node::setFloat(double _val)
    {
        value.get<Override<double>>().set(_val);
    }
    void Node::setInt(int64_t _val)
    {
        value.get<Override<int64_t>>().set(_val);
    }
    void Node::setString(char const* _val)
    {
        value.get<Override<String>>().set(_val);
    }
    void Node::setBool(bool _val)
    {
        value.get<Override<bool>>().set(_val);
    }

    void Node::setEntityRef(EntityRef _entityRef)
    {
        value.get<Override<EntityRef>>().set(std::move(_entityRef));
    }

    struct UnSet
    {
        template <typename T>
        void operator()(T& _nodeInternal) const
        {
            return _nodeInternal.unset();
        }

        void operator()(Null&) const
        {
        }
    };

    void Node::unset()
    {
        mapbox::util::apply_visitor(UnSet{}, value);
    }

    struct IsSet
    {
        template <typename T>
        bool operator()(Override<T> const& _ov) const
        {
            return _ov.isSet();
        }

        template <typename U>
        bool operator()(U const& _notOverride) const
        {
            (void*)&_notOverride;
            // throw BadType();
            return true; // Object and Array are always considered as overrided
        }
    };

    bool Node::isSet() const
    {
        return mapbox::util::apply_visitor(IsSet{}, value);
    }

    struct HasDefaultValue
    {
        Subschema const* schema;

        template <typename T>
        bool operator()(Override<T> const& _ov) const
        {
            return (not _ov.hasPrefabValue()) and (not _ov.hasOverride());
        }

        bool operator()(Null const&) const
        {
            return false;
        }

        bool operator()(Array const& _arr) const
        {
            return _arr.hasDefaultValue();
        }

        bool operator()(Object const& _obj) const
        {
            return std::all_of(begin(_obj), end(_obj), [](auto&& name_node) {
                return std::get<1>(name_node)->hasDefaultValue();
            });
        }

        bool operator()(Union const& _un) const
        {
            return _un.wrapper->hasDefaultValue();
        }
    };

    bool Node::hasDefaultValue() const
    {
        return mapbox::util::apply_visitor(HasDefaultValue{schema}, value);
    }

    struct Detach
    {
        Subschema const* schema;

        template <typename T>
        Node operator()(Override<T> const& _ov) const
        {
            return Node(_ov.detach(), schema);
        }

        Node operator()(Null const& _val) const
        {
            (void*)&_val; // Null contains nothing so it is not needed
            return Node(Null{}, schema);
        }

        Node operator()(Array const& _arr) const
        {
            return Node(_arr.detach(), schema);
        }

        Node operator()(Object const& _obj) const
        {
            return Node(_obj.detach(), schema);
        }

        Node operator()(Union const& _un) const
        {
            Union detUnion{};
            detUnion.schema = _un.schema;
            detUnion.wrapper = _un.wrapper->detach();
            detUnion.metaData = _un.metaData;
            detUnion.typeIndex = _un.typeIndex;
            return Node(std::move(detUnion), schema);
        }
    };

    Node Node::detach() const
    {
        return mapbox::util::apply_visitor(Detach{schema}, value);
    }

    struct MakeInstanceOf
    {
        Subschema const* schema;

        template <typename T>
        Node operator()(Override<T> const& _ov) const
        {
            return Node(_ov.makeInstanceOf(), schema);
        }

        Node operator()(Null const& _val) const
        {
            (void*)&_val; // Null contains nothing so it is not needed
            return Node(Null{}, schema);
        }

        Node operator()(Array const& _arr) const
        {
            return Node(_arr.makeInstanceOf(), schema);
        }

        Node operator()(Object const& _obj) const
        {
            return Node(_obj.makeInstanceOf(), schema);
        }

        Node operator()(Union const& _un) const
        {
            Union detUnion{};
            ENTLIB_ASSERT(_un.schema != nullptr);
            detUnion.schema = _un.schema;
            if (_un.wrapper != nullptr)
            {
                detUnion.wrapper = _un.wrapper->makeInstanceOf();
            }
            detUnion.metaData = _un.metaData;
            detUnion.typeIndex = _un.typeIndex;
            return Node(std::move(detUnion), schema);
        }
    };

    Node Node::makeInstanceOf() const
    {
        return mapbox::util::apply_visitor(MakeInstanceOf{schema}, value);
    }

    struct HasOverride
    {
        Subschema const* schema;

        template <typename T>
        bool operator()(Override<T> const& _ov) const
        {
            return _ov.isSet();
        }

        bool operator()(Null const& _val) const
        {
            (void*)&_val; // Null contains nothing so it is not needed
            return false;
        }

        bool operator()(Array const& _arr) const
        {
            return _arr.hasOverride();
        }

        bool operator()(Object const& _obj) const
        {
            if (_obj.instanceOf.hasOverride())
            {
                return true;
            }
            for (auto&& name_node : _obj)
            {
                if (std::get<1>(name_node)->hasOverride())
                {
                    return true;
                }
            }
            return false;
        }

        bool operator()(Union const& _un) const
        {
            return _un.wrapper->hasOverride();
        }
    };

    bool Node::hasOverride() const
    {
        return mapbox::util::apply_visitor(HasOverride{schema}, value);
    }

    struct HasPrefabValue
    {
        Subschema const* schema;

        template <typename T>
        bool operator()(Override<T> const& _ov) const
        {
            return _ov.hasPrefabValue();
        }

        bool operator()(Null const& _val) const
        {
            (void*)&_val; // Null contains nothing so it is not needed
            return false;
        }

        bool operator()(Array const& _arr) const
        {
            return _arr.hasPrefabValue();
        }

        bool operator()(Object const& _obj) const
        {
            if (_obj.instanceOf.hasPrefabValue())
            {
                return true;
            }
            for (auto&& name_node : _obj)
            {
                if (std::get<1>(name_node)->hasPrefabValue())
                {
                    return true;
                }
            }
            return false;
        }

        bool operator()(Union const& _un) const
        {
            return _un.wrapper->hasPrefabValue();
        }
    };

    bool Node::hasPrefabValue() const
    {
        return mapbox::util::apply_visitor(HasPrefabValue{schema}, value);
    }

    bool Node::matchValueSource(OverrideValueSource _source) const
    {
        return not(
            _source == OverrideValueSource::OverrideOrPrefab and hasDefaultValue()
            or _source == OverrideValueSource::Override and not hasOverride());
    }

    std::vector<char const*> Node::getFieldNames() const
    {
        if (value.is<Object>())
        {
            std::vector<char const*> fields;
            for (auto&& f : value.get<Object>())
            {
                fields.push_back(f.first);
            }
            return fields;
        }
        throw BadType();
    }

    char const* Node::getInstanceOf() const
    {
        if (value.is<Object>())
        {
            return value.get<Object>().instanceOf.get().c_str();
        }
        throw BadType();
    }

    std::vector<Node const*> Node::getItems() const
    {
        if (value.is<Array>())
        {
            return value.get<Array>().getItems();
        }
        throw BadType();
    }

    Node* Node::push()
    {
        if (value.is<Array>())
        {
            auto& arr = value.get<Array>();
            if (arr.hasKey())
            {
                throw BadArrayType("Can't 'push' in a map or set. Use 'mapInsert'.");
            }
            return arr.arrayPush();
        }
        throw BadType();
    }
    void Node::pop()
    {
        if (value.is<Array>())
        {
            auto&& arr = value.get<Array>();
            if (arr.hasKey())
            {
                throw BadArrayType("Can't call 'pop' on map/set array");
            }
            if (arr.isTuple())
            {
                throw BadArrayType("Can't call 'pop' on pair/tuple");
            }
            arr.pop();
        }
        else
        {
            throw BadType();
        }
    }

    void Node::clear()
    {
        if (value.is<Array>())
        {
            auto&& arr = value.get<Array>();
            if (arr.isTuple())
            {
                throw BadArrayType("Can't call 'clear' on pair/tuple");
            }
            arr.clear();
        }
        else
        {
            throw BadType();
        }
    }

    bool Node::empty() const
    {
        if (value.is<Array>())
        {
            return value.get<Array>().empty();
        }
        throw BadType();
    }

    bool Node::mapErase(char const* _key)
    {
        checkMap("mapErase");
        if (not value.get<Array>().canErase())
        {
            throw BadArrayType(format("Can call 'mapErase' only on map and set of union").c_str());
        }
        return value.get<Array>().mapErase(_key);
    }

    Node* Node::mapGet(char const* _key)
    {
        checkMap("mapGet");
        return value.get<Array>().mapGet(_key);
    }
    Node const* Node::mapGet(char const* _key) const
    {
        checkMap("mapGet");
        return value.get<Array>().mapGet(_key);
    }
    bool Node::mapErase(int64_t _key)
    {
        checkMap("mapErase");
        return value.get<Array>().mapErase(_key);
    }
    Node* Node::mapGet(int64_t _key)
    {
        checkMap("mapGet");
        return value.get<Array>().mapGet(_key);
    }
    Node const* Node::mapGet(int64_t _key) const
    {
        checkMap("mapGet");
        return value.get<Array>().mapGet(_key);
    }

    Node const* Node::mapInsert(int64_t _key)
    {
        checkMap("mapInsert");
        return value.get<Array>().mapInsert(_key);
    }

    Node const* Node::mapInsert(char const* _key)
    {
        checkMap("mapInsert");
        return value.get<Array>().mapInsert(_key);
    }

    void Node::checkMap(char const* _calledMethod) const
    {
        if (not value.is<Array>())
        {
            throw BadType();
        }
        if (not value.get<Array>().hasKey())
        {
            throw BadArrayType(format("Can call '%s' only on map/set", _calledMethod).c_str());
        }
    }

    bool Node::isMapOrSet() const
    {
        if (not value.is<Array>())
        {
            return false;
        }
        return value.get<Array>().hasKey();
    }

    DataType Node::getKeyType() const
    {
        checkMap("getKeyType");
        return value.get<Array>().getKeyType();
    }

    std::vector<String> Node::getKeysString() const
    {
        checkMap("getKeysString");
        auto const keyType = Node::getKeyType();
        if (keyType != Ent::DataType::string and keyType != Ent::DataType::entityRef)
        {
            throw ContextException("Can't call 'getKeysString' if key is not string or entityRef");
        }
        auto const& arr = value.get<Array>();
        auto const arrSize = arr.size();
        std::vector<String> keys;
        keys.reserve(arrSize);
        for (size_t i = 0; i < arrSize; ++i)
        {
            keys.push_back(arr.getChildKey(arr.at(i)).get<String>());
        }
        return keys;
    }

    std::vector<int64_t> Node::getKeysInt() const
    {
        checkMap("getMapKeysInt");
        auto const keyType = Node::getKeyType();
        if (keyType != Ent::DataType::integer)
        {
            throw ContextException("Can't call 'getKeysInt' if key is not integer");
        }
        auto const& arr = value.get<Array>();
        auto const arrSize = arr.size();
        std::vector<int64_t> keys;
        keys.reserve(arrSize);
        for (size_t i = 0; i < arrSize; ++i)
        {
            keys.push_back(arr.getChildKey(arr.at(i)).get<int64_t>());
        }
        return keys;
    }

    struct IsDefault
    {
        Subschema const* schema;

        template <typename T>
        bool operator()(Override<T> const& _ov) const
        {
            return not _ov.hasPrefabValue() and not _ov.hasOverride();
        }

        bool operator()(Null const& _val) const
        {
            (void*)&_val; // Null contains nothing so it is not needed
            return false;
        }

        bool operator()(Array const& _arr) const
        {
            (void*)&_arr;
            return false;
        }

        bool operator()(Object const& _obj) const
        {
            (void*)&_obj;
            return false;
        }

        bool operator()(Union const&) const
        {
            return false;
        }
    };

    bool Node::isDefault() const
    {
        return mapbox::util::apply_visitor(IsDefault{schema}, value);
    }

    json Node::toJson(
        OverrideValueSource _dumpedValueSource,
        bool _superKeyIsTypeName,
        std::function<void(EntityRef&)> const& _entityRefPreProc,
        bool _saveUnionIndex) const
    {
        return EntityLib::dumpNode(
            *getSchema(),
            *this,
            _dumpedValueSource,
            _superKeyIsTypeName,
            _entityRefPreProc,
            _saveUnionIndex);
    }

    void Node::saveNode(std::filesystem::path const& _path) const
    {
        json node = toJson();
        node["$schema"] = getSchema()->name;

        std::filesystem::path path = getEntityLib()->getAbsolutePath(_path);
        std::ofstream file(path);
        if (not file.is_open())
        {
            throw FileSystemError(
                "Trying to open file for write", getEntityLib()->rawdataPath, _path);
        }
        file << node.dump(4);
    }

    double Node::getDefaultFloat() const
    {
        return getRawFloat(OverrideValueLocation::Default).value();
    }
    int64_t Node::getDefaultInt() const
    {
        return getRawInt(OverrideValueLocation::Default).value();
    }
    char const* Node::getDefaultString() const
    {
        return getRawString(OverrideValueLocation::Default).value();
    }
    bool Node::getDefaultBool() const
    {
        return getRawBool(OverrideValueLocation::Default).value();
    }

    tl::optional<double> Node::getRawFloat(OverrideValueLocation _location) const
    {
        if (value.is<Override<double>>())
        {
            return value.get<Override<double>>().getRaw(_location);
        }
        if (value.is<Override<int64_t>>())
        {
            auto intValue = value.get<Override<int64_t>>().getRaw(_location);
            return intValue.has_value() ?
                       tl::optional<double>{static_cast<double>(intValue.value())} :
                       tl::nullopt;
        }
        throw BadType();
    }

    tl::optional<int> Node::getRawInt(OverrideValueLocation _location) const
    {
        if (value.is<Override<int64_t>>())
        {
            return value.get<Override<int64_t>>().getRaw(_location);
        }
        throw BadType();
    }

    tl::optional<char const*> Node::getRawString(OverrideValueLocation _location) const
    {
        if (value.is<Override<String>>())
        {
            auto strValue = value.get<Override<String>>().getRaw(_location);
            return strValue.has_value() ? tl::optional<char const*>{strValue.value().c_str()} :
                                          tl::nullopt;
        }
        throw BadType();
    }

    tl::optional<bool> Node::getRawBool(OverrideValueLocation _location) const
    {
        if (value.is<Override<bool>>())
        {
            auto boolValue = value.get<Override<bool>>().getRaw(_location);
            return boolValue.has_value() ? tl::optional<bool>{boolValue} : tl::nullopt;
        }
        throw BadType();
    }

    char const* Node::getTypeName() const
    {
        if (schema == nullptr)
        {
            return nullptr;
        }
        return schema->name.c_str();
    }

    Subschema const* Node::getSchema() const
    {
        return schema;
    }

    struct ComputeMem
    {
        MemoryProfiler& prof;
        template <typename T>
        void operator()(Override<T> const& _ov) const
        {
            return _ov.computeMemory(prof);
        }

        void operator()(Null const&) const
        {
        }

        void operator()(Array const& _arr) const
        {
            return _arr.computeMemory(prof);
        }

        void operator()(Object const& _obj) const
        {
            prof.addMem("Object", _obj.nodes.capacity() * sizeof(_obj.front()));
            _obj.instanceOf.computeMemory(prof);
            for (auto&& name_node : _obj)
            {
                std::get<1>(name_node)->computeMemory(prof);
                prof.addMem("Object::value_ptr", sizeof(Ent::Node));
            }
            prof.addNodes(_obj.size());
        }

        void operator()(Union const& _un) const
        {
            prof.currentComp.push_back(_un.getUnionType());
            _un.computeMemory(prof);
            prof.currentComp.pop_back();
        }
    };

    void Node::computeMemory(MemoryProfiler& prof) const
    {
        mapbox::util::apply_visitor(ComputeMem{prof}, value);
    }

    void Ent::Node::setInstanceOf(char const* _prefabNodePath)
    {
        resetInstanceOf(_prefabNodePath);
    }

    void Ent::Node::resetInstanceOf(char const* _prefabNodePath)
    {
        if (not value.is<Object>())
        {
            throw BadType();
        }
        value.get<Object>().resetInstanceOf(_prefabNodePath);
    }

    void Ent::Node::resetInstanceOf()
    {
        if (not value.is<Object>())
        {
            throw BadType();
        }
        value.get<Object>().resetInstanceOf(nullptr);
    }

    void Ent::Entity::changeInstanceOf(char const* _newPrefab)
    {
        const auto cloned = clone();
        resetInstanceOf(_newPrefab);
        cloned->applyAllValuesButPrefab(*this, CopyMode::MinimalOverride);
    }

    EntityLib* Ent::Node::getEntityLib() const
    {
        return schema->rootSchema->entityLib;
    }

    struct ApplyToPrefab
    {
        Node::Value& dest;
        CopyMode copyMode;

        template <typename T>
        void operator()(T const& _value) const
        {
            _value.applyAllValues(dest.get<T>(), copyMode);
        }

        void operator()(Null const&) const
        {
        }
    };

    void Ent::Node::applyAllValues(Node& _dest, CopyMode _copyMode) const
    {
        if (value.is<Object>())
        {
            auto const& object = value.get<Object>();
            if (object.instanceOf.isSet()) // 'this' has an InstanceOf
            {
                if (_dest.getInstanceOf() == nullptr
                    or strcmp(object.instanceOf.get().c_str(), _dest.getInstanceOf())
                           != 0) // Not the same InstanceOf
                {
                    _dest.resetInstanceOf(object.instanceOf.get().c_str());
                }
            }
        }

        ENTLIB_ASSERT(schema == _dest.schema);
        mapbox::util::apply_visitor(ApplyToPrefab{_dest.value, _copyMode}, value);
    }

    void destroyAndFree(Node* ptr)
    {
        auto& pool = ptr->getSchema()->rootSchema->entityLib->nodePool;
        ptr->~Node();
        pool.free(ptr);
    }

    Pool<Node>& getPool(Node const* ptr)
    {
        ENTLIB_ASSERT(ptr);
        ENTLIB_ASSERT(ptr->getSchema());
        return ptr->getEntityLib()->nodePool;
    }

    // ********************************* SubSceneComponent ****************************************
    SubSceneComponent::SubSceneComponent(
        EntityLib const* _entlib, size_t _index, std::unique_ptr<Scene> _embedded)
        : index(_index)
        , embedded(std::move(_embedded))
    {
        if (embedded == nullptr)
        {
            embedded = std::make_unique<Scene>(_entlib);
        }
    }

    // ********************************* Entity ***************************************************

    static Ent::Node makeDefaultActorStatesField(EntityLib const& _entlib)
    {
        Ent::Subschema const& actorStatesSchema =
            AT(_entlib.schema.schema.allDefinitions, actorStatesSchemaName);
        return Node{Array{&_entlib, &actorStatesSchema}, &actorStatesSchema};
    }

    Entity::Entity(EntityLib const& _entlib)
        : entlib(&_entlib)
        , name(std::string())
        , actorStates(Ent::makeDefaultActorStatesField(_entlib))
        , color(Ent::makeDefaultColorField(_entlib))
        , thumbnail(std::string())
        , instanceOf(std::string())
        , maxActivationLevel(Ent::ActivationLevel::Started)
    {
    }

    Entity::Entity(
        EntityLib const& _entlib,
        Override<String> _name,
        std::map<std::string, Component> _components,
        std::set<std::string> _removedComponents,
        std::unique_ptr<SubSceneComponent> _subSceneComponent,
        Node _actorStates,
        Node _color,
        Override<String> _thumbnail,
        Override<String> _instanceOf,
        Override<Ent::ActivationLevel> _maxActivationLevel,
        bool _hasASuper)
        : entlib(&_entlib)
        , name(std::move(_name))
        , components(std::move(_components))
        , removedComponents(std::move(_removedComponents))
        , subSceneComponent(std::move(_subSceneComponent))
        , actorStates(std::move(_actorStates))
        , color(std::move(_color))
        , thumbnail(std::move(_thumbnail))
        , instanceOf(std::move(_instanceOf))
        , maxActivationLevel(_maxActivationLevel)
        , hasASuper(_hasASuper)
    {
        updateSubSceneOwner();
    }

    std::unique_ptr<Entity> Entity::clone() const
    {
        std::map<std::string, Component> instComponents;
        std::unique_ptr<SubSceneComponent> instSubSceneComponent;

        for (auto&& name_comp : components)
        {
            instComponents.emplace(name_comp.first, name_comp.second);
        }
        if (subSceneComponent != nullptr)
        {
            instSubSceneComponent = subSceneComponent->clone();
        }

        std::unique_ptr<Entity> ent = std::make_unique<Entity>(
            *entlib,
            name,
            std::move(instComponents),
            removedComponents,
            std::move(instSubSceneComponent),
            actorStates,
            color,
            thumbnail,
            instanceOf,
            maxActivationLevel);
        ent->hasASuper = hasASuper;
        return ent;
    }

    char const* Entity::getName() const
    {
        return name.get().c_str();
    }
    void Entity::setName(Ent::String _name)
    {
        if (name.get() == _name)
        {
            return;
        }
        if (hasASuper)
        {
            throw ContextException(
                "Setting name : %s. A SubEntity of an instance which override a SubEntity in a "
                "prefab can't be renamed. Check the canBeRenamed method.",
                _name.c_str());
        }
        name.set(std::move(_name));
    }
    bool Entity::canBeRenamed() const
    {
        return not hasASuper;
    }
    bool Entity::newInTheScene() const
    {
        return not hasASuper;
    }
    void Entity::setCanBeRenamed(bool _can)
    {
        hasASuper = not _can;
    }

    char const* Entity::getInstanceOf() const
    {
        return instanceOf.isDefault() ? nullptr : instanceOf.get().c_str();
    }

    ActivationLevel Entity::getMaxActivationLevel() const
    {
        return maxActivationLevel.get();
    }

    void Entity::setMaxActivationLevel(ActivationLevel _level)
    {
        maxActivationLevel.set(_level);
    }

    char const* Entity::getThumbnail() const
    {
        return thumbnail.isDefault() ? nullptr : thumbnail.get().c_str();
    }
    void Entity::setThumbnail(Ent::String _thumbPath)
    {
        thumbnail.set(std::move(_thumbPath));
    }
    std::array<double, 4> Entity::getColor() const
    {
        std::array<double, 4> col{};
        for (size_t i = 0; i < 4; ++i)
        {
            col[i] = color.at(i)->getFloat();
        }
        return col;
    }
    void Entity::setColor(std::array<double, 4> _color)
    {
        for (size_t i = 0; i < 4; ++i)
        {
            color.at(i)->setFloat(_color[i]);
        }
    }
    Component* Entity::addComponent(char const* _type)
    {
        if (entlib->schema.components.count(_type) == 0)
        {
            ENTLIB_LOG_ERROR("Unknown Component type : %s", _type);
            return nullptr;
        }
        if (entlib->componentDependencies.count(_type) != 0) // Could be an editor componant
        {
            for (auto&& dep : AT(entlib->componentDependencies, _type))
            {
                addComponent(dep.c_str());
            }
        }
        Ent::Subschema const& compSchema = *AT(entlib->schema.components, _type);
        Ent::Component comp{
            json(), false, _type, entlib->loadNode(compSchema, json(), nullptr), 1, components.size()};
        removedComponents.erase(_type);
        auto iter_bool = components.emplace(_type, std::move(comp));
        return &(iter_bool.first->second);
    }
    Component const* Entity::getComponent(char const* _type) const
    {
        auto iter = components.find(_type);
        return iter == components.end() ? nullptr : &(iter->second);
    }
    Component* Entity::getComponent(char const* _type)
    {
        auto iter = components.find(_type);
        return iter == components.end() ? nullptr : &(iter->second);
    }
    void Entity::removeComponent(char const* _type)
    {
        // TODO : Use dependencies
        auto iter = components.find(_type);
        if (iter != end(components))
        {
            Component const& comp = iter->second;
            if (comp.hasPrefab)
            {
                removedComponents.insert(_type);
            }
            components.erase(iter);
        }
    }

    std::vector<char const*> Entity::getComponentTypes() const
    {
        std::vector<char const*> types;
        for (auto&& type_comp : components)
        {
            types.push_back(type_comp.first.c_str());
        }
        return types;
    }

    std::map<std::string, Component> const& Entity::getComponents() const
    {
        return components;
    }

    SubSceneComponent const* Entity::getSubSceneComponent() const
    {
        if (subSceneComponent != nullptr)
        {
            return &(*subSceneComponent);
        }
        return nullptr;
    }

    SubSceneComponent* Entity::getSubSceneComponent()
    {
        if (subSceneComponent != nullptr)
        {
            return &(*subSceneComponent);
        }
        return nullptr;
    }

    SubSceneComponent* Entity::addSubSceneComponent()
    {
        if (subSceneComponent == nullptr)
        {
            subSceneComponent = std::make_unique<SubSceneComponent>(entlib);
            removedComponents.erase("SubScene");
            subSceneComponent->embedded->setOwnerEntity(this);
        }
        return &(*subSceneComponent);
    }

    void Entity::removeSubSceneComponent()
    {
        if (subSceneComponent != nullptr)
        {
            subSceneComponent.reset();
            removedComponents.insert("SubScene");
        }
    }

    std::unique_ptr<Entity> Entity::makeInstanceOf() const
    {
        std::map<std::string, Component> instComponents;
        std::unique_ptr<SubSceneComponent> instSubSceneComponent;

        for (auto&& name_comp : components)
        {
            instComponents.emplace(name_comp.first, name_comp.second.makeInstanceOf());
        }
        if (subSceneComponent != nullptr)
        {
            instSubSceneComponent = subSceneComponent->makeInstanceOf();
        }

        return std::make_unique<Entity>(
            *entlib,
            name.makeInstanceOf(),
            std::move(instComponents),
            std::set<std::string>{},
            std::move(instSubSceneComponent),
            actorStates.makeInstanceOf(),
            color.makeInstanceOf(),
            thumbnail.makeInstanceOf(),
            instanceOf.makeInstanceOf(),
            maxActivationLevel.makeInstanceOf(),
            true // It is an instance so it is not a new entity in the scene
        );
    }

    bool Entity::hasOverride() const
    {
        //    If "InstanceOf" is set, this entity "hasOverride"
        if (name.isSet() or color.hasOverride() or thumbnail.isSet() or actorStates.hasOverride()
            or instanceOf.hasOverride())
        {
            return true;
        }
        for (auto&& name_comp : components)
        {
            if (name_comp.second.hasOverride())
            {
                return true;
            }
        }
        return subSceneComponent != nullptr and subSceneComponent->hasOverride();
    }

    void Entity::setParentScene(Scene* _scene)
    {
        parentScene = _scene;
    }

    void Entity::setInstanceOf(std::string const& _prefab)
    {
        resetInstanceOf(_prefab.c_str());
    }

    void Entity::resetInstanceOf(char const* _prefab)
    {
        std::shared_ptr<Ent::Entity const> templ;
        std::string prefab;
        if (_prefab == nullptr or strlen(_prefab) == 0)
        {
            templ = std::make_shared<Ent::Entity const>(*entlib);
        }
        else
        {
            prefab = entlib->getRelativePath(_prefab).generic_u8string();
            templ = entlib->loadEntityReadOnly(prefab.c_str(), nullptr);
        }
        components.clear();
        removedComponents.clear();
        for (auto const& type_comp : templ->getComponents())
        {
            auto const& cmpType = std::get<0>(type_comp);
            auto const& superComp = std::get<1>(type_comp);
            components.emplace(
                cmpType,
                Ent::Component{
                    superComp.rawData,
                    true,
                    cmpType,
                    superComp.root.makeInstanceOf(),
                    superComp.version,
                    superComp.index,
                });
        }
        auto prevName = name;
        name = templ->getNameValue().makeInstanceOf();
        if (not canBeRenamed()) // Name is the key to override entities, so it can't be changed
            name.set(prevName.get());
        subSceneComponent = templ->getSubSceneComponent() != nullptr ?
                                templ->getSubSceneComponent()->makeInstanceOf() :
                                nullptr;
        actorStates = templ->getActorStates().makeInstanceOf();
        color = templ->getColorValue().makeInstanceOf();
        thumbnail = templ->getThumbnailValue().makeInstanceOf();
        instanceOf = templ->getInstanceOfValue().makeOverridedInstanceOf(prefab.c_str());
        maxActivationLevel = templ->getMaxActivationLevelValue().makeInstanceOf();

        updateSubSceneOwner();
    }

    Scene* Entity::getParentScene() const
    {
        return parentScene;
    }

    static std::tuple<std::vector<std::string>, Entity*, Scene*> getAbsolutePathReversed(Entity* _entity)
    {
        Entity* current = _entity;
        Entity* rootEntity = nullptr;
        Scene* rootScene = nullptr;
        std::vector<std::string> path;
        while (current != nullptr)
        {
            path.emplace_back(current->getName());
            rootEntity = current;
            rootScene = current->getParentScene();
            current = current->getParentScene() != nullptr ?
                          current->getParentScene()->getOwnerEntity() :
                          nullptr;
        }
        return {std::move(path), rootEntity, rootScene};
    }

    EntityRef Entity::makeEntityRef(Entity& _entity)
    {
        // get the two absolute path
        auto&& thisPathInfos = getAbsolutePathReversed(this);
        auto&& entityPathInfos = getAbsolutePathReversed(&_entity);

        Entity* thisRootEntity = std::get<1>(thisPathInfos);
        Entity* entityRootEntity = std::get<1>(entityPathInfos);
        Scene* thisRootScene = std::get<2>(thisPathInfos);
        Scene* entityRootScene = std::get<2>(entityPathInfos);

        // entities should either share a common root scene
        // or a common root entity if they are in a .entity (i.e there is no root scene)
        if (thisRootScene != entityRootScene
            or thisRootEntity == nullptr and thisRootEntity != entityRootEntity)
        {
            // cannot reference unrelated entities
            return {};
        }

        auto&& thisPath = std::get<0>(thisPathInfos);
        auto&& entityPath = std::get<0>(entityPathInfos);

        std::string relativePath = computeRelativePath(thisPath, std::move(entityPath), false);

        return {relativePath};
    }

    /// @tparam E is Entity or Entity const.
    template <typename E>
    static auto getSubScene(E* _entity) -> decltype(_entity->getSubSceneComponent()->embedded.get())
    {
        if (auto* subScene = _entity->getSubSceneComponent())
        {
            return subScene->embedded.get();
        }
        return nullptr;
    }

    static Entity* findChild(Scene* _scene, const std::string& _name)
    {
        auto&& children = _scene->getObjects();
        const auto found = std::find_if(children.begin(), children.end(), [&_name](auto& childPtr) {
            return childPtr->getName() == _name;
        });
        return found == children.end() ? nullptr : found->get();
    }

    /// @tparam E is Entity or Entity const.
    template <typename E>
    static E*
    resolveEntityRefRecursive(E* _current, Scene* _up, Scene* _down, std::vector<std::string>& _path)
    {
        auto& head = _path.front();

        if (head == "..")
        {
            // go up in hierarchy
            if (_up == nullptr)
            {
                // broken ref
                return nullptr;
            }
            _current = _up->getOwnerEntity();
            _down = _up;
            _up = _current == nullptr ? nullptr : _current->getParentScene();
        }
        else if (head != ".")
        {
            // go down in child hierarchy named "head"
            if (_down == nullptr)
            {
                // broken ref
                return nullptr;
            }
            _current = findChild(_down, head);
            _up = _down;
            _down = _current == nullptr ? nullptr : getSubScene(_current);
        }
        _path.erase(_path.begin());
        if (_path.empty())
        {
            return _current;
        }
        return resolveEntityRefRecursive(_current, _up, _down, _path);
    }

    /// @tparam E is Entity or Entity const.
    template <typename E>
    E* resolveEntityRefImpl(E* _current, const EntityRef& _entityRef)
    {
        if (_entityRef.entityPath.empty())
        {
            // empty ref
            return nullptr;
        }

        // split around '/'
        std::vector<std::string> parts = splitString(_entityRef.entityPath.c_str(), '/');

        Scene* down = getSubScene(_current);
        Scene* up = _current->getParentScene();

        return resolveEntityRefRecursive(_current, up, down, parts);
    }

    Entity* Entity::resolveEntityRef(const EntityRef& _entityRef)
    {
        return resolveEntityRefImpl(this, _entityRef);
    }

    Entity const* Entity::resolveEntityRef(const EntityRef& _entityRef) const
    {
        return resolveEntityRefImpl(this, _entityRef);
    }

    void Entity::updateSubSceneOwner()
    {
        if (auto* subScene = getSubSceneComponent())
        {
            subScene->embedded->setOwnerEntity(this);
        }
    }

    // ********************************* Scene ***************************************************

    Scene::Scene(EntityLib const* _entitylib)
        : entlib(_entitylib)
    {
    }

    Scene::Scene(std::vector<std::unique_ptr<Entity>> _entities)
        : objects(std::move(_entities))
    {
        updateChildrenContext();
    }

    void Scene::addEntity(std::unique_ptr<Entity>&& _entity)
    {
        _entity->setParentScene(this);
        objects.emplace_back(std::move(_entity));
    }

    std::vector<std::unique_ptr<Entity>> const& Scene::getObjects() const
    {
        return objects;
    }

    Entity const* Scene::getEntity(size_t index) const
    {
        if (index >= objects.size())
        {
            return nullptr;
        }
        return objects.at(index).get();
    }

    Entity* Scene::getEntity(size_t index)
    {
        if (index >= objects.size())
        {
            return nullptr;
        }
        return objects.at(index).get();
    }

    size_t Scene::entityCount() const
    {
        return objects.size();
    }

    std::vector<std::unique_ptr<Entity>> Scene::releaseAllEntities()
    {
        std::vector<std::unique_ptr<Entity>> freeEntities;
        for (auto&& ent : objects)
        {
            ent->setParentScene(nullptr);
            freeEntities.emplace_back(std::move(ent));
        }
        objects.clear();
        return freeEntities;
    }

    Entity* Scene::resolveEntityRef(const EntityRef& _entityRef)
    {
        if (_entityRef.entityPath.empty())
        {
            // empty ref
            return nullptr;
        }

        // split around '/'
        std::vector<std::string> parts = splitString(_entityRef.entityPath.c_str(), '/');

        Entity* current = getOwnerEntity();
        Scene* down = this;
        Scene* up = current == nullptr ? nullptr : current->getParentScene();

        return resolveEntityRefRecursive(current, up, down, parts);
    }

    Entity* Scene::findEntityByPath(const std::string& _path)
    {
        return resolveEntityRef({_path});
    }

    std::unique_ptr<Scene> Scene::makeInstanceOf() const
    {
        std::vector<std::unique_ptr<Entity>> instanceEntities;
        auto scene = std::make_unique<Scene>(entlib);
        for (auto const& ent : objects)
        {
            instanceEntities.emplace_back(ent->makeInstanceOf());
            instanceEntities.back()->setParentScene(scene.get());
        }
        scene->objects = std::move(instanceEntities);
        return scene;
    }

    std::unique_ptr<Scene> Scene::clone() const
    {
        std::vector<std::unique_ptr<Entity>> instanceEntities;
        auto scene = std::make_unique<Scene>(entlib);
        for (auto const& ent : objects)
        {
            instanceEntities.emplace_back(ent->clone());
            instanceEntities.back()->setParentScene(scene.get());
        }
        scene->objects = std::move(instanceEntities);
        return scene;
    }

    bool Scene::hasOverride() const
    {
        for (std::unique_ptr<Entity> const& ent : objects)
        {
            if (ent->hasOverride() or ent->newInTheScene())
            {
                return true;
            }
        }
        return false;
    }

    Entity* Scene::getOwnerEntity() const
    {
        return ownerEntity;
    }

    void Scene::setOwnerEntity(Entity* entity)
    {
        ownerEntity = entity;
    }

    void Scene::applyAllValues(Scene& _dest, CopyMode _copyMode) const
    {
        std::map<std::string, Entity*> destMap;
        for (auto&& obj : _dest.objects)
        {
            destMap.emplace(obj->getName(), obj.get());
        }
        for (auto&& ent : objects)
        {
            auto destIter = destMap.find(ent->getName());
            if (destIter != destMap.end()) // Preserved Entity
            {
                ent->applyAllValues(*destIter->second, _copyMode);
                destMap.erase(destIter);
            }
            else // Entity just added
            {
                _dest.addEntity(ent->clone());
            }
        }
        ENTLIB_ASSERT_MSG(destMap.empty(), "Can't handle removed entities for now");
    }

    void Scene::updateChildrenContext()
    {
        for (auto& childEntityPtr : objects)
        {
            childEntityPtr->setParentScene(this);
        }
    }

} // namespace Ent

// ********************************** Load/Save ***********************************************

using Ent::String;

struct MergeMapOverride
{
    Ent::Subschema const& _nodeSchema;
    json const& _data;
    Ent::Node const* _super;
    json const* _default;
    Ent::EntityLib const* entlib;

    // Merge the instance array/map/set with the prefab array/map/set and return the resulting Ent::Array
    template <typename GetKeyJson, typename GetKeyNode, typename DoRemoveElement>
    Ent::Array operator()(
        GetKeyJson&& getKeyJson, ///< Function to get the key in the json (instance)
        GetKeyNode&& getKeyNode, ///< Function to get the key in the Node (prefab)
        DoRemoveElement&& doRemove)
    {
        using namespace Ent;

        auto&& meta = _nodeSchema.meta.get<Ent::Subschema::ArrayMeta>();
        bool const ordered = meta.ordered;

        // Make a map key=>item of the instance array
        using KeyType = std::remove_reference_t<decltype(getKeyJson(json()))>;
        std::map<KeyType, json const*> instancePropMap;
        for (auto const& item : _data)
        {
            instancePropMap.emplace(getKeyJson(item), &item);
        }
        struct NodeWrapper
        {
            //TODO : Add default values when C++17
            Node node;
            OverrideValueLocation loc;
            bool removed;

            NodeWrapper(Node _node, OverrideValueLocation _loc, bool _removed)
                : node(std::move(_node))
                , loc(_loc)
                , removed(_removed)
            {
            }
        };
        std::vector<std::pair<KeyType, NodeWrapper>> result;
        if (_super != nullptr)
        {
            size_t index = 0;
            // Load all Nodes from the _super (overriden or not)
            for (Ent::Node const* subSuper : _super->getItems())
            {
                json const* subDefault = _default == nullptr ? nullptr : &_default->at(index);
                KeyType key = getKeyNode(subSuper);
                auto loc = subDefault != nullptr ? OverrideValueLocation::Default :
                                                   OverrideValueLocation::Prefab;
                if (instancePropMap.count(key)) // Overriden in instance
                {
                    Ent::Node tmpNode = entlib->loadNode(
                        _nodeSchema.singularItems->get(), *instancePropMap[key], subSuper, subDefault);
                    if (not doRemove(*instancePropMap[key]))
                    {
                        result.emplace_back(key, NodeWrapper{std::move(tmpNode), loc, false});
                    }
                    else
                    {
                        result.emplace_back(key, NodeWrapper{std::move(tmpNode), loc, true});
                    }
                    instancePropMap.erase(key); // Later we need to know which item are NOT in the prefab
                }
                else // Not overriden
                {
                    Ent::Node tmpNode = entlib->loadNode(
                        _nodeSchema.singularItems->get(), json(), subSuper, subDefault);
                    ENTLIB_ASSERT(tmpNode.hasOverride() == false);
                    result.emplace_back(key, NodeWrapper{std::move(tmpNode), loc, false});
                }
                ++index;
            }
        }
        else if (_default != nullptr)
        {
            size_t index = 0;
            // Load all Nodes from the _default (overriden or not)
            for (json const& subDefault : *_default)
            {
                json const& key = getKeyJson(subDefault);
                if (instancePropMap.count(key)) // Overriden in instance
                {
                    Ent::Node tmpNode = entlib->loadNode(
                        _nodeSchema.singularItems->get(), *instancePropMap[key], nullptr, &subDefault);
                    bool const isRemoved = doRemove(*instancePropMap[key]);
                    result.emplace_back(
                        key,
                        NodeWrapper{std::move(tmpNode), OverrideValueLocation::Default, isRemoved});
                    instancePropMap.erase(key); // Later we need to know which item are NOT in the prefab
                }
                else // Not overriden
                {
                    Ent::Node tmpNode = entlib->loadNode(
                        _nodeSchema.singularItems->get(), json(), nullptr, &subDefault);
                    ENTLIB_ASSERT(tmpNode.hasOverride() == false);
                    result.emplace_back(
                        key, NodeWrapper{std::move(tmpNode), OverrideValueLocation::Default, false});
                }
                ++index;
            }
        }
        // Load items from instance which are not in prefab neither in default (they are new)
        // Use _data (and not instancePropMap) to keep the order of items inside _data
        for (auto const& item : _data)
        {
            auto key = getKeyJson(item);
            if (instancePropMap.count(key))
            {
                if (not doRemove(*instancePropMap[key]))
                {
                    auto node = entlib->loadNode(_nodeSchema.singularItems->get(), item, nullptr);
                    result.emplace_back(
                        key, NodeWrapper{std::move(node), OverrideValueLocation::Override, false});
                }
                // else? New but removed => Let's ignore them.
            }
        }
        if (ordered)
        {
            std::sort(begin(result), end(result), [](auto&& a, auto&& b) {
                return std::get<0>(a) < std::get<0>(b);
            });
        }
        Ent::Array arr{entlib, &_nodeSchema};
        for (auto const& key_node : result)
        {
            auto&& key = std::get<0>(key_node);
            auto&& node = std::get<1>(key_node);
            if (arr.mapGet(key) != nullptr)
            {
                std::stringstream ss;
                ss << "Twice the same key in map : " << key;
                throw InvalidJsonData(ss.str().c_str());
            }
            arr.mapInitInsert(node.loc, key, std::move(node.node));
            if (node.removed)
            {
                arr.mapErase(KeyType(key));
            }
        }
        return arr;
    }
};

Ent::Node Ent::EntityLib::loadNode(
    Ent::Subschema const& _nodeSchema,
    json const& _data,
    Ent::Node const* _super,
    json const* _default) const
{
    ENTLIB_ASSERT(_super == nullptr or &_nodeSchema == _super->getSchema());

    Ent::Node result;

    if (_default == nullptr and not _nodeSchema.defaultValue.is_null())
    {
        _default = &_nodeSchema.defaultValue;
    }

    switch (_nodeSchema.type)
    {
    case Ent::DataType::null: result = Ent::Node(Ent::Null{}, &_nodeSchema); break;
    case Ent::DataType::string:
    {
        if (_nodeSchema.constValue.has_value())
        {
            // _nodeSchema is const and the value can't be overriden
            auto const def = _nodeSchema.constValue->get<std::string>();
            // We don't want to "override" this value to avoid to write every oneOf
            if (_super != nullptr) // If there is a prefab, the value is not overriden
            {
                result = Ent::Node(Ent::Override<String>("", def, tl::nullopt), &_nodeSchema);
            }
            else // If there is no prefab, it is overriden to be sure the node "hasOverride" and be saved
            {
                result = Ent::Node(Ent::Override<String>("", tl::nullopt, def), &_nodeSchema);
            }
        }
        else
        {
            std::string const def =
                _default == nullptr ? std::string() : _default->get<std::string>();
            tl::optional<std::string> const supVal =
                (_super != nullptr and not _super->hasDefaultValue()) ?
                    tl::optional<std::string>(_super->getString()) :
                    tl::optional<std::string>(tl::nullopt);
            tl::optional<std::string> const val =
                _data.is_string() ? tl::optional<std::string>(_data.get<std::string>()) :
                                    tl::optional<std::string>(tl::nullopt);
            result = Ent::Node(Ent::Override<String>(def, supVal, val), &_nodeSchema);
        }
    }
    break;
    case Ent::DataType::boolean:
    {
        bool const def = _default == nullptr ? bool{} : _default->get<bool>();
        tl::optional<bool> const supVal = (_super != nullptr and not _super->hasDefaultValue()) ?
                                              tl::optional<bool>(_super->getBool()) :
                                              tl::optional<bool>(tl::nullopt);
        tl::optional<bool> const val = _data.is_boolean() ? tl::optional<bool>(_data.get<bool>()) :
                                                            tl::optional<bool>(tl::nullopt);
        result = Ent::Node(Ent::Override<bool>(def, supVal, val), &_nodeSchema);
    }
    break;
    case Ent::DataType::integer:
    {
        int64_t const def = _default == nullptr ? int64_t{} : _default->get<int64_t>();
        tl::optional<int64_t> const supVal = (_super != nullptr and not _super->hasDefaultValue()) ?
                                                 tl::optional<int64_t>(_super->getInt()) :
                                                 tl::optional<int64_t>(tl::nullopt);
        tl::optional<int64_t> const val = _data.is_number_integer() or _data.is_number_unsigned() ?
                                              tl::optional<int64_t>(_data.get<int64_t>()) :
                                              tl::optional<int64_t>(tl::nullopt);
        result = Ent::Node(Ent::Override<int64_t>(def, supVal, val), &_nodeSchema);
    }
    break;
    case Ent::DataType::number:
    {
        double const def = _default == nullptr ? double{} : _default->get<double>();
        tl::optional<double> const supVal = (_super != nullptr and not _super->hasDefaultValue()) ?
                                                tl::optional<double>(_super->getFloat()) :
                                                tl::optional<double>(tl::nullopt);
        tl::optional<double> const val =
            _data.is_number_float() or _data.is_number_integer() or _data.is_number_unsigned() ?
                tl::optional<double>(_data.get<double>()) :
                tl::optional<double>(tl::nullopt);
        result = Ent::Node(Ent::Override<double>(def, supVal, val), &_nodeSchema);
    }
    break;
    case Ent::DataType::object:
    {
        Ent::Object object(&_nodeSchema);
        // Read the InstanceOf field
        Ent::Node prefabNode;
        auto InstanceOfIter = _data.find("InstanceOf");
        if (InstanceOfIter != _data.end())
        {
            auto nodeFileName = InstanceOfIter->get<std::string>();
            json nodeData = loadJsonFile(rawdataPath, nodeFileName);
            // Do not inherit from _super since the override of InstanceOf reset the Entity
            prefabNode = loadNode(_nodeSchema, nodeData, nullptr, _default);
            _super = &prefabNode;
            Ent::Override<String> tmplPath("", tl::nullopt, InstanceOfIter->get<std::string>());
            object.instanceOf = prefabNode.value.get<Object>().instanceOf.makeOverridedInstanceOf(
                InstanceOfIter->get<std::string>());
        }

        // Read the fields in schema
        object.nodes.reserve(_nodeSchema.properties.size());
        for (auto&& name_sub : _nodeSchema.properties)
        {
            Ent::SubschemaRef const& propSchemaRef = std::get<1>(name_sub);
            std::string const& name = std::get<0>(name_sub);
            Ent::Node const* superProp = (_super != nullptr) ? _super->at(name.c_str()) : nullptr;
            json const* refDefault = propSchemaRef.getRefDefaultValues();
            json const* schemaDefault =
                (_default != nullptr) and _default->count(name) != 0 ? &_default->at(name) : nullptr;
            // The less local default value has the priority
            json const* defaultProp = schemaDefault != nullptr ? schemaDefault : refDefault;
            json const emptyJson;
            json const& prop = _data.count(name) != 0 ? _data.at(name) : emptyJson;
            Ent::Node tmpNode = loadNode(*propSchemaRef, prop, superProp, defaultProp);
            object.nodes.emplace_back(name.c_str(), std::move(tmpNode));
        }
        std::sort(begin(object), end(object), Ent::CompObject());
        result = Ent::Node(std::move(object), &_nodeSchema);
    }
    break;
    case Ent::DataType::array:
    {
        Ent::Array arr(this, &_nodeSchema);
        auto&& meta = _nodeSchema.meta.get<Ent::Subschema::ArrayMeta>();
        size_t index = 0;
        if (_nodeSchema.singularItems)
        {
            uint64_t defaultArraySize =
                std::max(_nodeSchema.minItems, _default == nullptr ? 0 : _default->size());
            if (_data.is_null()) // No overrided
            {
                if (_super != nullptr)
                {
                    for (Ent::Node const* subSuper : _super->getItems())
                    {
                        json const* defaultItem = (_default != nullptr and index < _default->size()) ?
                                                      &_default->at(index) :
                                                      nullptr;
                        Ent::Node tmpNode = loadNode(
                            _nodeSchema.singularItems->get(), json(), subSuper, defaultItem);
                        auto loc = defaultItem == nullptr ? Ent::OverrideValueLocation::Prefab :
                                                            Ent::OverrideValueLocation::Default;
                        arr.initAdd(loc, std::move(tmpNode));
                        ++index;
                    }
                    if (not arr.hasKey())
                    {
                        tl::optional<uint64_t> prefabArraySize =
                            defaultArraySize == _super->size() ?
                                tl::nullopt :
                                tl::optional<uint64_t>{_super->size()};
                        arr.arraySetSize(Ent::Override<uint64_t>(
                            defaultArraySize, prefabArraySize, tl::nullopt));
                    }
                }
                else if (_default != nullptr)
                {
                    for (json const& subDefault : *_default)
                    {
                        auto& itemSchema = _nodeSchema.singularItems->get();
                        Ent::Node tmpNode = loadNode(itemSchema, json(), nullptr, &subDefault);
                        arr.initAdd(Ent::OverrideValueLocation::Default, std::move(tmpNode));
                        ++index;
                    }
                    if (not arr.hasKey())
                    {
                        arr.arraySetSize(
                            Ent::Override<uint64_t>(defaultArraySize, tl::nullopt, tl::nullopt));
                    }
                }
                else
                {
                    for (size_t i = 0; i < _nodeSchema.minItems; ++i)
                    {
                        Ent::Node tmpNode =
                            loadNode(_nodeSchema.singularItems->get(), json(), nullptr);
                        arr.initAdd(Ent::OverrideValueLocation::Default, std::move(tmpNode));
                        ++index;
                    }
                    if (not arr.hasKey())
                    {
                        arr.arraySetSize(
                            Ent::Override<uint64_t>(defaultArraySize, tl::nullopt, tl::nullopt));
                    }
                }
            }
            else // If it is a singularItems and there is _data, we have to use the overridePolicy
            {
                using namespace Ent;
                MergeMapOverride mergeMapOverride{_nodeSchema, _data, _super, _default, this};
                auto doRemoveDefault = [](json const&) {
                    return false;
                };
                switch (hash(meta.overridePolicy))
                {
                case "map"_hash:
                {
                    // It is a C++ map.
                    // In json it is an array of "2 item array" where the 1st item is the key
                    // and can be string, double or integer
                    // meta.ordered means the items have to be sorted by the key
                    Ent::DataType keyType = _nodeSchema.singularItems->get().linearItems->at(0)->type;
                    auto doRemove = [](json const& item) {
                        return item[1].is_null();
                    };
#pragma warning(push)
#pragma warning(disable : 4061) // There are switches with missing cases. This is wanted.
                    switch (keyType)
                    {
                    case Ent::DataType::string:
                        arr = mergeMapOverride(
                            [](json const& item) { return item[0].get<std::string>(); },
                            [](Node const* tmplItem) { return tmplItem->at(0llu)->getString(); },
                            doRemove);

                        break;
                    case Ent::DataType::entityRef:
                        arr = mergeMapOverride(
                            [](json const& item) { return item[0].get<std::string>(); },
                            [](Node const* tmplItem) {
                                return tmplItem->at(0llu)->getEntityRef().entityPath;
                            },
                            doRemove);
                        break;
                    case Ent::DataType::number:
                        arr = mergeMapOverride(
                            [](json const& item) { return item[0].get<double>(); },
                            [](Node const* tmplItem) { return tmplItem->at(0llu)->getFloat(); },
                            doRemove);
                        break;
                    case Ent::DataType::integer:
                        arr = mergeMapOverride(
                            [](json const& item) { return item[0].get<int64_t>(); },
                            [](Node const* tmplItem) { return tmplItem->at(0llu)->getInt(); },
                            doRemove);
                        break;
                    default:
                        throw ContextException(
                            "Unknown key type in map '%s'", _nodeSchema.name.c_str());
                    }
                }
                break;
                case "set"_hash:
                {
                    // It is a C++ set.
                    // In json it is an array of primitive. string, double or integer or oneOf
                    // meta.ordered means the items have to be sorted by the key
                    Ent::DataType const keyType = _nodeSchema.singularItems->get().type;
                    switch (keyType)
                    {
                    case Ent::DataType::oneOf: // The key is the className string
                    {
                        auto const& unionMeta =
                            _nodeSchema.singularItems->get().meta.get<Ent::Subschema::UnionMeta>();
                        auto doRemoveUnion = [unionMeta](json const& item) {
                            return item[unionMeta.dataField].is_null();
                        };
                        arr = mergeMapOverride(
                            [&unionMeta](json const& item) {
                                return item[unionMeta.typeField].get<std::string>();
                            },
                            [](Node const* subSuper) { return subSuper->getUnionType(); },
                            doRemoveUnion);
                    }
                    break;
                    case Ent::DataType::string: // The key is the item itself
                        arr = mergeMapOverride(
                            [](json const& item) { return item.get<std::string>(); },
                            [&](Node const* tmplItem) {
                                ENTLIB_ASSERT(
                                    tmplItem->getSchema() == &_nodeSchema.singularItems->get());
                                return tmplItem->getString();
                            },
                            doRemoveDefault);
                        break;
                    case Ent::DataType::number: // The key is the item itself
                        arr = mergeMapOverride(
                            [](json const& item) { return item.get<double>(); },
                            [](Node const* tmplItem) { return tmplItem->getFloat(); },
                            doRemoveDefault);
                        break;
                    case Ent::DataType::integer: // The key is the item itself
                        arr = mergeMapOverride(
                            [](json const& item) { return item.get<int64_t>(); },
                            [](Node const* tmplItem) { return tmplItem->getInt(); },
                            doRemoveDefault);
                        break;
                    case Ent::DataType::object: // The key is a field in the item
                        if (meta.keyField.has_value())
                        {
                            auto& keyProperty =
                                *_nodeSchema.singularItems->get().properties[*meta.keyField];
                            auto doRemoveSet = [](json const& item) {
                                return item.value("__removed__", false);
                            };
                            switch (keyProperty.type)
                            {
                            case Ent::DataType::string:
                                arr = mergeMapOverride(
                                    [key = meta.keyField->c_str()](json const& item) {
                                        return item.at(key).get<std::string>();
                                    },
                                    [key = meta.keyField->c_str()](Node const* tmplItem) {
                                        return tmplItem->at(key)->getString();
                                    },
                                    doRemoveSet);
                                break;
                            case Ent::DataType::integer:
                                arr = mergeMapOverride(
                                    [key = meta.keyField->c_str()](json const& item) {
                                        return item.at(key).get<int64_t>();
                                    },
                                    [key = meta.keyField->c_str()](Node const* tmplItem) {
                                        return tmplItem->at(key)->getInt();
                                    },
                                    doRemoveSet);
                                break;
                            default:
                                throw ContextException(
                                    "Wrong type for keyField '%s'", meta.keyField->c_str());
                            }
                            break;
                        }
                        // [[fallthrough]]
                    default:
                        throw ContextException(
                            "Unknown key type in set '%s'", _nodeSchema.name.c_str());
                    }
#pragma warning(pop)
                }
                break;
                case ""_hash: // The default "overridePolicy" is for simple array
                {
                    for (auto const& item : _data)
                    {
                        Ent::Node const* subSuper =
                            (_super != nullptr and (_super->size() > index)) ? _super->at(index) :
                                                                               nullptr;
                        json const* subDefault =
                            (_default != nullptr and (_default->size() > index)) ?
                                &_default->at(index) :
                                nullptr;
                        Ent::Node tmpNode =
                            loadNode(_nodeSchema.singularItems->get(), item, subSuper, subDefault);
                        bool const isDefault = (index < defaultArraySize) or subDefault != nullptr;
                        auto loc = isDefault           ? Ent::OverrideValueLocation::Default :
                                   subSuper != nullptr ? Ent::OverrideValueLocation::Prefab :
                                                         Ent::OverrideValueLocation::Override;
                        arr.initAdd(loc, std::move(tmpNode));
                        ++index;
                    }
                    tl::optional<uint64_t> prefabArraySize =
                        (_super != nullptr and _super->size() != defaultArraySize) ?
                            tl::optional<uint64_t>{_super->size()} :
                            tl::nullopt;
                    const uint64_t sizeInPrefab = prefabArraySize.value_or(defaultArraySize);
                    tl::optional<uint64_t> overrideArraySize =
                        _data.size() == sizeInPrefab ? tl::nullopt :
                                                       tl::optional<uint64_t>{_data.size()};
                    arr.arraySetSize(Ent::Override<uint64_t>(
                        defaultArraySize, prefabArraySize, overrideArraySize));
                }
                break;
                default:
                    throw ContextException(
                        "Unknown key type (%s) in schema of '%s'",
                        meta.overridePolicy.c_str(),
                        _nodeSchema.name.c_str());
                }
            }
        }
        else
        {
            ENTLIB_ASSERT(_nodeSchema.linearItems.has_value());
            for (Ent::SubschemaRef const& sub : *_nodeSchema.linearItems)
            {
                Ent::Node const* subSuper =
                    (_super != nullptr and _super->size() > index) ? _super->at(index) : nullptr;
                json const* subDefault = (_default != nullptr and _default->size() > index) ?
                                             &_default->at(index) :
                                             nullptr;
                json const emptyJson;
                json const& prop = _data.size() > index ? _data.at(index) : emptyJson;
                Ent::Node tmpNode = loadNode(*sub, prop, subSuper, subDefault);
                arr.arrayInitPush(std::move(tmpNode));
                ++index;
            }
            uint64_t defaultArraySize = _nodeSchema.linearItems->size();
            arr.arraySetSize(Ent::Override<uint64_t>(defaultArraySize, tl::nullopt, tl::nullopt));
        }
        result = Ent::Node(std::move(arr), &_nodeSchema);
    }
    break;
    case Ent::DataType::entityRef:
    {
        Ent::EntityRef const def = _default == nullptr ?
                                       Ent::EntityRef() :
                                       Ent::EntityRef{String(_default->get<std::string>())};

        tl::optional<Ent::EntityRef> const supVal =
            (_super != nullptr and not _super->hasDefaultValue()) ? // Keep the prefab value if there is
                tl::optional<Ent::EntityRef>(_super->getEntityRef()) :
                tl::optional<Ent::EntityRef>(tl::nullopt);

        tl::optional<std::string> const refString =
            _data.is_string() ? _data.get<std::string>() : tl::optional<std::string>(tl::nullopt);

        tl::optional<Ent::EntityRef> const val =
            refString.has_value() ? tl::optional<Ent::EntityRef>(Ent::EntityRef{refString.value()}) :
                                    tl::optional<Ent::EntityRef>(tl::nullopt);

        result = Ent::Node(Ent::Override<Ent::EntityRef>(def, supVal, val), &_nodeSchema);
    }
    break;
    case Ent::DataType::oneOf:
    {
        auto&& meta = _nodeSchema.meta.get<Ent::Subschema::UnionMeta>();
        std::string const& typeField = meta.typeField;
        if (typeField.empty())
        {
            auto message = Ent::format("%s has no meta/unionTypeField", _nodeSchema.name.c_str());
            throw Ent::IllFormedSchema(message.c_str());
        }
        std::string dataType;
        if (_data.count(typeField) != 0)
        {
            dataType = _data.at(typeField).get<std::string>();
            if (_super != nullptr and dataType != _super->getUnionType())
            {
                _super = nullptr; // The datatype has changed. No more use the data from _super
            }
        }
        else // No uniontype
        {
            if (_super != nullptr) // If no uniontype, use the one the prefab
            {
                dataType = _super->getUnionType();
            }
            else
            {
                // We are making a new node without input data
                // "back()" because the base type is at the end of the type list
                // TODO : Loïc - Add in metadata the name of the default type
                auto& lastSubSchema = _nodeSchema.oneOf->back();
                if (lastSubSchema->properties.count(typeField) == 0)
                {
                    auto message = Ent::format(
                        "Last subschema of %s has no typeField named '%s'",
                        _nodeSchema.name.c_str(),
                        typeField.c_str());
                    throw Ent::IllFormedSchema(message.c_str());
                }
                dataType =
                    AT(lastSubSchema->properties, typeField).get().constValue->get<std::string>();
            }
        }
        bool typeFound = false;
        int subSchemaIndex = -1;
        for (Ent::SubschemaRef const& schemaTocheck : *_nodeSchema.oneOf)
        {
            ++subSchemaIndex;
            if (schemaTocheck->properties.count(typeField) == 0)
            {
                auto message = Ent::format(
                    "%dth subschema of %s has no typeField named '%s'",
                    subSchemaIndex,
                    _nodeSchema.name.c_str(),
                    typeField.c_str());
                throw Ent::IllFormedSchema(message.c_str());
            }
            auto&& schemaType =
                AT(schemaTocheck->properties, typeField).get().constValue->get<std::string>();
            if (schemaType == dataType)
            {
                Ent::Node const* superUnionDataWrapper =
                    _super != nullptr ? _super->getUnionDataWrapper() : nullptr;
                ENTLIB_ASSERT(
                    superUnionDataWrapper == nullptr
                    or &schemaTocheck.get() == superUnionDataWrapper->getSchema());
                Ent::Node dataNode =
                    loadNode(schemaTocheck.get(), _data, superUnionDataWrapper, _default);
                Ent::Union un{};
                un.schema = &_nodeSchema;
                un.wrapper = Ent::make_value<Ent::Node>(std::move(dataNode));
                un.metaData = &meta;
                un.typeIndex = size_t(subSchemaIndex);
                result = Ent::Node(std::move(un), &_nodeSchema);
                typeFound = true;
                break;
            }
        }
        if (not typeFound)
        {
            ENTLIB_LOG_ERROR(
                "Can't find type %s in schema %s", dataType.c_str(), _nodeSchema.name.c_str());
            Ent::Union un;
            un.schema = &_nodeSchema;
            un.metaData = &meta;
            un.typeIndex = 0;
            result = Ent::Node(std::move(un), &_nodeSchema);
        }
    }
    break;
    case Ent::DataType::COUNT:
    default: ENTLIB_LOGIC_ERROR("Invalid DataType"); break;
    }
    return result;
}

json Ent::EntityLib::dumpNode(
    Subschema const& _schema,
    Node const& _node,
    OverrideValueSource _dumpedValueSource,
    bool _superKeyIsTypeName,
    std::function<void(EntityRef&)> const& _entityRefPreProc,
    bool _saveUnionIndex)
{
    json data;
    switch (_schema.type)
    {
    case Ent::DataType::null: break;
    case Ent::DataType::string: data = _node.getString(); break;
    case Ent::DataType::boolean: data = _node.getBool(); break;
    case Ent::DataType::integer: data = _node.getInt(); break;
    case Ent::DataType::number: data = _node.getFloat(); break;
    case Ent::DataType::object:
    {
        data = json::object();
        for (auto const& name_sub : _schema.properties)
        {
            auto&& name = std::get<0>(name_sub);
            Ent::Node const* subNode = _node.at(name.c_str());
            if (subNode->matchValueSource(_dumpedValueSource))
            {
                json subJson = dumpNode(
                    *std::get<1>(name_sub),
                    *subNode,
                    _dumpedValueSource,
                    _superKeyIsTypeName,
                    _entityRefPreProc);
                // handle "Super" special key
                if (_superKeyIsTypeName and name == "Super")
                {
                    const auto* typeName = getRefTypeName(subNode->getTypeName());
                    data[typeName] = std::move(subJson);
                }
                else
                {
                    data[name] = std::move(subJson);
                }
            }
        }
        if (_dumpedValueSource == OverrideValueSource::Override
            and _node.value.get<Ent::Object>().instanceOf.isSet())
        {
            data["InstanceOf"] = _node.getInstanceOf();
        }
    }
    break;
    case Ent::DataType::array:
    {
        data = json::array();
        auto&& meta = _schema.meta.get<Ent::Subschema::ArrayMeta>();
        bool const fullWrite = meta.isMapItem;
        auto const& arr = _node.value.get<Ent::Array>();
        if (arr.hasKey())
        {
            for (auto& item : arr.getItemsWithRemoved())
            {
                if (arr.isErased(arr.getChildKey(item)))
                {
                    if (_dumpedValueSource == OverrideValueSource::Override)
                    {
                        if (meta.overridePolicy == "map")
                        {
                            ENTLIB_ASSERT(item->getSchema() != nullptr);
                            json tmpNode;
                            tmpNode[0] = item->at(0llu)->toJson(
                                _dumpedValueSource, _superKeyIsTypeName, _entityRefPreProc);
                            tmpNode[1] = json();
                            data.emplace_back(std::move(tmpNode));
                        }
                        else if (meta.overridePolicy == "set")
                        {

                            if (item->getSchema()->type == Ent::DataType::oneOf)
                            {
                                auto& unionMeta =
                                    item->getSchema()->meta.get<Ent::Subschema::UnionMeta>();
                                char const* type = item->getUnionType();
                                json tmpNode;
                                tmpNode[unionMeta.typeField] = type;
                                tmpNode[unionMeta.dataField] = json();
                                data.emplace_back(std::move(tmpNode));
                                if (unionMeta.indexField.has_value() and _saveUnionIndex)
                                {
                                    data[*unionMeta.indexField] = _node.getUnionTypeIndex();
                                }
                            }
                            else if (
                                item->getSchema()->type == Ent::DataType::object
                                and meta.keyField.has_value())
                            {
                                json tmpNode;
                                auto key = arr.getChildKey(item);
                                mapbox::util::apply_visitor(
                                    [&](auto&& k) { tmpNode[*meta.keyField] = k; }, key);
                                tmpNode["__removed__"] = true;
                                data.emplace_back(std::move(tmpNode));
                                // [[fallthrough]]
                            }
                            else
                                throw ContextException("Can't write an erased element in a set of "
                                                       "non-union");
                        }
                    }
                }
                else if (item->matchValueSource(_dumpedValueSource) or fullWrite)
                {
                    ENTLIB_ASSERT(item->getSchema() != nullptr);
                    json tmpNode = dumpNode(
                        *item->getSchema(),
                        *item,
                        _dumpedValueSource,
                        _superKeyIsTypeName,
                        _entityRefPreProc);
                    data.emplace_back(std::move(tmpNode));
                }
            }
        }
        else
        {
            for (auto& item : arr.getItems())
            {
                if (item->matchValueSource(_dumpedValueSource) or fullWrite)
                {
                    ENTLIB_ASSERT(item->getSchema() != nullptr);
                    json tmpNode = dumpNode(
                        *item->getSchema(),
                        *item,
                        _dumpedValueSource,
                        _superKeyIsTypeName,
                        _entityRefPreProc);
                    data.emplace_back(std::move(tmpNode));
                }
                else
                {
                    data.emplace_back(json());
                }
            }
        }
    }
    break;
    case Ent::DataType::entityRef:
    {
        Ent::EntityRef ref = _node.getEntityRef();
        if (_entityRefPreProc)
        {
            _entityRefPreProc(ref);
        }
        data = ref.entityPath.c_str();
    }
    break;
    case Ent::DataType::oneOf:
    {
        auto&& meta = _schema.meta.get<Ent::Subschema::UnionMeta>();
        Ent::Node const* dataInsideUnion = _node.getUnionData();
        char const* type = _node.getUnionType();
        data[meta.typeField] = type;
        data[meta.dataField] = dumpNode(
            *dataInsideUnion->getSchema(),
            *dataInsideUnion,
            _dumpedValueSource,
            _superKeyIsTypeName,
            _entityRefPreProc);
        if (meta.indexField.has_value() and _saveUnionIndex)
        {
            data[*meta.indexField] = _node.getUnionTypeIndex();
        }
    }
    break;
    case Ent::DataType::COUNT:
    default: ENTLIB_LOGIC_ERROR("DataType is Invalid!!"); break;
    }
    return data;
}

namespace
{
    Ent::ActivationLevel parseActivationLevel(const std::string& _name)
    {
        if (_name == "Created")
        {
            return Ent::ActivationLevel::Created;
        }
        if (_name == "Started")
        {
            return Ent::ActivationLevel::Started;
        }
        if (_name == "Loading")
        {
            return Ent::ActivationLevel::Loading;
        }
        if (_name == "InWorld")
        {
            return Ent::ActivationLevel::InWorld;
        }
        return Ent::ActivationLevel::Started;
    }

    char const* getActivationLevelString(Ent::ActivationLevel _level)
    {
        if (_level == Ent::ActivationLevel::Created)
        {
            return "Created";
        }
        if (_level == Ent::ActivationLevel::Started)
        {
            return "Started";
        }
        if (_level == Ent::ActivationLevel::Loading)
        {
            return "Loading";
        }
        if (_level == Ent::ActivationLevel::InWorld)
        {
            return "InWorld";
        }
        return "Started";
    }
} // namespace

static std::unique_ptr<Ent::Entity> loadEntity(
    Ent::EntityLib const& _entlib, json const& _entNode, Ent::Entity const* _superEntityFromParentEntity)
{
    ENTLIB_ASSERT(
        _superEntityFromParentEntity == nullptr
        or _superEntityFromParentEntity->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);

    Ent::Override<String> ovInstanceOf;
    if (_superEntityFromParentEntity != nullptr)
    {
        ovInstanceOf = _superEntityFromParentEntity->getInstanceOfValue().makeInstanceOf();
    }
    auto superEntityOfThisEntity = std::make_unique<Ent::Entity>(_entlib);
    ENTLIB_ASSERT(superEntityOfThisEntity->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);
    bool superIsInit = false;
    Ent::Entity const* superEntity = superEntityOfThisEntity.get();
    ENTLIB_ASSERT(superEntity->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);
    if (_entNode.count("InstanceOf") != 0)
    {
        auto const prefabPath = _entNode.at("InstanceOf").get<std::string>();
        // Do not inherit from _superEntityFromParentEntity since the override of InstanceOf reset the Entity
        auto superEntityShared = _entlib.loadEntityReadOnly(prefabPath.c_str(), nullptr);
        ovInstanceOf = superEntityShared->getInstanceOfValue().makeOverridedInstanceOf(prefabPath);
        superEntity = superEntityShared.get();
        ENTLIB_ASSERT(superEntity->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);
        superIsInit = true;
    }
    ENTLIB_ASSERT(superEntity->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);

    if (not superIsInit and _superEntityFromParentEntity != nullptr)
    {
        superEntity = _superEntityFromParentEntity;
        ENTLIB_ASSERT(superEntity->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);
    }

    tl::optional<std::string> const thumbnail = _entNode.count("Thumbnail") != 0 ?
                                                    _entNode.at("Thumbnail").get<std::string>() :
                                                    tl::optional<std::string>();
    Ent::Override<String> superThumbnail = superEntity->getThumbnailValue();
    Ent::Override<String> ovThumbnail = superThumbnail.makeOverridedInstanceOf(thumbnail);

    tl::optional<std::string> const name = _entNode.count("Name") != 0 ?
                                               _entNode.at("Name").get<std::string>() :
                                               tl::optional<std::string>();

    Ent::Override<String> superName = superEntity->getNameValue();
    Ent::Override<String> ovName = superName.makeOverridedInstanceOf(name);

    Ent::Override<String> superInstanceOf = superEntity->getInstanceOfValue();

    tl::optional<Ent::ActivationLevel> maxActivationLevel;
    if (_entNode.count("MaxActivationLevel") != 0)
    {
        maxActivationLevel =
            parseActivationLevel(_entNode.at("MaxActivationLevel").get<std::string>());
    }
    Ent::Override<Ent::ActivationLevel> superActivationLevel =
        superEntity != nullptr ? superEntity->getMaxActivationLevelValue() :
                                 Ent::Override<Ent::ActivationLevel>{Ent::ActivationLevel::Started};
    Ent::Override<Ent::ActivationLevel> ovMaxActivationLevel =
        superActivationLevel.makeOverridedInstanceOf(maxActivationLevel);

    // Color
    Ent::Node ovColor = Ent::makeDefaultColorField(_entlib);
    if (_entNode.contains("Color"))
    {
        Ent::Subschema const& colorSchema =
            AT(_entlib.schema.schema.allDefinitions, Ent::colorSchemaName);
        ovColor = _entlib.loadNode(
            colorSchema,
            _entNode.at("Color"),
            _superEntityFromParentEntity != nullptr ? &_superEntityFromParentEntity->getColorValue() :
                                                      nullptr);
    }
    else if (superEntity != nullptr)
    {
        ovColor = superEntity->getColorValue().makeInstanceOf();
    }

    // ActorStates
    Ent::Subschema const& actorStatesSchema =
        AT(_entlib.schema.schema.allDefinitions, Ent::actorStatesSchemaName);
    Ent::Node ovActorStates(Ent::Array{&_entlib, &actorStatesSchema}, &actorStatesSchema);
    if (_entNode.contains("ActorStates"))
    {
        ovActorStates = _entlib.loadNode(
            actorStatesSchema, _entNode.at("ActorStates"), &superEntity->getActorStates());
    }
    else
    {
        ovActorStates = superEntity->getActorStates().makeInstanceOf();
    }

    std::map<std::string, Ent::Component> components;
    std::set<std::string> removedComponents;
    std::unique_ptr<Ent::SubSceneComponent> subSceneComponent;
    size_t index = 0;
    if (_entNode.count("Components") != 0)
    {
        json const& componentsNode = _entNode.at("Components");
        for (json const& compNode : componentsNode)
        {
            auto const cmpType = compNode.at("Type").get<std::string>();
            json const& data = compNode.at("Data");
            if (data.is_null())
            {
                removedComponents.insert(cmpType);
                continue;
            }

            if (cmpType == "SubScene")
            {
                Ent::SubSceneComponent const* superComp = superEntity->getSubSceneComponent();

                auto fileInJson = (data.count("File") != 0) ?
                                      tl::optional<std::string>(data["File"].get<std::string>()) :
                                      tl::nullopt;
                auto subSceneComp = std::make_unique<Ent::SubSceneComponent>(&_entlib, index);
                subSceneComp->embedded = _entlib.loadScene(
                    data["Embedded"], (superComp != nullptr ? superComp->embedded.get() : nullptr));
                subSceneComponent = std::move(subSceneComp);
            }
            else
            {
                Ent::Component const* superComp = superEntity->getComponent(cmpType.c_str());
                auto const version =
                    compNode.count("Version") != 0u ? compNode.at("Version").get<size_t>() : 0;

                if (_entlib.schema.components.count(cmpType) == 0)
                {
                    ENTLIB_LOG_ERROR("Unknown Component type : %s", cmpType.c_str());
                }
                else
                {
                    Ent::Subschema const& compSchema = *AT(_entlib.schema.components, cmpType);
                    json rawData = (superComp != nullptr ? superComp->rawData : json());
                    rawData.merge_patch(data);
                    Ent::Component comp{
                        rawData,
                        superComp != nullptr, // has a super component
                        cmpType,
                        _entlib.loadNode(
                            compSchema, data, (superComp != nullptr ? &superComp->root : nullptr)),
                        version,
                        index};

                    components.emplace(cmpType, std::move(comp));
                }
            }
            ++index;
        }
    }
    // Add undeclared componants to be able to get values inside (They are full reference to prefab)
    for (auto const& type_comp : superEntity->getComponents())
    {
        auto const& cmpType = std::get<0>(type_comp);
        if (removedComponents.count(cmpType) != 0)
        {
            continue;
        }
        auto const& superComp = std::get<1>(type_comp);
        if (components.count(cmpType) == 0)
        {
            Ent::Component comp{
                superComp.rawData,
                true,
                cmpType,
                superComp.root.makeInstanceOf(),
                superComp.version,
                superComp.index};

            components.emplace(cmpType, std::move(comp));
        }
        ++index;
    }
    {
        Ent::SubSceneComponent const* superComp = superEntity->getSubSceneComponent();
        if (superComp != nullptr and subSceneComponent == nullptr
            and removedComponents.count("SubScene") == 0)
        {
            subSceneComponent = std::make_unique<Ent::SubSceneComponent>(
                &_entlib, superComp->index, superComp->embedded->makeInstanceOf());
        }
    }
    return std::make_unique<Ent::Entity>(
        _entlib,
        std::move(ovName),
        std::move(components),
        std::move(removedComponents),
        std::move(subSceneComponent),
        std::move(ovActorStates),
        std::move(ovColor),
        std::move(ovThumbnail),
        std::move(ovInstanceOf),
        ovMaxActivationLevel);
}

/// Exception thrown when a method is called on legacy data (or vice versa)
struct UnsupportedFormat : ContextException
{
    UnsupportedFormat() = default;
};

template <typename Type, typename Cache, typename ValidateFunc, typename LoadFunc>
std::shared_ptr<Type const> Ent::EntityLib::loadEntityOrScene(
    std::filesystem::path const& _path,
    Cache& cache,
    ValidateFunc&& validate,
    LoadFunc&& load,
    Type const* _super) const
{
    auto const absPath = getAbsolutePath(_path);
    std::filesystem::path relPath = absPath.c_str() + rawdataPath.native().size() + 1;
    bool reload = false;
    auto error = std::error_code{};
    auto timestamp = std::filesystem::last_write_time(absPath, error);
    if (error)
    {
        throw FileSystemError("Trying to open file for read", rawdataPath, relPath, error);
    }
    auto iter = cache.find(relPath);
    if (iter == cache.end())
    {
        reload = true;
    }
    else
    {
        if (timestamp > iter->second.time)
        {
            reload = true;
        }
    }

    if (reload)
    {
        try
        {
            json document = loadJsonFile(rawdataPath, relPath);
            if (document.count("Objects") and typeid(Type) == typeid(Entity)
                or (document.count("Name") or document.count("InstanceOf")
                    or document.count("Components"))
                       and typeid(Type) == typeid(Scene))
            {
                // we are trying to load a legacy scene through loadScene method
                // or a new Scene format through loadLegacyScene method
                throw UnsupportedFormat();
            }
            if (validationEnabled)
            {
                validate(schema.schema, toolsDir, document);
            }

            std::unique_ptr<Type> entity = load(*this, document, _super);
            auto file = typename Cache::mapped_type{std::move(entity), timestamp};
            auto iter_bool = cache.insert_or_assign(relPath, std::move(file));
            return std::get<0>(iter_bool)->second.data;
        }
        catch (ContextException& ex)
        {
            ex.addContextMessage("loading : %s", formatPath(rawdataPath, relPath));
            throw;
        }
        catch (...)
        {
            throw WrapperException(
                std::current_exception(), "loading : %s", formatPath(rawdataPath, relPath));
        }
    }
    else
    {
        return iter->second.data;
    }
}

std::shared_ptr<Ent::Entity const> Ent::EntityLib::loadEntityReadOnly(
    std::filesystem::path const& _entityPath, Ent::Entity const* _super) const
{
    return loadEntityOrScene<Ent::Entity>(
        _entityPath, m_entityCache, &validateEntity, &::loadEntity, _super);
}

std::unique_ptr<Ent::Scene> Ent::EntityLib::loadScene(json const& _entities, Ent::Scene const* _super) const
{
    auto scene = std::make_unique<Ent::Scene>(this);

    // Add all entities from super scene ...
    std::set<std::string> entFromSuper;
    if (_super != nullptr)
    {
        for (auto&& superEnt : _super->getObjects())
        {
            entFromSuper.insert(superEnt->getName());
            json const* instEntNode = nullptr;
            // ... and look if there is an override.
            for (json const& entNode : _entities)
            {
                auto const instEntName = entNode.at("Name").get<std::string>();
                if (superEnt->getName() == instEntName)
                {
                    instEntNode = &entNode;
                    break;
                }
            }
            std::unique_ptr<Ent::Entity> ent = (instEntNode == nullptr) ?
                                                   superEnt->makeInstanceOf() :
                                                   ::loadEntity(*this, *instEntNode, superEnt.get());
            ent->setCanBeRenamed(false);
            scene->addEntity(std::move(ent));
        }
    }

    // Add new entities
    for (json const& entNode : _entities)
    {
        auto const name = entNode.at("Name").get<std::string>();
        if (entFromSuper.count(name) != 0)
        {
            continue;
        }
        std::unique_ptr<Ent::Entity> ent = ::loadEntity(*this, entNode, nullptr);
        scene->addEntity(std::move(ent));
    }

    return scene;
}

std::shared_ptr<Ent::Scene const>
Ent::EntityLib::loadSceneReadOnly(std::filesystem::path const& _scenePath) const
{
    return loadScene(_scenePath);
}

std::shared_ptr<Ent::Scene const>
Ent::EntityLib::loadLegacySceneReadOnly(std::filesystem::path const& _scenePath) const
{
    auto loadFunc = [](Ent::EntityLib const& _entLib, json const& _document, Ent::Scene const* _super) {
        return _entLib.loadScene(_document.at("Objects"), _super);
    };

    return loadEntityOrScene<Ent::Scene>(_scenePath, m_sceneCache, &validateScene, loadFunc, nullptr);
}

Ent::Node Ent::EntityLib::loadEntityAsNode(std::filesystem::path const& _entityPath) const
{
    Ent::Subschema const& entitySchema =
        AT(schema.schema.allDefinitions, "./Scene-schema.json#/definitions/Object");
    return loadFileAsNode(_entityPath, entitySchema);
}

Ent::Node Ent::EntityLib::loadFileAsNode(
    std::filesystem::path const& _path, Ent::Subschema const& _schema) const
{
    json jsonData = loadJsonFile(rawdataPath, _path);
    return loadNode(_schema, jsonData, nullptr, nullptr);
}

std::unique_ptr<Ent::Entity>
Ent::EntityLib::loadEntity(std::filesystem::path const& _entityPath, Ent::Entity const* _super) const
{
    return loadEntityReadOnly(_entityPath, _super)->clone();
}

std::unique_ptr<Ent::Scene> Ent::EntityLib::loadScene(std::filesystem::path const& _scenePath) const
{
    try
    {
        auto entity = loadEntity(_scenePath);
        if (auto* subScene = entity->getSubSceneComponent())
        {
            return subScene->detachEmbedded();
        }
        return {};
    }
    catch (const UnsupportedFormat&)
    {
        return loadLegacyScene(_scenePath);
    }
}

std::unique_ptr<Ent::Scene> Ent::EntityLib::loadLegacyScene(std::filesystem::path const& _scenePath) const
{
    return loadLegacySceneReadOnly(_scenePath)->clone();
}

nlohmann::json Ent::Entity::saveEntity() const
{
    ComponentsSchema const& _schema = entlib->schema;
    json entNode;

    // Always save Name since it is use for override
    entNode.emplace("Name", getNameValue().get().c_str());

    if (getInstanceOfValue().isSet())
    {
        entNode.emplace("InstanceOf", getInstanceOfValue().get().c_str());
    }

    Subschema const& colorSchema = AT(_schema.schema.allDefinitions, colorSchemaName);
    if (getColorValue().hasOverride())
    {
        entNode.emplace("Color", EntityLib::dumpNode(colorSchema, getColorValue()));
    }

    if (getThumbnailValue().isSet())
    {
        entNode.emplace("Thumbnail", getThumbnail());
    }

    if (getMaxActivationLevelValue().isSet())
    {
        entNode.emplace("MaxActivationLevel", getActivationLevelString(getMaxActivationLevel()));
    }

    json& componentsNode = entNode["Components"] = json::array();
    std::vector<Component const*> sortedComp;
    for (auto&& type_comp : getComponents())
    {
        sortedComp.push_back(&std::get<1>(type_comp));
    }
    Component subscenePlaceholder{json(), true, "SubScene", Node(), 1, 0};
    if (SubSceneComponent const* subscene = getSubSceneComponent())
    {
        subscenePlaceholder.index = subscene->index;
        sortedComp.push_back(&subscenePlaceholder);
    }
    std::sort(begin(sortedComp), end(sortedComp), [](Component const* cmp, Component const* cmp2) {
        return cmp->index < cmp2->index;
    });
    for (Component const* comp : sortedComp)
    {
        if (comp->type == "SubScene")
        {
            SubSceneComponent const* subscene = getSubSceneComponent();
            ENTLIB_ASSERT(subscene != nullptr);
            bool const subsceneHasOverride = subscene->hasOverride();
            bool const hasInstanceOf = getInstanceOf() != nullptr;
            if ((subsceneHasOverride and hasInstanceOf) or not hasInstanceOf)
            {
                json data;
                data.emplace("Embedded", subscene->embedded->saveScene()["Objects"]);

                json compNode;
                compNode.emplace("Version", comp->version);
                compNode.emplace("Type", comp->type);
                compNode.emplace("Data", std::move(data));
                componentsNode.emplace_back(std::move(compNode));
            }
        }
        else if (not comp->hasPrefab or comp->root.hasOverride())
        {
            json compNode;
            compNode.emplace("Version", comp->version);
            compNode.emplace("Type", comp->type);
            compNode.emplace(
                "Data", EntityLib::dumpNode(*AT(_schema.components, comp->type), comp->root));

            componentsNode.emplace_back(std::move(compNode));
        }
    }
    for (auto const& type : removedComponents)
    {
        json compNode;
        compNode.emplace("Type", type);
        compNode.emplace("Data", json{});
        componentsNode.emplace_back(std::move(compNode));
    }
    Subschema const& actorStatesSchema = AT(_schema.schema.allDefinitions, actorStatesSchemaName);
    if (getActorStates().hasOverride())
    {
        entNode.emplace("ActorStates", EntityLib::dumpNode(actorStatesSchema, getActorStates()));
    }
    return entNode;
}

void Ent::Entity::applyToPrefab()
{
    auto prefabPath = getInstanceOf();
    if (prefabPath == nullptr)
    {
        throw ContextException("This entity has no prefab");
    }
    auto prefab = entlib->loadEntity(prefabPath);
    auto prefabName = prefab->name;
    auto instanceName = name;

    // When the value is overridden is the source, we want to make it overridden in the dest => CopyOverride
    applyAllValuesButPrefab(*prefab, CopyMode::CopyOverride);
    prefab->name = prefabName;
    resetInstanceOf(prefabPath); // Reset 'this' to a vanilla instance of prefab
    name = instanceName;
    entlib->saveEntity(*prefab, prefabPath);
}

void Ent::Entity::applyAllValues(Entity& _dest, CopyMode _copyMode) const
{
    applyInstanceOfField(*this, _dest, _copyMode);
    applyAllValuesButPrefab(_dest, _copyMode);
}

void Ent::Entity::applyAllValuesButPrefab(Entity& _dest, CopyMode _copyMode) const
{
    name.applyAllValues(_dest.name, _copyMode);
    thumbnail.applyAllValues(_dest.thumbnail, _copyMode);
    maxActivationLevel.applyAllValues(_dest.maxActivationLevel, _copyMode);
    actorStates.applyAllValues(_dest.actorStates, _copyMode);
    color.applyAllValues(_dest.color, _copyMode);

    for (auto&& name_comp : getComponents())
    {
        auto&& cmpName = name_comp.first;
        auto&& comp = name_comp.second;
        // addComponent has no effect if the component exist
        comp.applyAllValues(*_dest.addComponent(cmpName.c_str()), _copyMode);
    }
    std::vector<char const*> compToRemove;
    for (auto&& name_comp : _dest.getComponents())
    {
        auto&& cmpName = name_comp.first;
        if (getComponent(cmpName.c_str()) == nullptr) // Removed component
        {
            compToRemove.push_back(cmpName.c_str());
        }
    }
    if (auto subScene = getSubSceneComponent())
    {
        // addSubSceneComponent has no effect if the component exist
        subScene->applyAllValues(*_dest.addSubSceneComponent(), _copyMode);
    }
    else if (auto destSubScene = _dest.getSubSceneComponent()) // Removed component
    {
        compToRemove.push_back("SubScene");
    }
    for (auto&& cmpName : compToRemove)
    {
        _dest.removeComponent(cmpName);
    }
}

std::unique_ptr<Ent::Entity> Ent::Entity::detachEntityFromPrefab() const
{
    std::map<std::string, Ent::Component> detComponents;
    size_t index = 0;
    for (auto const& type_comp : getComponents())
    {
        auto const& type = std::get<0>(type_comp);
        auto const& comp = std::get<1>(type_comp);

        Ent::Component detachedComp{comp.rawData, false, type, comp.root.detach(), 1, index};

        detComponents.emplace(type, std::move(detachedComp));
        ++index;
    }
    std::unique_ptr<SubSceneComponent> detSubSceneComponent;
    if (SubSceneComponent const* subscene = getSubSceneComponent())
    {
        detSubSceneComponent = std::make_unique<SubSceneComponent>(entlib);
        detSubSceneComponent->embedded = std::make_unique<Ent::Scene>(entlib);
        for (std::unique_ptr<Ent::Entity> const& subEntity : subscene->embedded->getObjects())
        {
            detSubSceneComponent->embedded->addEntity(subEntity->detachEntityFromPrefab());
        }
    }

    auto detachedColor = getColorValue().detach();
    auto detachedMaxActivationLevel = getMaxActivationLevelValue().detach();
    return std::make_unique<Ent::Entity>(
        *entlib,
        getNameValue().detach().makeOverridedInstanceOf(std::string(getName()) + "_detached"),
        std::move(detComponents),
        std::set<std::string>{}, // removedComponents
        std::move(detSubSceneComponent),
        actorStates.detach(),
        std::move(detachedColor),
        getThumbnailValue().detach(),
        Override<String>{},
        detachedMaxActivationLevel);
}

std::unique_ptr<Ent::Entity> Ent::EntityLib::makeInstanceOf(std::string const& _instanceOf) const
{
    std::unique_ptr<Ent::Entity> inst = std::make_unique<Ent::Entity>(*this);
    inst->resetInstanceOf(_instanceOf.c_str());
    return inst;
}

void Ent::EntityLib::saveEntity(Entity const& _entity, std::filesystem::path const& _relEntityPath) const
{
    std::filesystem::path entityPath = getAbsolutePath(_relEntityPath);
    std::ofstream file(entityPath);
    if (not file.is_open())
    {
        throw FileSystemError("Trying to open file for write", rawdataPath, entityPath);
    }
    json document = _entity.saveEntity();
    file << document.dump(4);
    file.close();

    // Better to check after save because it is easiest to debug
    if (validationEnabled)
    {
        try
        {
            validateEntity(schema.schema, toolsDir, document);
        }
        catch (ContextException& ex)
        {
            ex.addContextMessage("saving entity : %s", formatPath(rawdataPath, _relEntityPath));
            throw;
        }
        catch (...)
        {
            throw WrapperException(
                std::current_exception(),
                "saving entity : %s",
                formatPath(rawdataPath, _relEntityPath));
        }
    }
}

std::filesystem::path Ent::EntityLib::getAbsolutePath(std::filesystem::path const& _path) const
{
    if (_path.is_absolute())
    {
        std::filesystem::path absPath = _path;
        return very_weakly_canonical(absPath);
    }
    else
    {
        std::filesystem::path absPath = rawdataPath;
        absPath /= _path;
        return very_weakly_canonical(absPath);
    }
}

std::filesystem::path Ent::EntityLib::getRelativePath(std::filesystem::path const& _path) const
{
    if (_path.is_absolute())
    {
        // Check if _path is inside rawdataPath
        std::filesystem::path parrent = _path;
        std::filesystem::path relPath;
        while (parrent != rawdataPath)
        {
            if (parrent.has_parent_path() and parrent.parent_path() != parrent)
            {
                if (relPath.empty())
                {
                    relPath = parrent.filename();
                }
                else
                {
                    relPath = parrent.filename() / relPath;
                }
                parrent = parrent.parent_path();
            }
            else
            {
                throw ContextException(
                    R"(_path %s in not inside rawdata "%s")",
                    formatPath(rawdataPath, _path),
                    rawdataPath.generic_string().c_str());
            }
        }

        return relPath;
    }
    else
    {
        return _path;
    }
}

std::map<std::filesystem::path, Ent::EntityLib::EntityFile> const& Ent::EntityLib::getEntityCache() const
{
    return m_entityCache;
}
std::map<std::filesystem::path, Ent::EntityLib::SceneFile> const& Ent::EntityLib::getSceneCache() const
{
    return m_sceneCache;
}

void Ent::EntityLib::clearCache()
{
    m_entityCache.clear();
    m_sceneCache.clear();
}

json Ent::Scene::saveScene() const
{
    json document;

    document.emplace("Version", 2);
    json& jsnObjects = document["Objects"];
    jsnObjects = json::array();

    for (std::unique_ptr<Ent::Entity> const& ent : getObjects())
    {
        if (ent->hasOverride() or ent->newInTheScene())
        {
            jsnObjects.emplace_back(ent->saveEntity());
        }
    }

    return document;
}

void Ent::EntityLib::saveScene(Scene const& _scene, std::filesystem::path const& _scenePath) const
{
    Ent::Entity sceneEntity{*this};
    // scene entity is named after scene base file name
    sceneEntity.setName(_scenePath.stem().string());

    // generate relative wthumb path
    auto thumbNailPath = _scenePath.generic_string() + ".wthumb";
    const auto genericRawdataPath = rawdataPath.generic_string();
    const auto pos = thumbNailPath.find(genericRawdataPath);
    if (pos == 0)
    {
        const size_t offset = genericRawdataPath.size() + 1; // also strip the leading '/'
        thumbNailPath = thumbNailPath.substr(offset);
    }
    sceneEntity.setThumbnail(thumbNailPath);

    // embed scene
    auto* subScene = sceneEntity.addSubSceneComponent();
    for (auto&& entity : _scene.getObjects())
    {
        subScene->embedded->addEntity(entity->clone());
    }

    saveEntity(sceneEntity, _scenePath);
}

void Ent::SubSceneComponent::computeMemory(MemoryProfiler& prof) const
{
    prof.currentComp.push_back("SubScene");
    if (embedded)
    {
        embedded->computeMemory(prof);
    }
    prof.currentComp.pop_back();
}

std::unique_ptr<Ent::SubSceneComponent> Ent::SubSceneComponent::makeInstanceOf() const
{
    ENTLIB_ASSERT(embedded != nullptr);
    std::unique_ptr<Scene> instEmbedded = embedded->makeInstanceOf();
    return std::make_unique<SubSceneComponent>(
        embedded->getEntityLib(), index, std::move(instEmbedded));
}

std::unique_ptr<Ent::SubSceneComponent> Ent::SubSceneComponent::clone() const
{
    ENTLIB_ASSERT(embedded != nullptr);
    std::unique_ptr<Scene> instEmbedded = embedded->clone();
    return std::make_unique<SubSceneComponent>(
        embedded->getEntityLib(), index, std::move(instEmbedded));
}

std::unique_ptr<Ent::Scene> Ent::SubSceneComponent::detachEmbedded()
{
    auto scene = std::make_unique<Scene>(embedded->getEntityLib());
    std::swap(scene, embedded);

    // we don't to swap owners though
    embedded->setOwnerEntity(scene->getOwnerEntity());
    scene->setOwnerEntity(nullptr); // detached scene is not owned by any entity

    return scene;
}

void Ent::SubSceneComponent::applyAllValues(SubSceneComponent& _dest, CopyMode _copyMode) const
{
    if (embedded != nullptr and _dest.embedded != nullptr)
    {
        embedded->applyAllValues(*_dest.embedded, _copyMode);
    }
}

bool Ent::SubSceneComponent::hasOverride() const
{
    //if (isEmbedded.isSet())
    //    return true;
    //if (file.isSet())
    //    return true;
    //if (index.isSet())
    //    return true;
    return embedded != nullptr && embedded->hasOverride();
}

/// \endcond
