#include "Node.h"

#include <fstream>
#include <sstream>
#include <ciso646>

#include "external/json.hpp"

#include "include/EntityLib.h"

using namespace nlohmann;

namespace Ent
{

    Node::Node(Value val, Subschema const* _schema)
        : schema(_schema)
        , value(std::move(val))
    {
    }

    Node::Node(Node const& _node)
        : parentNode(nullptr)
        , schema(_node.schema)
        , value(_node.value)
        , addedInInstance(_node.addedInInstance)
    {
        updateParents();
    }
    Node::Node(Node&& _node) noexcept
        : parentNode(nullptr)
        , schema(_node.schema)
        , value(std::move(_node.value))
        , addedInInstance(_node.addedInInstance)
    {
        updateParents();
    }

    Node& Node::operator=(Node const& _node)
    {
        if (this != &_node)
        {
            parentNode = _node.parentNode;
            schema = _node.schema;
            value = _node.value;
            addedInInstance = _node.addedInInstance;
            updateParents();
        }
        return *this;
    }
    Node& Node::operator=(Node&& _node) noexcept
    {
        parentNode = _node.parentNode;
        schema = _node.schema;
        value = std::move(_node.value);
        addedInInstance = _node.addedInInstance;
        updateParents();
        return *this;
    }

    struct UpdateParents
    {
        Node* parent;

        template <typename T>
        void operator()(T& _val) const
        {
            _val.setParentNode(parent);
        }

        template <typename T>
        void operator()(Override<T>&) const
        {
        }

        void operator()(Null&) const
        {
        }
    };

    void Node::updateParents()
    {
        mapbox::util::apply_visitor(UpdateParents{this}, value);
    }

    struct CheckParents
    {
        Node const* parent{};

        template <typename T>
        void operator()(T const& _val) const
        {
            _val.checkParent(parent);
        }

        template <typename T>
        void operator()(Override<T> const&) const
        {
        }

        void operator()(Null const&) const
        {
        }
    };

    void Node::checkParent(Node const* _parentNode) const
    {
        ENTLIB_ASSERT(parentNode == _parentNode);
        mapbox::util::apply_visitor(CheckParents{this}, value);
    }

    Node* Node::getParentNode()
    {
        return parentNode;
    }
    Node const* Node::getParentNode() const
    {
        return parentNode;
    }

    void Node::setParentNode(Node* _parentNode)
    {
        parentNode = _parentNode;
    }

    DataType Node::getDataType() const
    {
        return (DataType)value.which();
    }

    Node* Node::at(char const* _field)
    {
        if (_field == nullptr)
        {
            throw NullPointerArgument("_field", "Node::at");
        }
        if (value.is<Object>())
        {
            return &Ent::at(value.get<Object>(), _field);
        }
        throw BadType();
    }
    Node const* Node::at(char const* _field) const
    {
        if (_field == nullptr)
        {
            throw NullPointerArgument("_field", "Node::at");
        }
        if (value.is<Object>())
        {
            return &Ent::at(value.get<Object>(), _field);
        }
        throw BadType();
    }
    bool Node::count(char const* _field) const
    {
        if (_field == nullptr)
        {
            throw NullPointerArgument("_field", "Node::count");
        }
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
            return &(*iter->node);
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
        if (_type == nullptr)
        {
            throw NullPointerArgument("_type", "Node::setUnionType");
        }
        if (value.is<Union>())
        {
            return value.get<Union>().setUnionType(_type);
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
        if (_val == nullptr)
        {
            throw NullPointerArgument("_val", "Node::setString");
        }
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
        bool operator()(T const& _ov) const
        {
            return _ov.hasDefaultValue();
        }

        bool operator()(Null const&) const
        {
            return false;
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
        Node operator()(T const& _ov) const
        {
            return Node(_ov.detach(), schema);
        }

        Node operator()(Null const&) const
        {
            return Node(Null{}, schema);
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
        Node operator()(T const& _ov) const
        {
            return Node(_ov.makeInstanceOf(), schema);
        }

        Node operator()(Null const&) const
        {
            return Node(Null{}, schema);
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
        bool operator()(T const& _ov) const
        {
            return _ov.hasOverride();
        }

        bool operator()(Null const&) const
        {
            return false;
        }
    };

    bool Node::hasOverride() const
    {
        if (addedInInstance)
        {
            return true;
        }
        return mapbox::util::apply_visitor(HasOverride{schema}, value);
    }

    struct HasPrefabValue
    {
        Subschema const* schema;

        template <typename T>
        bool operator()(T const& _ov) const
        {
            return _ov.hasPrefabValue();
        }

        bool operator()(Null const&) const
        {
            return false;
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
                fields.push_back(f.name);
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
        if (_key == nullptr)
        {
            throw NullPointerArgument("_key", "Node::mapErase");
        }
        checkMap("mapErase");
        if (not value.get<Array>().canErase())
        {
            throw BadArrayType(format("Can call 'mapErase' only on map and set of union").c_str());
        }
        return value.get<Array>().mapErase(_key);
    }

    Node* Node::mapGet(char const* _key)
    {
        if (_key == nullptr)
        {
            throw NullPointerArgument("_key", "Node::mapGet");
        }
        checkMap("mapGet");
        return value.get<Array>().mapGet(_key);
    }
    Node const* Node::mapGet(char const* _key) const
    {
        if (_key == nullptr)
        {
            throw NullPointerArgument("_key", "Node::mapGet");
        }
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

    Node* Node::mapInsert(int64_t _key)
    {
        checkMap("mapInsert");
        return value.get<Array>().mapInsert(_key);
    }

    Node* Node::mapInsert(char const* _key)
    {
        if (_key == nullptr)
        {
            throw NullPointerArgument("_key", "Node::mapInsert");
        }
        checkMap("mapInsert");
        return value.get<Array>().mapInsert(_key);
    }

    Node* Node::mapInsertInstanceOf(char const* _prefabPath)
    {
        if (_prefabPath == nullptr)
        {
            throw NullPointerArgument("_prefabPath", "Node::mapInsertInstanceOf");
        }
        checkMap("mapInsertInstanceOf");
        auto prefab = getEntityLib()->loadNodeReadOnly(**getSchema()->singularItems, _prefabPath);
        Node* newNode = value.get<Array>().mapInsert(value.get<Array>().getChildKey(prefab.get()));
        newNode->resetInstanceOf(_prefabPath);
        return newNode;
    }

    Node* Node::mapRename(char const* _key, char const* _newkey)
    {
        if (_key == nullptr)
        {
            throw NullPointerArgument("_key", "Node::mapRename");
        }
        if (_newkey == nullptr)
        {
            throw NullPointerArgument("_newkey", "Node::mapRename");
        }
        checkMap("mapGet");
        return value.get<Array>().mapRename(_key, _newkey);
    }

    Node* Node::mapRename(int64_t _key, int64_t _newkey)
    {
        checkMap("mapGet");
        return value.get<Array>().mapRename(_key, _newkey);
    }

    void Node::checkMap(char const* _calledMethod) const
    {
        ENTLIB_ASSERT(_calledMethod != nullptr);
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
        return value.get<Array>().getKeysString();
    }

    std::vector<int64_t> Node::getKeysInt() const
    {
        checkMap("getMapKeysInt");
        return value.get<Array>().getKeysInt();
    }

    struct IsDefault
    {
        Subschema const* schema;

        template <typename T>
        bool operator()(Override<T> const& _ov) const
        {
            return _ov.hasDefaultValue();
        }

        template <typename T>
        bool operator()(T const&) const
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
        if (getDataType() != DataType::object)
        {
            throw Ent::BadType("In saveNode, an object is expeted");
        }
        json node = toJson();
        node["$schema"] = getSchema()->name;

        std::filesystem::path path = getEntityLib()->getAbsolutePath(_path);
        std::stringstream buffer;
        buffer << node.dump(4);
        std::ofstream file(path);
        if (not file.is_open())
        {
            throw FileSystemError(
                "Trying to open file for write", getEntityLib()->rawdataPath, _path);
        }
        file << buffer.str();
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

    EntityRef Node::getDefaultEntityRef() const
    {
        return getRawEntityRef(OverrideValueLocation::Default).value();
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

    tl::optional<EntityRef> Node::getRawEntityRef(OverrideValueLocation _location) const
    {
        if (value.is<Override<EntityRef>>())
        {
            auto entityRefValue = value.get<Override<EntityRef>>().getRaw(_location);
            return entityRefValue.has_value() ? tl::optional<EntityRef>{entityRefValue} : tl::nullopt;
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
        void operator()(T const& _ov) const
        {
            return _ov.computeMemory(prof);
        }

        void operator()(Null const&) const
        {
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

        mapbox::util::apply_visitor(ApplyToPrefab{_dest.value, _copyMode}, value);
    }

    void Ent::Node::applyAllValuesButPrefab(Node& _dest, CopyMode _copyMode) const
    {
        if (not value.is<Object>() or not _dest.value.is<Object>())
        {
            throw BadType();
        }
        value.get<Object>().applyAllValuesButPrefab(_dest.value.get<Object>(), _copyMode);
    }

    void Ent::Node::changeInstanceOf(char const* _newPrefab)
    {
        Node cloned = *this;
        resetInstanceOf(_newPrefab);
        cloned.applyAllValuesButPrefab(*this, CopyMode::MinimalOverride);
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

} // namespace Ent
