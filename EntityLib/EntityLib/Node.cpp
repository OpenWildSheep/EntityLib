#include "Node.h"

#include <fstream>
#include <sstream>
#include <ciso646>

#include "external/json.hpp"

#include "include/EntityLib.h"
#include "Tools.h"

using namespace nlohmann;

namespace Ent
{

    Node::Node(Value val, Subschema const* _schema)
        : schema(_schema)
        , value(std::move(val))
    {
        updateParents();
    }

    /*Node::Node(Node const& _node)
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
    }*/

    Node::Value copyValue(Node::Value const& value)
    {
        return std::visit(
            [](auto&& typedvalue)
            {
                using Type = std::remove_const_t<std::remove_reference_t<decltype(typedvalue)>>;
                if constexpr (std::is_same_v<Type, ArrayPtr> or std::is_same_v<Type, UnionPtr> or std::is_same_v<Type, ObjectPtr>)
                {
                    using EltType = typename Type::element_type;
                    return Node::Value(std::make_unique<EltType>(*typedvalue));
                }
                else
                {
                    return Node::Value(typedvalue);
                }
            },
            value);
    }

    NodeUniquePtr Node::clone() const
    {
        auto newNode = getEntityLib()->newNode(copyValue(value), schema);
        newNode->parentNode = parentNode;
        newNode->addedInInstance = addedInInstance;
        newNode->updateParents();
        return newNode;
    }

    // Get the NodeRef token to get the _child from the _parent
    static NodeRef computeParentToChildNodeRef(Node const* _parent, Node const* _child)
    {
        return std::visit(
            [_child](auto const& _node) -> NodeRef
            {
                using NodeType = std::remove_const_t<std::remove_reference_t<decltype(_node)>>;
                if constexpr (
                    std::is_same_v<
                        NodeType,
                        ObjectPtr> or std::is_same_v<NodeType, UnionPtr> or std::is_same_v<NodeType, ArrayPtr>)
                {
                    // Call computeNodeRefToChild on any container type
                    return _node->computeNodeRefToChild(_child);
                }
                else
                {
                    ENTLIB_LOGIC_ERROR(
                        R"(In computeParentToChildNodeRef, parent have to contain child!)");
                }
            },
            _parent->GetRawValue());
    }

    Node const* Node::getRootNode() const
    {
        auto rootParent = this;
        while (rootParent->parentNode != nullptr)
        {
            rootParent = rootParent->parentNode;
        }
        return rootParent;
    }

    static bool isUnionSet(Node const* node)
    {
        if (node == nullptr or node->getDataType() != DataType::array)
        {
            return false;
        }
        auto const* schema = node->getSchema();
        return std::get<Subschema::ArrayMeta>(schema->meta).overridePolicy == "set"
               and schema->singularItems->get().type == DataType::oneOf;
    }

    static bool isUnion(Node const* node)
    {
        return node != nullptr and node->getDataType() == DataType::oneOf;
    }

    static bool isMap(Node const* node)
    {
        if (node != nullptr and node->getDataType() == DataType::array)
        {
            auto const& meta = std::get<Subschema::ArrayMeta>(node->getSchema()->meta);
            return meta.overridePolicy == "map";
        }
        return false;
    }

    // Get the path from _root to _child, but reversed.
    static std::vector<std::string> makeNodeRefReversed(Node const* _root, Node const* _child)
    {
        std::vector<std::string> nodeRef;
        if (_child != _root)
        {
            bool isChildOfUnionSet = false;
            Node const* usedParent{};
            ENTLIB_ASSERT(_child->getParentNode() != nullptr);
            if (isUnion(_child->getParentNode()->getParentNode()))
            {
                // Special case of Union.
                // There is an intermediate wrapper Node which doesn't apear in the path.
                if (_child->getParentNode()->getParentNode() != _root
                    and isUnionSet(_child->getParentNode()->getParentNode()->getParentNode()))
                {
                    // Special case of UnionSet.
                    // Don't need to explicit the type of the Union since it is the key of the set
                    isChildOfUnionSet = true;
                }
                usedParent = _child->getParentNode()->getParentNode();
            }
            else if (isMap(_child->getParentNode()->getParentNode()))
            {
                // Special case of Map.
                // There is an intermediate pair Node which doesn't appear in the path.
                usedParent = _child->getParentNode()->getParentNode();
            }
            else
            {
                usedParent = _child->getParentNode();
            }
            // Get the path to parent
            nodeRef = makeNodeRefReversed(_root, usedParent);
            // Insert the path from parent to child at the begining
            if (not isChildOfUnionSet)
            {
                nodeRef.insert(nodeRef.begin(), computeParentToChildNodeRef(usedParent, _child));
            }
        }
        return nodeRef;
    }

    NodeRef Node::makeNodeRef(Node const* _target) const
    {
        auto const* thisRoot = getRootNode();
        auto const* targetRoot = _target->getRootNode();
        if (thisRoot != targetRoot)
        {
            throw UnrelatedNodes();
        }
        // get the two absolute path
        auto&& thisPath = makeNodeRefReversed(thisRoot, this);
        auto&& targetPath = makeNodeRefReversed(targetRoot, _target);

        // Get path from this to target
        std::string relativePath =
            computeRelativePath(std::move(thisPath), std::move(targetPath), false);

        return relativePath;
    }

    Node const* Node::resolveNodeRef(char const* _nodeRef) const
    {
        auto tokenStart = _nodeRef;
        auto const nodeRefEnd = _nodeRef + strlen(_nodeRef);

        auto tokenStop = strchr(tokenStart, '/');
        if (tokenStop == nullptr)
        {
            tokenStop = nodeRefEnd;
        }
        auto current = this;

        auto nextToken = [&tokenStart, &tokenStop, nodeRefEnd]
        {
            if (tokenStop == nodeRefEnd)
            {
                tokenStart = nodeRefEnd;
            }
            else
            {
                tokenStart = tokenStop + 1;
                tokenStop = strchr(tokenStart, '/');
                if (tokenStop == nullptr)
                {
                    tokenStop = nodeRefEnd;
                }
            }
        };

        // For each token in _nodeRef
        std::string token;
        for (; tokenStart != nodeRefEnd; nextToken())
        {
            // Get the child, using the token and the DataType
            token.assign(tokenStart, tokenStop - tokenStart);
            if (token == ".")
            {
                continue;
            }
            ENTLIB_ASSERT(not token.empty());
            switch (current->getDataType())
            {
            case DataType::object:
            {
                current = current->at(token.c_str());
                break;
            }
            case DataType::oneOf:
            {
                if (token != current->getUnionType())
                {
                    throw WrongPath("Wrong union type. Path doesn't exist.");
                }
                current = current->getUnionData();
                break;
            }
            case DataType::array:
            {
                if (current->isMapOrSet())
                {
                    if (current->getSchema()->singularItems->get().type == DataType::oneOf)
                    {
                        // current is UnionSet
                        current = current->mapGet(token.c_str())->getUnionData();
                    }
                    else if (current->getKeyType() == DataType::integer)
                    {
                        // current is any other map/set kind, with an integer key
                        auto const key = atoi(token.c_str());
                        current = current->mapGet(key);
                    }
                    else
                    {
                        // current is any other map/set kind, with a string, or EntityRef key
                        current = current->mapGet(token.c_str());
                    }
                }
                else
                {
                    // current is an array
                    auto const index = atoi(token.c_str());
                    current = current->at(index);
                }
                break;
            }
            case DataType::null: [[fallthrough]];
            case DataType::boolean: [[fallthrough]];
            case DataType::entityRef: [[fallthrough]];
            case DataType::integer: [[fallthrough]];
            case DataType::number: [[fallthrough]];
            case DataType::string: [[fallthrough]];
            case DataType::COUNT: [[fallthrough]];
            default: ENTLIB_LOGIC_ERROR("Unexpected DataType in Node::resolveNodeRef");
            }
        }
        return current;
    }

    Node* Node::resolveNodeRef(char const* _nodeRef)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
        return const_cast<Node*>(std::as_const(*this).resolveNodeRef(_nodeRef));
    }

    NodeRef Node::makeAbsoluteNodeRef() const
    {
        return getRootNode()->makeNodeRef(this);
    }

    std::vector<Node::PrefabInfo> Node::getPrefabHistory() const
    {
        std::vector<PrefabInfo> result;
        // Going up to find the first prefab
        auto parent = this;
        while (parent != nullptr)
        {
            if (auto* obj = std::get_if<ObjectPtr>(&parent->value))
            {
                if ((*obj)->instanceOf.hasOverride())
                {
                    break;
                }
            }

            parent = parent->getParentNode();
        }
        if (parent != nullptr) // A prefab has been found
        {
            auto const* obj = std::get_if<ObjectPtr>(&parent->value)->get();
            if (not obj->instanceOf.get().empty())
            {
                auto const prefab =
                    getEntityLib()->loadNodeReadOnly(*getSchema(), obj->instanceOf.get().c_str());
                NodeRef const prefabToThis = parent->makeNodeRef(this);
                Node const* thisPrefab = prefab->resolveNodeRef(prefabToThis.c_str());
                result = thisPrefab->getPrefabHistory();
                result.emplace_back(obj->instanceOf.get(), prefabToThis, thisPrefab);
            }
            // If instanceOf is empty, keep result empty
        }
        return result;
    }

    struct UpdateParents
    {
        Node* parent;

        template <typename T>
        void operator()(T& _val) const
        {
            _val->setParentNode(parent);
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
        std::visit(UpdateParents{this}, value);
    }

    struct CheckParents
    {
        Node const* parent{};

        template <typename T>
        void operator()(T const& _val) const
        {
            _val->checkParent(parent);
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
        std::visit(CheckParents{this}, value);
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
        return static_cast<DataType>(value.index());
    }

    Node* Node::at(char const* _field)
    {
        if (_field == nullptr)
        {
            throw NullPointerArgument("_field", "Node::at");
        }
        if (std::holds_alternative<ObjectPtr>(value))
        {
            return &Ent::at(*std::get<ObjectPtr>(value), _field);
        }
        throw BadType();
    }
    Node const* Node::at(char const* _field) const
    {
        if (_field == nullptr)
        {
            throw NullPointerArgument("_field", "Node::at");
        }
        if (std::holds_alternative<ObjectPtr>(value))
        {
            return &Ent::at(*std::get<ObjectPtr>(value), _field);
        }
        throw BadType();
    }
    bool Node::count(char const* _field) const
    {
        if (_field == nullptr)
        {
            throw NullPointerArgument("_field", "Node::count");
        }
        if (std::holds_alternative<ObjectPtr>(value))
        {
            return Ent::count(*std::get<ObjectPtr>(value), _field) != 0;
        }
        throw BadType();
    }
    Node* Node::at(size_t _index)
    {
        if (std::holds_alternative<ArrayPtr>(value))
        {
            return std::get<ArrayPtr>(value)->at(_index);
        }
        throw BadType();
    }
    Node const* Node::at(size_t _index) const
    {
        if (std::holds_alternative<ObjectPtr>(value))
        {
            auto iter = begin(*std::get<ObjectPtr>(value));
            std::advance(iter, _index);
            return &(*iter->node);
        }
        if (std::holds_alternative<ArrayPtr>(value))
        {
            return std::get<ArrayPtr>(value)->at(_index);
        }
        throw BadType();
    }
    size_t Node::size() const
    {
        if (std::holds_alternative<ArrayPtr>(value))
        {
            return std::get<ArrayPtr>(value)->size();
        }
        throw BadType();
    }

    std::optional<size_t> Node::getRawSize(OverrideValueLocation _location) const
    {
        if (std::holds_alternative<ArrayPtr>(value))
        {
            return std::get<ArrayPtr>(value)->getRawSize(_location);
        }
        throw BadType();
    }

    Node const* Node::getUnionDataWrapper() const
    {
        if (std::holds_alternative<UnionPtr>(value))
        {
            return std::get<UnionPtr>(value)->wrapper.get();
        }
        throw BadType();
    }

    Node* Node::getUnionData()
    {
        if (std::holds_alternative<UnionPtr>(value))
        {
            return std::get<UnionPtr>(value)->getUnionData();
        }
        throw BadType();
    }
    Node const* Node::getUnionData() const
    {
        if (std::holds_alternative<UnionPtr>(value))
        {
            return std::get<UnionPtr>(value)->getUnionData();
        }
        throw BadType();
    }

    char const* Node::getUnionType() const
    {
        if (std::holds_alternative<UnionPtr>(value))
        {
            return std::get<UnionPtr>(value)->getUnionType();
        }
        throw BadType();
    }

    size_t Node::getUnionTypeIndex() const
    {
        if (std::holds_alternative<UnionPtr>(value))
        {
            return std::get<UnionPtr>(value)->typeIndex;
        }
        throw BadType();
    }

    Node* Node::setUnionType(char const* _type) const
    {
        if (_type == nullptr)
        {
            throw NullPointerArgument("_type", "Node::setUnionType");
        }
        if (std::holds_alternative<UnionPtr>(value))
        {
            return std::get<UnionPtr>(value)->setUnionType(_type);
        }
        throw BadType();
    }

    double Node::getFloat() const
    {
        if (std::holds_alternative<Override<double>>(value))
        {
            return std::get<Override<double>>(value).get();
        }
        if (std::holds_alternative<Override<int64_t>>(value))
        {
            return static_cast<double>(std::get<Override<int64_t>>(value).get());
        }
        throw BadType();
    }
    int64_t Node::getInt() const
    {
        if (std::holds_alternative<Override<int64_t>>(value))
        {
            return std::get<Override<int64_t>>(value).get();
        }
        throw BadType();
    }
    char const* Node::getString() const
    {
        if (std::holds_alternative<Override<String>>(value))
        {
            return std::get<Override<String>>(value).get().c_str();
        }
        throw BadType();
    }
    bool Node::getBool() const
    {
        if (std::holds_alternative<Override<bool>>(value))
        {
            return std::get<Override<bool>>(value).get();
        }
        throw BadType();
    }

    EntityRef Node::getEntityRef() const
    {
        if (std::holds_alternative<Override<EntityRef>>(value))
        {
            return std::get<Override<EntityRef>>(value).get();
        }
        throw BadType();
    }

    Node::Value const& Node::GetRawValue() const
    {
        return value;
    }

    void Node::setFloat(double _val)
    {
        std::get<Override<double>>(value).set(_val);
    }
    void Node::setInt(int64_t _val)
    {
        std::get<Override<int64_t>>(value).set(_val);
    }
    void Node::setString(char const* _val)
    {
        if (_val == nullptr)
        {
            throw NullPointerArgument("_val", "Node::setString");
        }
        std::get<Override<String>>(value).set(_val);
    }
    void Node::setBool(bool _val)
    {
        std::get<Override<bool>>(value).set(_val);
    }

    void Node::setEntityRef(EntityRef _entityRef)
    {
        std::get<Override<EntityRef>>(value).set(std::move(_entityRef));
    }

    struct UnSet
    {
        template <typename T>
        void operator()(std::unique_ptr<T>& _nodeInternal) const
        {
            return _nodeInternal->unset();
        }

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
        std::visit(UnSet{}, value);
    }

    struct IsSet
    {
        template <typename T>
        bool operator()(Override<T> const& _ov) const
        {
            return _ov.isSet();
        }

        template <typename U>
        bool operator()([[maybe_unused]] U const& _notOverride) const
        {
            // throw BadType();
            return true; // Object and Array are always considered as overrided
        }
    };

    bool Node::isSet() const
    {
        return std::visit(IsSet{}, value);
    }

    struct HasDefaultValue
    {
        Subschema const* schema;

        template <typename T>
        bool operator()(std::unique_ptr<T> const& _ov) const
        {
            return _ov->hasDefaultValue();
        }
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
        return std::visit(HasDefaultValue{schema}, value);
    }

    struct Detach
    {
        Subschema const* schema;

        template <typename T>
        NodeUniquePtr operator()(std::unique_ptr<T> const& _ov) const
        {
            return schema->rootSchema->entityLib->newNode(std::make_unique<T>(_ov->detach()), schema);
        }

        template <typename T>
        NodeUniquePtr operator()(T const& _ov) const
        {
            return schema->rootSchema->entityLib->newNode(_ov.detach(), schema);
        }

        NodeUniquePtr operator()(Null const&) const
        {
            return schema->rootSchema->entityLib->newNode(Null{}, schema);
        }
    };

    NodeUniquePtr Node::detach() const
    {
        return std::visit(Detach{schema}, value);
    }

    struct MakeInstanceOf
    {
        Subschema const* schema;

        template <typename T>
        NodeUniquePtr operator()(std::unique_ptr<T> const& _ov) const
        {
            return schema->rootSchema->entityLib->newNode(
                std::make_unique<T>(_ov->makeInstanceOf()), schema);
        }

        template <typename T>
        NodeUniquePtr operator()(T const& _ov) const
        {
            return schema->rootSchema->entityLib->newNode(_ov.makeInstanceOf(), schema);
        }

        NodeUniquePtr operator()(Null const&) const
        {
            return schema->rootSchema->entityLib->newNode(Null{}, schema);
        }
    };

    NodeUniquePtr Node::makeInstanceOf() const
    {
        return std::visit(MakeInstanceOf{schema}, value);
    }

    struct HasOverride
    {
        Subschema const* schema;

        template <typename T>
        bool operator()(std::unique_ptr<T> const& _ov) const
        {
            return _ov->hasOverride();
        }

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
        return std::visit(HasOverride{schema}, value);
    }

    struct HasPrefabValue
    {
        Subschema const* schema;

        template <typename T>
        bool operator()(std::unique_ptr<T> const& _ov) const
        {
            return _ov->hasPrefabValue();
        }

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
        return std::visit(HasPrefabValue{schema}, value);
    }

    bool Node::matchValueSource(OverrideValueSource _source) const
    {
        return not(
            _source == OverrideValueSource::OverrideOrPrefab and hasDefaultValue()
            or _source == OverrideValueSource::Override and not hasOverride());
    }

    std::vector<char const*> Node::getFieldNames() const
    {
        if (std::holds_alternative<ObjectPtr>(value))
        {
            std::vector<char const*> fields;
            for (auto&& f : *std::get<ObjectPtr>(value))
            {
                fields.push_back(f.name);
            }
            return fields;
        }
        throw BadType();
    }

    std::map<char const*, Node const*> Node::getFields() const
    {
        if (std::holds_alternative<ObjectPtr>(value))
        {
            std::map<char const*, Node const*> fieldMap;
            for (auto&& f : *std::get<ObjectPtr>(value))
            {
                fieldMap.emplace(f.name, f.node.get());
            }
            return fieldMap;
        }
        throw BadType();
    }

    char const* Node::getInstanceOf() const
    {
        if (auto const object = std::get_if<ObjectPtr>(&value))
        {
            auto const& instanceOf = (*object)->instanceOf;
            return instanceOf.get().empty() ? nullptr : instanceOf.get().c_str();
        }
        if (auto const unionPtr = std::get_if<UnionPtr>(&value))
        {
            auto const& instanceOf = (*unionPtr)->instanceOf;
            return instanceOf.get().empty() ? nullptr : instanceOf.get().c_str();
        }
        throw BadType();
    }

    std::vector<Node const*> Node::getItems() const
    {
        if (std::holds_alternative<ArrayPtr>(value))
        {
            return std::as_const<Array>(*std::get<ArrayPtr>(value)).getItems();
        }
        throw BadType();
    }

    std::vector<Node*> Node::getItems()
    {
        if (std::holds_alternative<ArrayPtr>(value))
        {
            return std::get<ArrayPtr>(value)->getItems();
        }
        throw BadType();
    }

    Node* Node::push()
    {
        if (std::holds_alternative<ArrayPtr>(value))
        {
            auto& arr = *std::get<ArrayPtr>(value);
            if (arr.hasKey())
            {
                throw BadArrayType("Can't 'push' in a map or set. Use 'mapInsert'.");
            }
            auto const newNode = arr.arrayPush();
            newNode->setParentNode(this);
            newNode->updateParents();
            return newNode;
        }
        throw BadType();
    }
    void Node::pop() const
    {
        if (std::holds_alternative<ArrayPtr>(value))
        {
            auto&& arr = *std::get<ArrayPtr>(value);
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

    void Node::clear() const
    {
        if (std::holds_alternative<ArrayPtr>(value))
        {
            auto&& arr = *std::get<ArrayPtr>(value);
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
        if (std::holds_alternative<ArrayPtr>(value))
        {
            return std::get<ArrayPtr>(value)->empty();
        }
        throw BadType();
    }

    bool Node::mapErase(char const* _key) const
    {
        if (_key == nullptr)
        {
            throw NullPointerArgument("_key", "Node::mapErase");
        }
        checkMap("mapErase");
        if (not std::get<ArrayPtr>(value)->canErase())
        {
            throw BadArrayType(format("Can call 'mapErase' only on map and set of union").c_str());
        }
        return std::get<ArrayPtr>(value)->mapErase(_key);
    }

    Node* Node::mapGet(char const* _key)
    {
        if (_key == nullptr)
        {
            throw NullPointerArgument("_key", "Node::mapGet");
        }
        checkMap("mapGet");
        return std::get<ArrayPtr>(value)->mapGet(_key);
    }
    Node const* Node::mapGet(char const* _key) const
    {
        if (_key == nullptr)
        {
            throw NullPointerArgument("_key", "Node::mapGet");
        }
        checkMap("mapGet");
        return std::get<ArrayPtr>(value)->mapGet(_key);
    }
    bool Node::mapErase(int64_t _key) const
    {
        checkMap("mapErase");
        return std::get<ArrayPtr>(value)->mapErase(_key);
    }
    Node* Node::mapGet(int64_t _key)
    {
        checkMap("mapGet");
        return std::get<ArrayPtr>(value)->mapGet(_key);
    }
    Node const* Node::mapGet(int64_t _key) const
    {
        checkMap("mapGet");
        return std::get<ArrayPtr>(value)->mapGet(_key);
    }

    Node* Node::mapInsert(int64_t _key)
    {
        checkMap("mapInsert");
        Node* newNode = std::get<ArrayPtr>(value)->mapInsert(_key);
        newNode->setParentNode(this);
        newNode->updateParents();
        return newNode;
    }

    Node* Node::mapInsert(char const* _key) const
    {
        if (_key == nullptr)
        {
            throw NullPointerArgument("_key", "Node::mapInsert");
        }
        checkMap("mapInsert");
        Node* newNode = std::get<ArrayPtr>(value)->mapInsert(_key);
        newNode->updateParents();
        return newNode;
    }

    void Node::mapInsert(char const* _key, NodeUniquePtr _newNode) const
    {
        if (_key == nullptr)
        {
            throw NullPointerArgument("_key", "Node::mapInsert");
        }
        checkMap("mapInsert");
        std::get<ArrayPtr>(value)->mapInsert(_key, std::move(_newNode));
    }

    void Node::mapInsert(int64_t _key, NodeUniquePtr _newNode) const
    {
        checkMap("mapInsert");
        std::get<ArrayPtr>(value)->mapInsert(_key, std::move(_newNode));
    }

    Node* Node::mapInsertInstanceOf(char const* _prefabPath)
    {
        if (_prefabPath == nullptr)
        {
            throw NullPointerArgument("_prefabPath", "Node::mapInsertInstanceOf");
        }
        checkMap("mapInsertInstanceOf");
        auto const prefab =
            getEntityLib()->loadNodeReadOnly(**getSchema()->singularItems, _prefabPath);
        Node* newNode = std::get<ArrayPtr>(value)->mapInsert(
            std::get<ArrayPtr>(value)->getChildKey(prefab.get()));
        newNode->resetInstanceOf(_prefabPath);
        newNode->setParentNode(this);
        newNode->updateParents();
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
        auto const newNode = std::get<ArrayPtr>(value)->mapRename(_key, _newkey);
        newNode->setParentNode(this);
        newNode->updateParents();
        return newNode;
    }

    Node* Node::mapRename(int64_t _key, int64_t _newkey) const
    {
        checkMap("mapGet");
        return std::get<ArrayPtr>(value)->mapRename(_key, _newkey);
    }

    void Node::checkMap(char const* _calledMethod) const
    {
        ENTLIB_ASSERT(_calledMethod != nullptr);
        if (not std::holds_alternative<ArrayPtr>(value))
        {
            throw BadType();
        }
        if (not std::get<ArrayPtr>(value)->hasKey())
        {
            throw BadArrayType(format("Can call '%s' only on map/set", _calledMethod).c_str());
        }
    }

    bool Node::isMapOrSet() const
    {
        if (not std::holds_alternative<ArrayPtr>(value))
        {
            return false;
        }
        return std::get<ArrayPtr>(value)->hasKey();
    }

    DataType Node::getKeyType() const
    {
        checkMap("getKeyType");
        return std::get<ArrayPtr>(value)->getKeyType();
    }

    std::vector<String> Node::getKeysString(bool _forceSort) const
    {
        checkMap("getKeysString");
        return std::get<ArrayPtr>(value)->getKeysString(_forceSort);
    }

    std::vector<int64_t> Node::getKeysInt(bool _forceSort) const
    {
        checkMap("getMapKeysInt");
        return std::get<ArrayPtr>(value)->getKeysInt(_forceSort);
    }

    std::vector<NodeUniquePtr> Node::releaseAllElements() const
    {
        if (getDataType() != DataType::array)
        {
            throw BadType("In releaseAllElements, an array is expeted");
        }
        return std::get<ArrayPtr>(value)->releaseAllElements();
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
        return std::visit(IsDefault{schema}, value);
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
            throw BadType("In saveNode, an object is expeted");
        }
        json node = toJson();
        node["$schema"] = format(schemaFormat, getSchema()->name.c_str());

        std::filesystem::path const path = getEntityLib()->getAbsolutePath(_path);
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

    std::optional<double> Node::getRawFloat(OverrideValueLocation _location) const
    {
        if (std::holds_alternative<Override<double>>(value))
        {
            return std::get<Override<double>>(value).getRaw(_location);
        }
        if (std::holds_alternative<Override<int64_t>>(value))
        {
            auto const intValue = std::get<Override<int64_t>>(value).getRaw(_location);
            return intValue.has_value() ? std::optional{static_cast<double>(intValue.value())} :
                                          std::nullopt;
        }
        throw BadType();
    }

    std::optional<int> Node::getRawInt(OverrideValueLocation _location) const
    {
        if (std::holds_alternative<Override<int64_t>>(value))
        {
            auto const opt = std::get<Override<int64_t>>(value).getRaw(_location);
            return opt.has_value() ? std::optional(static_cast<int>(*opt)) : std::nullopt;
        }
        throw BadType();
    }

    std::optional<char const*> Node::getRawString(OverrideValueLocation _location) const
    {
        if (std::holds_alternative<Override<String>>(value))
        {
            auto const strValue = std::get<Override<String>>(value).getRaw(_location);
            return strValue.has_value() ? std::optional{strValue.value().get().c_str()} :
                                          std::nullopt;
        }
        throw BadType();
    }

    std::optional<bool> Node::getRawBool(OverrideValueLocation _location) const
    {
        if (std::holds_alternative<Override<bool>>(value))
        {
            auto boolValue = std::get<Override<bool>>(value).getRaw(_location);
            return boolValue.has_value() ? std::optional<bool>{boolValue} : std::nullopt;
        }
        throw BadType();
    }

    std::optional<EntityRef> Node::getRawEntityRef(OverrideValueLocation _location) const
    {
        if (std::holds_alternative<Override<EntityRef>>(value))
        {
            auto const entityRefValue = std::get<Override<EntityRef>>(value).getRaw(_location);
            return entityRefValue.has_value() ? std::optional<EntityRef>{entityRefValue} :
                                                std::nullopt;
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
        void operator()(std::unique_ptr<T> const& _ov) const
        {
            return _ov->computeMemory(prof);
        }

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
        std::visit(ComputeMem{prof}, value);
    }

    void Node::setInstanceOf(char const* _prefabNodePath)
    {
        resetInstanceOf(_prefabNodePath);
    }

    void Node::resetInstanceOf(char const* _prefabNodePath)
    {
        if (auto const objectPtr = std::get_if<ObjectPtr>(&value))
        {
            (*objectPtr)->resetInstanceOf(_prefabNodePath);
            (*objectPtr)->setParentNode(this);
        }
        else if (auto const unionPtr = std::get_if<UnionPtr>(&value))
        {
            (*unionPtr)->resetInstanceOf(_prefabNodePath);
            (*unionPtr)->setParentNode(this);
        }
        else
        {
            throw BadType();
        }
    }

    void Node::resetInstanceOf() const
    {
        if (not std::holds_alternative<ObjectPtr>(value))
        {
            throw BadType();
        }
        std::get<ObjectPtr>(value)->resetInstanceOf(nullptr);
    }

    EntityLib* Node::getEntityLib() const
    {
        return schema->rootSchema->entityLib;
    }

    struct ApplyToPrefab
    {
        Node::Value& dest;
        CopyMode copyMode;

        template <typename T>
        void operator()(std::unique_ptr<T> const& _value) const
        {
            _value->applyAllValues(*std::get<std::unique_ptr<T>>(dest), copyMode);
        }

        template <typename T>
        void operator()(T const& _value) const
        {
            _value.applyAllValues(std::get<T>(dest), copyMode);
        }

        void operator()(Null const&) const
        {
        }
    };

    void Node::applyAllValues(Node& _dest, CopyMode _copyMode) const
    {
        if (std::holds_alternative<ObjectPtr>(value))
        {
            auto const& object = *std::get<ObjectPtr>(value);
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

        std::visit(ApplyToPrefab{_dest.value, _copyMode}, value);
    }

    void Node::applyAllValuesButPrefab(Node& _dest, CopyMode _copyMode) const
    {
        if (not std::holds_alternative<ObjectPtr>(value)
            or not std::holds_alternative<ObjectPtr>(_dest.value))
        {
            throw BadType();
        }
        std::get<ObjectPtr>(value)->applyAllValuesButPrefab(
            *std::get<ObjectPtr>(_dest.value), _copyMode);
    }

    void Node::applyToPrefab()
    {
        if (getInstanceOf() == nullptr)
        {
            throw ContextException("Called Node::applyToPrefab an a Node without prefab");
        }

        auto* prefabPath = getInstanceOf();
        auto const prefab = getEntityLib()->loadFileAsNode(prefabPath, *getSchema());
        std::map<std::string, Map::KeyType> prefabsKeys;
        std::map<std::string, Map::KeyType> instanceKeys;
        // Save keyFields values
        for (auto&& [fieldName, prop] : getSchema()->properties)
        {
            if (not prop->isKeyField)
            {
                continue;
            }

            if (prop->type == DataType::string)
            {
                prefabsKeys.emplace(fieldName, prefab->at(fieldName.c_str())->getString());
                instanceKeys.emplace(fieldName, at(fieldName.c_str())->getString());
            }
            else if (prop->type == DataType::entityRef)
            {
                prefabsKeys.emplace(
                    fieldName, prefab->at(fieldName.c_str())->getEntityRef().entityPath);
                instanceKeys.emplace(fieldName, at(fieldName.c_str())->getEntityRef().entityPath);
            }
            else if (prop->type == DataType::integer)
            {
                prefabsKeys.emplace(fieldName, prefab->at(fieldName.c_str())->getInt());
                instanceKeys.emplace(fieldName, at(fieldName.c_str())->getInt());
            }
            else
            {
                ENTLIB_LOGIC_ERROR("This key type is not accepted : %d", prop->type);
            }
        }

        // When the value is overridden is the source, we want to make it overridden in the dest => CopyOverride
        applyAllValuesButPrefab(*prefab, CopyMode::CopyOverride);

        auto setToNode = [](Subschema const& prop,
                            Node& node,
                            String const& fieldName,
                            std::map<std::string, Map::KeyType> const& keys)
        {
            if (not prop.isKeyField)
            {
                return;
            }
            if (prop.type == DataType::string)
            {
                node.at(fieldName.c_str())
                    ->setString(std::get<String>(keys.at(fieldName.c_str())).c_str());
            }
            else if (prop.type == DataType::entityRef)
            {
                node.at(fieldName.c_str())
                    ->setEntityRef(EntityRef{std::get<String>(keys.at(fieldName.c_str()))});
            }
            else if (prop.type == DataType::integer)
            {
                node.at(fieldName.c_str())->setInt(std::get<int64_t>(keys.at(fieldName.c_str())));
            }
        };

        // Restore the keyFields values.
        // Asked by the maxscript team because they don't want to change the name this way
        for (auto&& [fieldName, prop] : getSchema()->properties)
        {
            setToNode(*prop, *prefab, fieldName, prefabsKeys);
        }
        // Need to save the prefab before "resetInstanceOf"
        // because "resetInstanceOf" will use the new prefab
        prefab->saveNode(prefabPath);
        resetInstanceOf(prefabPath); // Reset 'this' to a vanilla instance of prefab
        // Override key fiels (Entity name) the the previous value
        for (auto&& [fieldName, prop] : getSchema()->properties)
        {
            setToNode(*prop, *this, fieldName, instanceKeys);
        }
    }

    void Node::changeInstanceOf(char const* _newPrefab)
    {
        auto const cloned = clone();
        resetInstanceOf(_newPrefab);
        cloned->applyAllValuesButPrefab(*this, CopyMode::MinimalOverride);
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
