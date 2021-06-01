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

// char schemaPath[2048] = {};

static Ent::Node loadNode(
    Ent::EntityLib const* _entlib,
    Ent::Subschema const& _nodeSchema,
    json const& _data,
    Ent::Node const* _super,
    json const* _default = nullptr);
static std::unique_ptr<Ent::Scene> loadScene(
    Ent::EntityLib const& _entLib,
    Ent::ComponentsSchema const& _schema,
    json const& _entities,
    Ent::Scene const* _super);
static json saveScene(Ent::ComponentsSchema const& _schema, Ent::Scene const& _scene);

namespace Ent
{
    char const* actorStatesSchemaName = "./Scene-schema.json#/definitions/ActorStates";
    char const* colorSchemaName = "./RuntimeComponents.json#/definitions/Color";
    static Ent::Node makeDefaultColorField(EntityLib const& _entlib)
    {
        Ent::Subschema const& colorSchema = AT(_entlib.schema.schema.allDefinitions, colorSchemaName);
        return loadNode(&_entlib, colorSchema, json(), nullptr);
    }

    EntityLib::EntityLib(std::filesystem::path _rootPath, bool _doMergeComponents)
        : rootPath(std::move(_rootPath)) // Read schema and dependencies
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

        json schemaDocument = loadJsonFile(toolsDir / "WildPipeline/Schema/Scene-schema.json");

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

        json dependencies = loadJsonFile(toolsDir / "WildPipeline/Schema/Dependencies.json");
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

    // ************************************ Array *************************************************

    Ent::Array::Array(Subschema const* _schema)
        : schema(_schema)
        , arraySize(0llu, tl::nullopt, tl::nullopt)
    {
        ENTLIB_ASSERT(schema != nullptr);
    }

    bool Ent::Array::hasOverride() const
    {
        return arraySize.isSet()
               || std::any_of(begin(data), end(data), std::mem_fn(&Ent::Node::hasOverride));
    }

    bool Ent::Array::hasPrefabValue() const
    {
        return arraySize.hasPrefab
               || std::any_of(begin(data), end(data), std::mem_fn(&Ent::Node::hasPrefabValue));
    }

    static Ent::Array::KeyType getChildKey(Subschema const* _arraySchema, Node const* _child)
    {
        auto&& meta = _arraySchema->meta.get<Ent::Subschema::ArrayMeta>();
        using namespace Ent;
        switch (hash(meta.overridePolicy))
        {
        case "map"_hash:
        {
            // It is a C++ map.
            // In json it is an array of "2 item array" where the 1st item is the key
            // and can be string, double or integer
            // meta.ordered means the items have to be sorted by the key
            ENTLIB_ASSERT(_child->getSchema()->linearItems.has_value());
            Ent::DataType keyType = _arraySchema->singularItems->get().linearItems->at(0)->type;
#pragma warning(push)
#pragma warning(disable : 4061) // There are switches with missing cases. This is wanted.
            switch (keyType)
            {
            case Ent::DataType::string:
                ENTLIB_ASSERT(_child->at(0llu)->getString() != std::string());
                return _child->at(0llu)->getString();
            case Ent::DataType::entityRef:
                return _child->at(0llu)->getEntityRef().entityPath.c_str();
            case Ent::DataType::number: return _child->at(0llu)->getFloat();
            case Ent::DataType::integer: return _child->at(0llu)->getInt();
            default: throw std::runtime_error("Unknown key type in map " + _arraySchema->name);
            }
        }
        break;
        case "set"_hash:
        {
            // It is a C++ set.
            // In json it is an array of primitive. string, double or integer or oneOf
            // meta.ordered means the items have to be sorted by the key
            Ent::DataType const keyType = _arraySchema->singularItems->get().type;
            switch (keyType)
            {
            // The key is the className string
            case Ent::DataType::oneOf: return _child->getUnionType(); break;
            // The key is the item itself
            case Ent::DataType::string: return _child->getString();
            // The key is the item itself
            case Ent::DataType::number: return _child->getFloat();
            // The key is the item itself
            case Ent::DataType::integer: return _child->getInt();
            default: throw std::runtime_error("Unknown key type in set " + _arraySchema->name);
            }
#pragma warning(pop)
        }
        break;
        default:
            throw std::runtime_error(format(
                "Unknown key type (%s) in schema of %s",
                meta.overridePolicy.c_str(),
                _arraySchema->name.c_str()));
        }
    }

    static void setChildKey(Subschema const* _arraySchema, Node* _child, Ent::Array::KeyType _key)
    {
        auto&& meta = _arraySchema->meta.get<Ent::Subschema::ArrayMeta>();
        using namespace Ent;
        switch (hash(meta.overridePolicy))
        {
        case "map"_hash:
        {
            // It is a C++ map.
            // In json it is an array of "2 item array" where the 1st item is the key
            // and can be string, double or integer
            // meta.ordered means the items have to be sorted by the key
            ENTLIB_ASSERT(_child->getSchema()->linearItems.has_value());
            // ENTLIB_ASSERT(not _child->at(0llu)->hasDefaultValue); // Sometime there is a key in the default value
            Ent::DataType keyType = _arraySchema->singularItems->get().linearItems->at(0)->type;
#pragma warning(push)
#pragma warning(disable : 4061) // There are switches with missing cases. This is wanted.
            switch (keyType)
            {
            case Ent::DataType::string:
                _child->at(0llu)->setString(_key.get<Ent::String>().c_str());
                break;
            case Ent::DataType::entityRef:
                _child->at(0llu)->setEntityRef(Ent::EntityRef{_key.get<Ent::String>()});
                break;
            case Ent::DataType::integer: _child->at(0llu)->setInt(_key.get<int64_t>()); break;
            default:
                throw std::runtime_error(
                    "Can't use this type as key of a map : " + _arraySchema->name);
            }
        }
        break;
        case "set"_hash:
        {
            // It is a C++ set.
            // In json it is an array of primitive. string, double or integer or oneOf
            // meta.ordered means the items have to be sorted by the key
            Ent::DataType const keyType = _arraySchema->singularItems->get().type;
            switch (keyType)
            {
            // The key is the className string
            case Ent::DataType::oneOf: _child->setUnionType(_key.get<Ent::String>().c_str()); break;
            // The key is the item itself
            case Ent::DataType::string: _child->setString(_key.get<Ent::String>().c_str()); break;
            // The key is the item itself
            case Ent::DataType::integer: _child->setInt(_key.get<int64_t>()); break;
            default:
                throw std::runtime_error("Can't use this type in a set : " + _arraySchema->name);
            }
#pragma warning(pop)
        }
        break;
        default:
            throw std::runtime_error(format(
                "Unknown key type (%s) in schema of %s",
                meta.overridePolicy.c_str(),
                _arraySchema->name.c_str()));
        }
    }

    static void cleanSize(Override<uint64_t>& arraySize)
    {
        if (arraySize.hasOverride)
        {
            if (arraySize.hasPrefab)
            {
                if (arraySize.prefabValue == arraySize.overrideValue)
                {
                    arraySize.hasOverride = false;
                }
            }
            else if (arraySize.defaultValue == arraySize.overrideValue)
            {
                arraySize.hasOverride = false;
            }
        }
        if (arraySize.hasPrefab)
        {
            if (arraySize.defaultValue == arraySize.prefabValue)
            {
                arraySize.hasPrefab = false;
            }
        }
    }

    Node* Ent::Array::at(uint64_t _index)
    {
        if (_index < data.size())
        {
            return data[_index].get();
        }
        else
        {
            return nullptr;
        }
    }
    Node const* Ent::Array::at(uint64_t _index) const
    {
        if (_index < data.size())
        {
            return data[_index].get();
        }
        else
        {
            return nullptr;
        }
    }

    bool Ent::Array::mapEraseImpl(KeyType const& _key)
    {
        auto iter = itemMap.find(_key);
        if (iter == itemMap.end())
        {
            return false;
        }
        if (!iter->second.deleted)
        {
            iter->second.deleted = true;
            arraySize.set(arraySize.get() - 1);
            cleanSize(arraySize);
        }
        checkInvariants();
        return true;
    }

    Node* Ent::Array::mapRestoreImpl(KeyType const& _key)
    {
        auto iter = itemMap.find(_key);
        if (iter == itemMap.end())
        {
            return nullptr;
        }
        if (iter->second.deleted)
        {
            iter->second.deleted = false;
            arraySize.set(arraySize.get() + 1);
        }
        checkInvariants();
        return data[iter->second.index].get();
    }

    Node const* Ent::Array::mapGetImpl(KeyType const& _key) const
    {
        auto iter = itemMap.find(_key);
        if (iter == itemMap.end())
        {
            return nullptr;
        }
        if (iter->second.deleted)
        {
            return nullptr;
        }
        return data[iter->second.index].get();
    }

    Ent::Node* Ent::Array::mapInsertImpl(KeyType const& _key)
    {
        ENTLIB_ASSERT_MSG(hasKey(), "Can't 'mapInsert' in simple array. Only in map/set");
        auto iter = itemMap.find(_key);
        if (iter == itemMap.end())
        {
            SubschemaRef const* itemSchema = schema->singularItems.get();
            ENTLIB_ASSERT_MSG(itemSchema, "map/set expect a singularItems");
            auto newNode = loadNode(nullptr, itemSchema->get(), json(), nullptr);
            setChildKey(schema, &newNode, _key);
            return add(OverrideValueLocation::Override, std::move(newNode));
        }
        if (iter->second.deleted)
        {
            iter->second.deleted = false;
            arraySize.set(arraySize.get() + 1);
        }
        checkInvariants();
        return data[iter->second.index].get();
    }

    bool Ent::Array::isErased(KeyType const& _key) const
    {
        auto iter = itemMap.find(_key);
        if (iter == itemMap.end())
        {
            return false;
        }
        return iter->second.deleted;
    }

    bool Ent::Array::mapErase(KeyType const& _key)
    {
        return mapEraseImpl(_key);
    }

    Ent::Node* Ent::Array::mapGet(KeyType const& _key)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
        return const_cast<Ent::Node*>(std::as_const(*this).mapGetImpl(_key));
    }
    Ent::Node const* Ent::Array::mapGet(KeyType const& _key) const
    {
        return mapGetImpl(_key);
    }
    Ent::Node* Ent::Array::mapInsert(KeyType const& _key)
    {
        return mapInsertImpl(_key);
    }

    static void
    incrementSize(OverrideValueLocation loc, Override<uint64_t>& arraySize, bool decrement = false)
    {
        auto operation = [decrement](auto&& v) {
            v = decrement ? v - 1 : v + 1;
        };
        switch (loc)
        {
        case OverrideValueLocation::Default:
            operation(arraySize.defaultValue);
            if (arraySize.hasPrefab)
            {
                operation(arraySize.prefabValue);
            }
            if (arraySize.hasOverride)
            {
                operation(arraySize.overrideValue);
            }
            break;
        case OverrideValueLocation::Prefab:
            if (not arraySize.hasPrefab)
            {
                arraySize.prefabValue = arraySize.defaultValue;
                arraySize.hasPrefab = true;
            }
            operation(arraySize.prefabValue);
            if (arraySize.hasOverride)
            {
                operation(arraySize.overrideValue);
            }
            break;
        case OverrideValueLocation::Override:
            if (not arraySize.hasOverride)
            {
                arraySize.overrideValue =
                    arraySize.hasPrefab ? arraySize.prefabValue : arraySize.defaultValue;
                arraySize.hasOverride = true;
            }
            operation(arraySize.overrideValue);
            break;
        }
        cleanSize(arraySize);
    }

    Ent::Node* Ent::Array::mapAdd(OverrideValueLocation loc, KeyType _key, Node _node)
    {
        ENTLIB_ASSERT(hasKey());
        ENTLIB_ASSERT(mapGet(_key) == nullptr);
        checkInvariants();
        ENTLIB_ASSERT(&schema->singularItems->get() == _node.getSchema());
        data.emplace_back(std::move(_node));
        auto ptr = data.back().get();
        itemMap.emplace(std::move(_key), Deletable{data.size() - 1});
        incrementSize(loc, arraySize);
        checkInvariants();
        return ptr;
    }
    Ent::Node* Ent::Array::mapAdd(OverrideValueLocation loc, char const* _key, Node _node)
    {
        return mapAdd(loc, KeyType(String(_key)), std::move(_node));
    }
    Ent::Node* Ent::Array::mapAdd(OverrideValueLocation loc, int64_t _key, Node _node)
    {
        return mapAdd(loc, KeyType(_key), std::move(_node));
    }

    bool Ent::Array::hasKey() const
    {
        auto&& meta = schema->meta.get<Ent::Subschema::ArrayMeta>();
        return meta.overridePolicy == "map" || meta.overridePolicy == "set";
    }

    Node* Ent::Array::add(OverrideValueLocation loc, Node _node)
    {
        ENTLIB_ASSERT(
            schema->singularItems == nullptr || (&schema->singularItems->get() == _node.getSchema()));
        if (hasKey())
        {
            auto key = getChildKey(schema, &_node);
            return mapAdd(loc, key, std::move(_node));
        }
        else
        {
            data.emplace_back(Ent::make_value<Node>(std::move(_node)));
            Node* ptr = data.back().get();
            incrementSize(loc, arraySize);
            checkInvariants();
            return ptr;
        }
    }

    std::vector<Node const*> Ent::Array::getItemsWithRemoved() const
    {
        std::vector<Node const*> result;
        result.reserve(arraySize.get());
        for (auto&& node : data)
        {
            result.emplace_back(node.get());
        }
        return result;
    }

    std::vector<Node const*> Ent::Array::getItems() const
    {
        checkInvariants();
        std::vector<Node const*> result;
        result.reserve(arraySize.get());
        if (hasKey())
        {
            for (auto&& node : data)
            {
                auto key = getChildKey(schema, node.get());
                auto deleted = itemMap.at(key).deleted;
                if (not deleted)
                {
                    result.emplace_back(node.get());
                }
            }
        }
        else
        {
            for (auto&& node : data)
            {
                result.emplace_back(node.get());
            }
        }
        return result;
    }

    void Ent::Array::checkInvariants() const
    {
        if (data.size() >= 2)
        {
            ENTLIB_ASSERT(data[1].get() != data[0].get());
        }
        size_t deleted = 0;
        if (hasKey())
        {
            ENTLIB_ASSERT(itemMap.size() == data.size());
            deleted =
                (std::size_t)std::count_if(begin(itemMap), end(itemMap), [](auto&& key_wrapper) {
                    return std::get<1>(key_wrapper).deleted;
                });
        }
        ENTLIB_ASSERT(arraySize.get() == data.size() - deleted);
        if (schema->singularItems != nullptr)
        {
            auto singItem = &schema->singularItems->get();
            for (auto& itm : data)
            {
                ENTLIB_ASSERT(singItem == itm->getSchema());
            }
            for (auto& key_item : itemMap)
            {
                auto schem = data[std::get<1>(key_item).index]->getSchema();
                ENTLIB_ASSERT(singItem == schem);
            }
        }
    }

    bool Ent::Array::hasDefaultValue() const
    {
        bool const sizeHasDefault = (!arraySize.hasOverride && !arraySize.hasPrefab);
        if (not sizeHasDefault)
        {
            return false;
        }
        if (hasKey())
        {
            return std::all_of(begin(itemMap), end(itemMap), [this](auto&& key_wrapper) {
                return data[std::get<1>(key_wrapper).index]->hasDefaultValue()
                       and not std::get<1>(key_wrapper).deleted;
            });
        }
        else
        {
            return std::all_of(begin(data), end(data), std::mem_fn(&Node::hasDefaultValue));
        }
    }

    void Ent::Array::pop()
    {
        if (hasKey())
        {
            throw BadArrayType("Can't call 'pop' on map/set array");
            // TODO : Move exception into Node? (Array is internal)
        }
        if (schema->singularItems == nullptr)
        {
            throw BadArrayType("Can't call 'pop' on pair/tuple");
        }
        ENTLIB_ASSERT(not data.empty());
        data.pop_back();
        arraySize.set(arraySize.get() - 1);
        cleanSize(arraySize);
    }

    void Ent::Array::clear()
    {
        if (schema->singularItems == nullptr)
        {
            throw BadArrayType("Can't call 'pop' on pair/tuple");
        }
        if (hasKey())
        {
            for (auto&& key_item : itemMap)
            {
                auto& deletable = std::get<1>(key_item);
                if (!deletable.deleted)
                {
                    deletable.deleted = true;
                    arraySize.set(arraySize.get() - 1);
                    cleanSize(arraySize);
                }
            }
        }
        else
        {
            data.clear();
            arraySize.set(0);
            cleanSize(arraySize);
        }
        checkInvariants();
    }

    bool Ent::Array::empty() const
    {
        return arraySize.get() == 0;
    }

    void Ent::Array::addRemovedPrefab()
    {
        incrementSize(OverrideValueLocation::Prefab, arraySize);
        incrementSize(OverrideValueLocation::Override, arraySize, true);
    }

    void Ent::Array::addRemovedDefault(OverrideValueLocation _removedIn)
    {
        incrementSize(OverrideValueLocation::Default, arraySize);
        incrementSize(_removedIn, arraySize, true);
    }

    void Ent::Array::computeMemory(MemoryProfiler& prof) const
    {
        prof.addMem("Array::data", data.capacity() * sizeof(data.front()));
        for (auto&& item : data)
        {
            item->computeMemory(prof);
            prof.addMem("Array::data::value_ptr", sizeof(Ent::Node));
        }
        prof.addNodes(data.size());
        // TODO : itemMap
    }

    Node* Ent::Array::arrayPush()
    {
        ENTLIB_ASSERT_MSG(not hasKey(), "Can't 'push' in a map or set. Use 'mapInsert'.");
        ENTLIB_ASSERT_MSG(
            schema->singularItems.get() != nullptr,
            "Array is not a singularItems array (Can't push in a pair/tuple)");
        SubschemaRef const* itemSchema = schema->singularItems.get();
        return add(
            OverrideValueLocation::Override, loadNode(nullptr, itemSchema->get(), json(), nullptr));
    }

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

    Node* Union::setUnionType(char const* _type)
    {
        if (getUnionType() != _type)
        {
            Subschema const* subTypeSchema = schema->getUnionTypeWrapper(_type);
            // TODO : Loïc - low prio - Find a way to get the super.
            //   It could be hard because we are no more in the loading phase, so the super is
            //   now delete.
            wrapper = loadNode(nullptr, *subTypeSchema, json(), nullptr);
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

    // ************************************* Object ***********************************************

    struct CompObject
    {
        bool operator()(
            std::pair<char const*, value_ptr<Node>> const& a,
            std::pair<char const*, value_ptr<Node>> const& b) const
        {
            return strcmp(a.first, b.first) < 0;
        }
    };

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
            return value.get<Array>().getRawSize().getRaw(_location);
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

    Node* Node::setUnionType(char const* _type)
    {
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
        void operator()(Override<T>& _ov) const
        {
            _ov.unset();
        }

        template <typename U>
        void operator()(U& _notOverride) const
        {
            (void*)&_notOverride;
            throw BadType();
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
            return (not _ov.hasPrefab) and (not _ov.hasOverride);
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
            Array out(_arr.getSchema());
            for (auto&& item : _arr.getItems())
            {
                Node detached = item->detach();
                auto loc = detached.hasOverride() ? OverrideValueLocation::Override :
                                                    OverrideValueLocation::Default;
                out.add(loc, std::move(detached));
            }
            return Node(std::move(out), schema);
        }

        Node operator()(Object const& _obj) const
        {
            Object out;
            out.nodes.reserve(_obj.size());
            for (auto&& name_node : _obj)
            {
                out.nodes.emplace_back(std::get<0>(name_node), std::get<1>(name_node)->detach());
            }
            std::sort(begin(out), end(out), CompObject());
            return Node(std::move(out), schema);
        }

        Node operator()(Union const& _un) const
        {
            Union detUnion{};
            detUnion.schema = _un.schema;
            detUnion.wrapper = _un.wrapper->detach();
            detUnion.metaData = _un.metaData;
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
            Array out(_arr.getSchema());
            for (auto&& item : _arr.getItems())
            {
                out.add(OverrideValueLocation::Prefab, item->makeInstanceOf());
            }
            return Node(std::move(out), schema);
        }

        Node operator()(Object const& _obj) const
        {
            Object out;
            out.instanceOf = _obj.instanceOf.makeInstanceOf();
            out.nodes.reserve(_obj.size());
            for (auto&& name_node : _obj)
            {
                out.nodes.emplace_back(
                    std::get<0>(name_node), std::get<1>(name_node)->makeInstanceOf());
            }
            std::sort(begin(out), end(out), CompObject());
            return Node(std::move(out), schema);
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
            if (_obj.instanceOf.hasOverride)
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
            return _ov.hasPrefab;
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
            if (_obj.instanceOf.hasPrefab)
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
            value.get<Array>().pop();
        }
        throw BadType();
    }

    void Node::clear()
    {
        if (value.is<Array>())
        {
            value.get<Array>().clear();
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
        if (value.is<Array>())
        {
            return value.get<Array>().mapErase(_key);
        }
        throw BadType();
    }

    Node* Node::mapGet(char const* _key)
    {
        if (value.is<Array>())
        {
            return value.get<Array>().mapGet(_key);
        }
        throw BadType();
    }
    Node const* Node::mapGet(char const* _key) const
    {
        if (value.is<Array>())
        {
            return value.get<Array>().mapGet(_key);
        }
        throw BadType();
    }
    bool Node::mapErase(int64_t _key)
    {
        if (value.is<Array>())
        {
            return value.get<Array>().mapErase(_key);
        }
        throw BadType();
    }
    Node* Node::mapGet(int64_t _key)
    {
        if (value.is<Array>())
        {
            return value.get<Array>().mapGet(_key);
        }
        throw BadType();
    }
    Node const* Node::mapGet(int64_t _key) const
    {
        if (value.is<Array>())
        {
            return value.get<Array>().mapGet(_key);
        }
        throw BadType();
    }

    Node const* Node::mapInsert(int64_t _key)
    {
        if (value.is<Array>())
        {
            return value.get<Array>().mapInsert(_key);
        }
        throw BadType();
    }

    Node const* Node::mapInsert(char const* _key)
    {
        if (value.is<Array>())
        {
            return value.get<Array>().mapInsert(_key);
        }
        throw BadType();
    }

    struct IsDefault
    {
        Subschema const* schema;

        template <typename T>
        bool operator()(Override<T> const& _ov) const
        {
            return not _ov.hasPrefab and not _ov.hasOverride;
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
        std::function<void(EntityRef&)> const& _entityRefPreProc) const
    {
        return EntityLib::dumpNode(
            *getSchema(), *this, _dumpedValueSource, _superKeyIsTypeName, _entityRefPreProc);
    }

    void Node::saveNode(std::filesystem::path const& _path) const
    {
        json node = toJson();
        node["$schema"] = getSchema()->name;

        std::filesystem::path path = getEntityLib()->getAbsolutePath(_path);
        std::ofstream file(path);
        if (not file.is_open())
        {
            throw std::runtime_error(format("Can't open file for write: %ls", path.c_str()));
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
        if (not value.is<Object>())
        {
            throw BadType();
        }

        auto relPath = getEntityLib()->getRelativePath(_prefabNodePath).generic_u8string();
        json nodeData = loadJsonFile(getEntityLib()->getAbsolutePath(_prefabNodePath));
        Node prefabNode = loadNode(getEntityLib(), *getSchema(), nodeData, nullptr);
        (*this) = prefabNode.makeInstanceOf();
        value.get<Object>().instanceOf.set(relPath);
    }

    void Ent::Node::resetInstanceOf()
    {
        if (not value.is<Object>())
        {
            throw BadType();
        }
        (*this) = loadNode(getEntityLib(), *getSchema(), json(), nullptr);
        value.get<Object>().instanceOf.unset();
    }

    EntityLib* Ent::Node::getEntityLib() const
    {
        return schema->rootSchema->entityLib;
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
        bool _isEmbedded, Override<String> _file, size_t _index, std::unique_ptr<Scene> _embedded)
        : isEmbedded(_isEmbedded)
        , file(std::move(_file))
        , index(_index)
        , embedded(std::move(_embedded))
    {
    }

    void SubSceneComponent::makeEmbedded(bool _embedded)
    {
        isEmbedded = _embedded;
        if (_embedded)
        {
            if (embedded == nullptr)
            {
                embedded = std::make_unique<Scene>();
                // TODO: 2020-11-27 @Seb : set embedded owner entity
            }
            file.set(std::string());
        }
        else
        {
            embedded.reset();
        }
    }

    // ********************************* Entity ***************************************************

    static Ent::Node makeDefaultActorStatesField(EntityLib const& _entlib)
    {
        Ent::Subschema const& actorStatesSchema =
            AT(_entlib.schema.schema.allDefinitions, actorStatesSchemaName);
        return Node{Array{&actorStatesSchema}, &actorStatesSchema};
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
        ENTLIB_ASSERT_MSG(
            not hasASuper,
            "A SubEntity of an instance which override a SubEntity in a prefab can't be "
            "renamed. "
            "Check the canBeRenamed method.");
        name.set(std::move(_name));
    }
    bool Entity::canBeRenamed() const
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
            json(), false, _type, loadNode(entlib, compSchema, json(), nullptr), 1, components.size()};
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
        components.erase(_type);
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
            subSceneComponent = std::make_unique<SubSceneComponent>();
        }
        return &(*subSceneComponent);
    }

    void Entity::removeSubSceneComponent()
    {
        if (subSceneComponent != nullptr)
        {
            subSceneComponent.reset();
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
            std::move(instSubSceneComponent),
            actorStates.makeInstanceOf(),
            color.makeInstanceOf(),
            thumbnail.makeInstanceOf(),
            instanceOf.makeInstanceOf(),
            maxActivationLevel.makeInstanceOf());
    }

    bool Entity::hasOverride() const
    {
        // The override is done in comparison with the prefab so
        //     the "InstanceOf" path itself is never considered as overrided.
        if (name.isSet() or color.hasOverride() or thumbnail.isSet() or actorStates.hasOverride())
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
        std::string const prefab = entlib->getRelativePath(_prefab).generic_u8string();
        char const* normTmpl = prefab.c_str();
        std::shared_ptr<Ent::Entity const> templ = entlib->loadEntityReadOnly(normTmpl, nullptr);
        components.clear();
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
        name = templ->getNameValue().makeInstanceOf();
        subSceneComponent = templ->getSubSceneComponent() != nullptr ?
                                templ->getSubSceneComponent()->makeInstanceOf() :
                                nullptr;
        actorStates = templ->getActorStates().makeInstanceOf();
        color = templ->getColorValue().makeInstanceOf();
        thumbnail = templ->getThumbnailValue().makeInstanceOf();
        instanceOf = templ->getInstanceOfValue().makeOverridedInstanceOf(normTmpl);
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
            if (subScene->isEmbedded)
            {
                return subScene->embedded.get();
            }
            // TODO: major 2020-09-26 @Seb: else open non embedded subscene ?
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
            if (subScene->isEmbedded)
            {
                subScene->embedded->setOwnerEntity(this);
            }
        }
    }

    // ********************************* Scene ***************************************************

    Scene::Scene() = default;

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
        auto scene = std::make_unique<Scene>();
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
        auto scene = std::make_unique<Scene>();
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
            if (ent->hasOverride())
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

        uint64_t defaultElementCount = 0;
        uint64_t prefabAdditionalElementCount = 0;
        int instanceAdditionalElementCount = 0;

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
        // std::vector<std::pair<KeyType, Node>> removedItems;
        if (_super != nullptr)
        {
            size_t index = 0;
            // Load all Nodes from the _super (overriden or not)
            for (Ent::Node const* subSuper : _super->getItems())
            {
                json const* subDefault = _default == nullptr ? nullptr : &_default->at(index);
                if (subDefault != nullptr)
                {
                    // item was added in default
                    defaultElementCount++;
                }
                else
                {
                    // item was added in prefab
                    prefabAdditionalElementCount++;
                }
                KeyType key = getKeyNode(subSuper);
                auto loc = subDefault != nullptr ? OverrideValueLocation::Default :
                                                   OverrideValueLocation::Prefab;
                if (instancePropMap.count(key)) // Overriden in instance
                {
                    Ent::Node tmpNode = loadNode(
                        entlib,
                        _nodeSchema.singularItems->get(),
                        *instancePropMap[key],
                        subSuper,
                        subDefault);
                    if (not doRemove(*instancePropMap[key]))
                    {
                        result.emplace_back(key, NodeWrapper{std::move(tmpNode), loc, false});
                    }
                    else
                    {
                        result.emplace_back(key, NodeWrapper{std::move(tmpNode), loc, true});
                        --instanceAdditionalElementCount;
                        // removedItems.emplace_back(key, std::move(tmpNode));
                    }
                    instancePropMap.erase(key); // Later we need to know which item are NOT in the prefab
                }
                else // Not overriden
                {
                    Ent::Node tmpNode = loadNode(
                        entlib, _nodeSchema.singularItems->get(), json(), subSuper, subDefault);
                    ENTLIB_ASSERT(tmpNode.hasOverride() == false);
                    result.emplace_back(key, NodeWrapper{std::move(tmpNode), loc, false});
                }
                ++index;
            }
        }
        else if (_default != nullptr)
        {
            defaultElementCount = _default->size();
            size_t index = 0;
            // Load all Nodes from the _default (overriden or not)
            for (json const& subDefault : *_default)
            {
                json const& key = getKeyJson(subDefault);
                if (instancePropMap.count(key)) // Overriden in instance
                {
                    Ent::Node tmpNode = loadNode(
                        entlib,
                        _nodeSchema.singularItems->get(),
                        *instancePropMap[key],
                        nullptr,
                        &subDefault);
                    if (not doRemove(*instancePropMap[key]))
                    {
                        result.emplace_back(
                            key,
                            NodeWrapper{std::move(tmpNode), OverrideValueLocation::Default, false});
                    }
                    else
                    {
                        // removedItems.emplace_back(key, std::move(tmpNode));
                        result.emplace_back(
                            key,
                            NodeWrapper{std::move(tmpNode), OverrideValueLocation::Default, true});
                        --instanceAdditionalElementCount;
                    }
                    instancePropMap.erase(key); // Later we need to know which item are NOT in the prefab
                }
                else // Not overriden
                {
                    Ent::Node tmpNode = loadNode(
                        entlib, _nodeSchema.singularItems->get(), json(), nullptr, &subDefault);
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
                    auto node = loadNode(entlib, _nodeSchema.singularItems->get(), item, nullptr);
                    result.emplace_back(
                        key, NodeWrapper{std::move(node), OverrideValueLocation::Override, false});
                    instanceAdditionalElementCount++;
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
        Ent::Array arr{&_nodeSchema};
        size_t nodeIdx = 0;
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
            arr.mapAdd(node.loc, key, std::move(node.node));
            if (node.removed)
            {
                arr.mapErase(KeyType(key));
            }
            ++nodeIdx;
        }
        const auto prefabArraySize =
            prefabAdditionalElementCount > 0 ?
                tl::optional<uint64_t>{defaultElementCount + prefabAdditionalElementCount} :
                tl::nullopt;
        const auto instanceArraySize = instanceAdditionalElementCount != 0 ?
                                           tl::optional<uint64_t>{
                                               defaultElementCount + prefabAdditionalElementCount
                                               + instanceAdditionalElementCount} :
                                           tl::nullopt;
        // arr.arraySize = Override<uint64_t>{defaultElementCount, prefabArraySize, instanceArraySize};
        ENTLIB_ASSERT(defaultElementCount == arr.getRawSize().defaultValue);
        ENTLIB_ASSERT(prefabArraySize.has_value() == arr.getRawSize().hasPrefab);
        if (prefabArraySize.has_value())
        {
            ENTLIB_ASSERT(*prefabArraySize == arr.getRawSize().prefabValue);
        }
        ENTLIB_ASSERT(instanceArraySize.has_value() == arr.getRawSize().hasOverride);
        if (instanceArraySize.has_value())
        {
            ENTLIB_ASSERT(*instanceArraySize == arr.getRawSize().overrideValue);
        }
        return arr;
    }
};

static Ent::Node loadNode(
    Ent::EntityLib const* _entlib,
    Ent::Subschema const& _nodeSchema,
    json const& _data,
    Ent::Node const* _super,
    json const* _default)
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
        Ent::Object object;
        // Read the InstanceOf field
        Ent::Node prefabNode;
        auto InstanceOfIter = _data.find("InstanceOf");
        if (InstanceOfIter != _data.end())
        {
            auto nodeFileName = InstanceOfIter->get<std::string>();
            json nodeData = loadJsonFile(_entlib->getAbsolutePath(nodeFileName));
            prefabNode = loadNode(_entlib, _nodeSchema, nodeData, _super, _default);
            _super = &prefabNode;
            Ent::Override<String> tmplPath("", tl::nullopt, InstanceOfIter->get<std::string>());
            object.instanceOf = std::move(tmplPath);
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
            Ent::Node tmpNode = loadNode(_entlib, *propSchemaRef, prop, superProp, defaultProp);
            object.nodes.emplace_back(name.c_str(), std::move(tmpNode));
        }
        std::sort(begin(object), end(object), Ent::CompObject());
        result = Ent::Node(std::move(object), &_nodeSchema);
    }
    break;
    case Ent::DataType::array:
    {
        Ent::Array arr(&_nodeSchema);
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
                            _entlib, _nodeSchema.singularItems->get(), json(), subSuper, defaultItem);
                        auto loc = defaultItem == nullptr ? Ent::OverrideValueLocation::Prefab :
                                                            Ent::OverrideValueLocation::Default;
                        arr.add(loc, std::move(tmpNode));
                        ++index;
                    }
                }
                else if (_default != nullptr)
                {
                    for (json const& subDefault : *_default)
                    {
                        auto& itemSchema = _nodeSchema.singularItems->get();
                        Ent::Node tmpNode =
                            loadNode(_entlib, itemSchema, json(), nullptr, &subDefault);
                        // arr.data.emplace_back(Ent::make_value<Ent::Node>(std::move(tmpNode)));
                        arr.add(Ent::OverrideValueLocation::Default, std::move(tmpNode));
                        ++index;
                    }
                }
                else
                {
                    for (size_t i = 0; i < _nodeSchema.minItems; ++i)
                    {
                        Ent::Node tmpNode =
                            loadNode(_entlib, _nodeSchema.singularItems->get(), json(), nullptr);
                        arr.add(Ent::OverrideValueLocation::Default, std::move(tmpNode));
                        ++index;
                    }
                }
            }
            else // If it is a singularItems and there is _data, we have to use the overridePolicy
            {
                using namespace Ent;
                if (_super != nullptr)
                {
                    ENTLIB_ASSERT(&_nodeSchema == _super->getSchema());
                    auto&& superarr = _super->GetRawValue().get<Ent::Array>();
                    ENTLIB_ASSERT(&_nodeSchema == superarr.getSchema());
                    ENTLIB_ASSERT(_nodeSchema.singularItems != nullptr);
                    ENTLIB_ASSERT(
                        &_nodeSchema.singularItems->get()
                        == &superarr.getSchema()->singularItems->get());
                    auto itemSchema = &_nodeSchema.singularItems->get();
                    for (auto* tmplItem : _super->getItems())
                    {
                        auto itemSchema2 = tmplItem->getSchema();
                        ENTLIB_ASSERT(itemSchema2 == itemSchema);
                    }
                }

                MergeMapOverride mergeMapOverride{_nodeSchema, _data, _super, _default, _entlib};
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
                    //case Ent::DataType::number:
                    //    arr = mergeMapOverride(
                    //        [](json const& item) { return item[0].get<double>(); },
                    //        [](Node const* tmplItem) { return tmplItem->at(0llu)->getFloat(); },
                    //        doRemove);
                    //    break;
                    case Ent::DataType::integer:
                        arr = mergeMapOverride(
                            [](json const& item) { return item[0].get<int64_t>(); },
                            [](Node const* tmplItem) { return tmplItem->at(0llu)->getInt(); },
                            doRemove);
                        break;
                    default:
                        throw std::runtime_error("Unknown key type in map " + _nodeSchema.name);
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
                    //case Ent::DataType::number: // The key is the item itself
                    //    arr = mergeMapOverride(
                    //        [](json const& item) { return item.get<double>(); },
                    //        [](Node const* tmplItem) { return tmplItem->getFloat(); },
                    //        doRemoveDefault);
                    //    break;
                    case Ent::DataType::integer: // The key is the item itself
                        arr = mergeMapOverride(
                            [](json const& item) { return item.get<int64_t>(); },
                            [](Node const* tmplItem) { return tmplItem->getInt(); },
                            doRemoveDefault);
                        break;
                    default:
                        throw std::runtime_error("Unknown key type in set " + _nodeSchema.name);
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
                        Ent::Node tmpNode = loadNode(
                            _entlib, _nodeSchema.singularItems->get(), item, subSuper, subDefault);
                        bool const isDefault = (index < defaultArraySize) or subDefault != nullptr;
                        auto loc = isDefault           ? Ent::OverrideValueLocation::Default :
                                   subSuper != nullptr ? Ent::OverrideValueLocation::Prefab :
                                                         Ent::OverrideValueLocation::Override;
                        arr.add(loc, std::move(tmpNode));
                        ++index;
                    }
                    if (_super != nullptr)
                    {
                        for (size_t i = _super->size(); i < defaultArraySize; ++i)
                        {
                            arr.addRemovedDefault(Ent::OverrideValueLocation::Prefab);
                        }
                        for (size_t i = _data.size(); i < _super->size(); ++i)
                        {
                            arr.addRemovedPrefab();
                        }
                    }
                    else
                    {
                        for (size_t i = _data.size(); i < defaultArraySize; ++i)
                        {
                            arr.addRemovedDefault(Ent::OverrideValueLocation::Override);
                        }
                    }
                    tl::optional<uint64_t> prefabArraySize =
                        (_super != nullptr and _super->size() != defaultArraySize) ?
                            tl::optional<uint64_t>{_super->size()} :
                            tl::nullopt;
                    const uint64_t sizeInPrefab = prefabArraySize.value_or(defaultArraySize);
                    tl::optional<uint64_t> overrideArraySize =
                        _data.size() == sizeInPrefab ? tl::nullopt :
                                                       tl::optional<uint64_t>{_data.size()};
                    //arr.arraySize = Ent::Override<uint64_t>(
                    //    defaultArraySize, prefabArraySize, overrideArraySize);
                    ENTLIB_ASSERT(defaultArraySize == arr.getRawSize().defaultValue);
                    ENTLIB_ASSERT(prefabArraySize.has_value() == arr.getRawSize().hasPrefab);
                    if (prefabArraySize.has_value())
                    {
                        ENTLIB_ASSERT(*prefabArraySize == arr.getRawSize().prefabValue);
                    }
                    ENTLIB_ASSERT(overrideArraySize.has_value() == arr.getRawSize().hasOverride);
                    if (overrideArraySize.has_value())
                    {
                        ENTLIB_ASSERT(*overrideArraySize == arr.getRawSize().overrideValue);
                    }
                }
                break;
                default:
                    throw std::runtime_error(format(
                        "Unknown key type (%s) in schema of %s",
                        meta.overridePolicy.c_str(),
                        _nodeSchema.name.c_str()));
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
                Ent::Node tmpNode = loadNode(_entlib, *sub, prop, subSuper, subDefault);
                arr.add(Ent::OverrideValueLocation::Default, std::move(tmpNode));
                ++index;
            }
            // uint64_t defaultArraySize = _nodeSchema.linearItems->size();
            // arr.arraySize = Ent::Override<uint64_t>(defaultArraySize, tl::nullopt, tl::nullopt);
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
            (_super != nullptr and _super->isSet()) ?
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
                    loadNode(_entlib, schemaTocheck.get(), _data, superUnionDataWrapper, _default);
                Ent::Union un{};
                un.schema = &_nodeSchema;
                un.wrapper = Ent::make_value<Ent::Node>(std::move(dataNode));
                un.metaData = &meta;
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
    std::function<void(EntityRef&)> const& _entityRefPreProc)
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
                // Node const* item = arr.at(wrapper.index);
                if (arr.isErased(getChildKey(&_schema, item)))
                {
                    // TODO : Use the normal dumpNode with a "delete" argument?
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
                        if (item->getSchema()->type != Ent::DataType::oneOf)
                        {
                            throw std::runtime_error(
                                R"(Can't write an erased element in a set of non-union)");
                        }
                        auto& unionMeta = item->getSchema()->meta.get<Ent::Subschema::UnionMeta>();
                        char const* type = item->getUnionType();
                        json tmpNode;
                        tmpNode[unionMeta.typeField] = type;
                        tmpNode[unionMeta.dataField] = json();
                        data.emplace_back(std::move(tmpNode));
                    }
                }
                else
                {
                    if (item->matchValueSource(_dumpedValueSource))
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
                    else if (meta.overridePolicy.empty())
                    {
                        data.emplace_back(json());
                    }
                }
            }
        }
        else
        {
            for (Ent::Node const* item : _node.getItems())
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
                else if (meta.overridePolicy.empty())
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
    Ent::EntityLib const& _entlib,
    Ent::ComponentsSchema const& _schema,
    json const& _entNode,
    Ent::Entity const* _superEntityFromParentEntity)
{
    ENTLIB_ASSERT(
        _superEntityFromParentEntity == nullptr
        or _superEntityFromParentEntity->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);

    tl::optional<std::string> instanceOf;
    auto superEntityOfThisEntity = std::make_unique<Ent::Entity>(_entlib);
    ENTLIB_ASSERT(superEntityOfThisEntity->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);
    bool superIsInit = false;
    Ent::Entity const* superEntity = superEntityOfThisEntity.get();
    ENTLIB_ASSERT(superEntity->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);
    if (_entNode.count("InstanceOf") != 0)
    {
        instanceOf = _entNode.at("InstanceOf").get<std::string>();
        superEntity = _entlib.loadEntityReadOnly(*instanceOf, _superEntityFromParentEntity).get();
        ENTLIB_ASSERT(superEntity->deleteCheck.state_ == Ent::DeleteCheck::State::VALID);
        std::filesystem::path instanceOfPath = *instanceOf;
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
    Ent::Override<String> ovInstanceOf = superInstanceOf.makeOverridedInstanceOf(instanceOf);

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
        ovColor = loadNode(
            &_entlib,
            colorSchema,
            _entNode.at("Color"),
            _superEntityFromParentEntity != nullptr ? &_superEntityFromParentEntity->getColorValue() :
                                                      nullptr);
    }
    else
    {
        ovColor = superEntity->getColorValue().makeInstanceOf();
    }

    // ActorStates
    Ent::Subschema const& actorStatesSchema =
        AT(_entlib.schema.schema.allDefinitions, Ent::actorStatesSchemaName);
    Ent::Node ovActorStates(Ent::Array{&actorStatesSchema}, &actorStatesSchema);
    if (_entNode.contains("ActorStates"))
    {
        ovActorStates = loadNode(
            &_entlib, actorStatesSchema, _entNode.at("ActorStates"), &superEntity->getActorStates());
    }
    else
    {
        ovActorStates = superEntity->getActorStates().makeInstanceOf();
    }

    std::map<std::string, Ent::Component> components;
    std::unique_ptr<Ent::SubSceneComponent> subSceneComponent;
    size_t index = 0;
    if (_entNode.count("Components") != 0)
    {
        json const& componentsNode = _entNode.at("Components");
        for (json const& compNode : componentsNode)
        {
            auto const cmpType = compNode.at("Type").get<std::string>();
            json const& data = compNode.at("Data");
            if (cmpType == "SubScene")
            {
                Ent::SubSceneComponent const* superComp = superEntity->getSubSceneComponent();

                Ent::Override<String> file =
                    superComp != nullptr ? superComp->file : Ent::Override<String>(std::string());

                auto fileInJson = (data.count("File") != 0) ?
                                      tl::optional<std::string>(data["File"].get<std::string>()) :
                                      tl::nullopt;
                file = file.makeOverridedInstanceOf(fileInJson);
                bool isEmbeddedInJson =
                    (data.count("isEmbedded") != 0) ? data["isEmbedded"].get<bool>() : false;
                auto subSceneComp =
                    std::make_unique<Ent::SubSceneComponent>(isEmbeddedInJson, file, index);
                if (subSceneComp->isEmbedded)
                {
                    subSceneComp->embedded = loadScene(
                        _entlib,
                        _schema,
                        data["Embedded"],
                        (superComp != nullptr ? superComp->embedded.get() : nullptr));
                }
                subSceneComponent = std::move(subSceneComp);
            }
            else
            {
                Ent::Component const* superComp = superEntity->getComponent(cmpType.c_str());
                auto const version =
                    compNode.count("Version") != 0u ? compNode.at("Version").get<size_t>() : 0;

                if (_schema.components.count(cmpType) == 0)
                {
                    ENTLIB_LOG_ERROR("Unknown Component type : %s", cmpType.c_str());
                }
                else
                {
                    Ent::Subschema const& compSchema = *AT(_schema.components, cmpType);
                    json rawData = (superComp != nullptr ? superComp->rawData : json());
                    rawData.merge_patch(data);
                    Ent::Component comp{
                        rawData,
                        superComp != nullptr, // has a super component
                        cmpType,
                        loadNode(
                            &_entlib,
                            compSchema,
                            data,
                            (superComp != nullptr ? &superComp->root : nullptr)),
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
        if (superComp != nullptr and subSceneComponent == nullptr)
        {
            subSceneComponent = std::make_unique<Ent::SubSceneComponent>(
                superComp->isEmbedded,
                superComp->file,
                superComp->index,
                superComp->embedded->makeInstanceOf());
        }
    }
    return std::make_unique<Ent::Entity>(
        _entlib,
        std::move(ovName),
        std::move(components),
        std::move(subSceneComponent),
        std::move(ovActorStates),
        std::move(ovColor),
        std::move(ovThumbnail),
        std::move(ovInstanceOf),
        ovMaxActivationLevel);
}

/// Exception thrown when a method is called on legacy data (or vice versa)
struct UnsupportedFormat : std::exception
{
    UnsupportedFormat() = default;
};

struct FileSystemError : public std::runtime_error
{
    static std::string makeWhatMessage(
        std::string const& msg, std::filesystem::path const& path1, std::error_code error)
    {
        return Ent::format(
            "%s %s : '%ls'",
            msg.c_str(),
            Ent::convertANSIToUTF8(error.message()).c_str(),
            path1.c_str());
    }
    FileSystemError(std::string const& msg, std::filesystem::path const& path1, std::error_code error)
        : std::runtime_error(makeWhatMessage(msg, path1, error))
    {
    }
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
        const auto msg = not std::filesystem::exists(absPath) ?
                             format("file doesn't exist: %ls", absPath.c_str()) :
                             format(
                                 "last_write_time(p): invalid argument: %ls (%s)",
                                 absPath.c_str(),
                                 error.message().c_str());
        throw FileSystemError(msg, absPath, error);
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
        json document = loadJsonFile(absPath);
        if (document.count("Objects") and typeid(Type) == typeid(Entity)
            or (document.count("Name") or document.count("InstanceOf") or document.count("Components"))
                   and typeid(Type) == typeid(Scene))
        {
            // we are trying to load a legacy scene through loadScene method
            // or a new Scene format through loadLegacyScene method
            throw UnsupportedFormat();
        }
        if (validationEnabled)
        {
            try
            {
                validate(schema.schema, toolsDir, document);
            }
            catch (...)
            {
                ENTLIB_LOG_ERROR("validating : %ls", absPath.c_str());
                throw;
            }
        }

        std::unique_ptr<Type> entity = load(*this, schema, document, _super);
        auto file = typename Cache::mapped_type{std::move(entity), timestamp};
        auto iter_bool = cache.insert_or_assign(relPath, std::move(file));
        return std::get<0>(iter_bool)->second.data;
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

static std::unique_ptr<Ent::Scene> loadScene(
    Ent::EntityLib const& _entLib,
    Ent::ComponentsSchema const& _schema,
    json const& _entities,
    Ent::Scene const* _super)
{
    auto scene = std::make_unique<Ent::Scene>();

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
            std::unique_ptr<Ent::Entity> ent =
                (instEntNode == nullptr) ?
                    superEnt->makeInstanceOf() :
                    ::loadEntity(_entLib, _schema, *instEntNode, superEnt.get());
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
        std::unique_ptr<Ent::Entity> ent = ::loadEntity(_entLib, _schema, entNode, nullptr);
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
    auto loadFunc = [](Ent::EntityLib const& _entLib,
                       Ent::ComponentsSchema const& _schema,
                       json const& _document,
                       Ent::Scene const* _super) {
        return ::loadScene(_entLib, _schema, _document.at("Objects"), _super);
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
    auto const absPath = getAbsolutePath(_path);
    json jsonData = loadJsonFile(absPath);
    return loadNode(this, _schema, jsonData, nullptr, nullptr);
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

static json saveEntity(Ent::ComponentsSchema const& _schema, Ent::Entity const& _entity)
{
    json entNode;

    // Always save Name since it is use for override
    entNode.emplace("Name", _entity.getNameValue().get().c_str());

    if (_entity.getInstanceOfValue().isSet())
    {
        entNode.emplace("InstanceOf", _entity.getInstanceOfValue().get().c_str());
    }

    Ent::Subschema const& colorSchema = AT(_schema.schema.allDefinitions, Ent::colorSchemaName);
    if (_entity.getColorValue().hasOverride())
    {
        entNode.emplace("Color", Ent::EntityLib::dumpNode(colorSchema, _entity.getColorValue()));
    }

    if (_entity.getThumbnailValue().isSet())
    {
        entNode.emplace("Thumbnail", _entity.getThumbnail());
    }

    if (_entity.getMaxActivationLevelValue().isSet())
    {
        entNode.emplace(
            "MaxActivationLevel", getActivationLevelString(_entity.getMaxActivationLevel()));
    }

    json& componentsNode = entNode["Components"] = json::array();
    std::vector<Ent::Component const*> sortedComp;
    for (auto&& type_comp : _entity.getComponents())
    {
        sortedComp.push_back(&std::get<1>(type_comp));
    }
    Ent::Component subscenePlaceholder{json(), true, "SubScene", Ent::Node(), 1, 0};
    if (Ent::SubSceneComponent const* subscene = _entity.getSubSceneComponent())
    {
        subscenePlaceholder.index = subscene->index;
        sortedComp.push_back(&subscenePlaceholder);
    }
    std::sort(
        begin(sortedComp), end(sortedComp), [](Ent::Component const* cmp, Ent::Component const* cmp2) {
            return cmp->index < cmp2->index;
        });
    for (Ent::Component const* comp : sortedComp)
    {
        if (comp->type == "SubScene")
        {
            Ent::SubSceneComponent const* subscene = _entity.getSubSceneComponent();
            ENTLIB_ASSERT(subscene != nullptr);
            bool const subsceneHasOverride = subscene->hasOverride();
            bool const hasInstanceOf = _entity.getInstanceOf() != nullptr;
            if ((subsceneHasOverride and hasInstanceOf) or not hasInstanceOf)
            {
                json data;
                data.emplace("isEmbedded", subscene->isEmbedded);
                if (subscene->file.isSet())
                {
                    data.emplace("File", subscene->file.get().c_str());
                }
                if (subscene->isEmbedded)
                {
                    data.emplace("Embedded", saveScene(_schema, *subscene->embedded)["Objects"]);
                }

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
                "Data", Ent::EntityLib::dumpNode(*AT(_schema.components, comp->type), comp->root));

            componentsNode.emplace_back(std::move(compNode));
        }
    }
    Ent::Subschema const& actorStatesSchema =
        AT(_schema.schema.allDefinitions, Ent::actorStatesSchemaName);
    if (_entity.getActorStates().hasOverride())
    {
        entNode.emplace(
            "ActorStates", Ent::EntityLib::dumpNode(actorStatesSchema, _entity.getActorStates()));
    }
    return entNode;
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
        detSubSceneComponent = std::make_unique<SubSceneComponent>();
        detSubSceneComponent->isEmbedded = subscene->isEmbedded;
        detSubSceneComponent->file = subscene->file;
        if (subscene->isEmbedded)
        {
            detSubSceneComponent->embedded = std::make_unique<Ent::Scene>();
            for (std::unique_ptr<Ent::Entity> const& subEntity : subscene->embedded->getObjects())
            {
                detSubSceneComponent->embedded->addEntity(subEntity->detachEntityFromPrefab());
            }
        }
    }

    auto detachedColor = getColorValue().detach();
    auto detachedMaxActivationLevel = getMaxActivationLevelValue().detach();
    return std::make_unique<Ent::Entity>(
        *entlib,
        getNameValue().detach().makeOverridedInstanceOf(std::string(getName()) + "_detached"),
        std::move(detComponents),
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
    inst->setInstanceOf(_instanceOf);
    return inst;
}

void Ent::EntityLib::saveEntity(Entity const& _entity, std::filesystem::path const& _entityPath) const
{
    std::filesystem::path entityPath = getAbsolutePath(_entityPath);
    std::ofstream file(entityPath);
    if (not file.is_open())
    {
        constexpr size_t MessSize = 1024;
        std::array<char, MessSize> message = {};
        sprintf_s(message.data(), MessSize, "Can't open file for write: %ls", entityPath.c_str());
        throw std::runtime_error(message.data());
    }
    json document = ::saveEntity(schema, _entity);
    file << document.dump(4);
    file.close();

    // Better to check after save because it is easiest to debug
    if (validationEnabled)
    {
        try
        {
            validateEntity(schema.schema, toolsDir, document);
        }
        catch (...)
        {
            ENTLIB_LOG_ERROR("saving entity : %ls", entityPath.c_str());
            throw;
        }
    }
}

std::filesystem::path Ent::EntityLib::getAbsolutePath(std::filesystem::path const& _path) const
{
    if (_path.is_absolute())
    {
        std::filesystem::path absPath = _path;
        absPath.make_preferred();
        // canonical or weakly_canonical find the original physic drive but we want to keep X:
        return absPath;
    }
    else
    {
        std::filesystem::path absPath = rawdataPath;
        absPath /= _path;
        absPath.make_preferred();
        // canonical or weakly_canonical find the original physic drive but we want to keep X:
        return absPath;
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
                throw std::runtime_error(format(
                    "_path %ls in not inside rawdata %ls", _path.c_str(), rawdataPath.c_str()));
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

static json saveScene(Ent::ComponentsSchema const& _schema, Ent::Scene const& _scene)
{
    json document;

    document.emplace("Version", 2);
    json& objects = document["Objects"];
    objects = json::array();

    for (std::unique_ptr<Ent::Entity> const& ent : _scene.getObjects())
    {
        if (ent->hasOverride())
        {
            objects.emplace_back(::saveEntity(_schema, *ent));
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
    subScene->makeEmbedded(true);
    for (auto&& entity : _scene.getObjects())
    {
        subScene->embedded->addEntity(entity->clone());
    }

    saveEntity(sceneEntity, _scenePath);
}

void Ent::SubSceneComponent::computeMemory(MemoryProfiler& prof) const
{
    prof.currentComp.push_back("SubScene");
    file.computeMemory(prof);
    if (embedded)
    {
        embedded->computeMemory(prof);
    }
    prof.currentComp.pop_back();
}

std::unique_ptr<Ent::SubSceneComponent> Ent::SubSceneComponent::makeInstanceOf() const
{
    std::unique_ptr<Scene> instEmbedded;
    if (embedded)
    {
        instEmbedded = embedded->makeInstanceOf();
    }
    return std::make_unique<SubSceneComponent>(isEmbedded, file, index, std::move(instEmbedded));
}

std::unique_ptr<Ent::SubSceneComponent> Ent::SubSceneComponent::clone() const
{
    std::unique_ptr<Scene> instEmbedded;
    if (embedded)
    {
        instEmbedded = embedded->clone();
    }
    return std::make_unique<SubSceneComponent>(isEmbedded, file, index, std::move(instEmbedded));
}

std::unique_ptr<Ent::Scene> Ent::SubSceneComponent::detachEmbedded()
{
    if (isEmbedded)
    {
        auto scene = std::make_unique<Scene>();
        std::swap(scene, embedded);

        // we don't to swap owners though
        embedded->setOwnerEntity(scene->getOwnerEntity());
        scene->setOwnerEntity(nullptr); // detached scene is not owned by any entity

        return scene;
    }
    return {};
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
