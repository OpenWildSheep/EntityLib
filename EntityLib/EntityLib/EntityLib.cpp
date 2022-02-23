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
    char const* actorStatesSchemaName = "ActorStates";
    char const* colorSchemaName = "Color";
    char const* entitySchemaName = "Entity";
    char const* sceneSchemaName = "Scene";
    NodeUniquePtr makeDefaultColorField(EntityLib const& _entlib)
    {
        Subschema const& colorSchema = AT(_entlib.schema.schema.allDefinitions, colorSchemaName);
        return _entlib.loadNode(colorSchema, json(), nullptr);
    }

    // canonical or weakly_canonical find the original physic drive but we want to keep X:
    // We also want to add '/' if the path is a letter (X:)
    // We also want path with forward slashes
    static std::filesystem::path very_weakly_canonical(std::filesystem::path const& _path)
    {
        std::filesystem::path c;
        for (auto const& iter : _path)
        {
            if (iter.native() == L"..")
            {
                if (c.empty())
                {
                    c /= iter;
                }
                else
                {
                    c = c.parent_path();
                }
            }
            else if (iter.native() != L".")
            {
                c /= iter;
            }
        }
        if (c.native().back() == L':')
        {
            c = (c.native() + L'/');
        }
        return c.make_preferred();
    }

    EntityLib::EntityLib(std::filesystem::path const& _rootPath, bool _doMergeComponents)
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

        json schemaDocument = loadJsonFile(toolsDir, "WildPipeline/Schema/MergedComponents.json");

        loader.readSchema(&schema.schema, "MergedComponents.json", schemaDocument, schemaDocument);
        schema.schema.entityLib = this;

        auto&& compList = schema.schema.allDefinitions.at("Component").oneOf;

        for (SubschemaRef& comp : *compList)
        {
            auto&& compName = AT(comp->properties, "Type")->constValue->get<std::string>();
            auto&& compSchema = *AT(comp->properties, "Data");
            compSchema.meta = comp->meta;
            schema.components.emplace(compName, &compSchema);
        }

        auto&& actorstateList =
            schema.schema.allDefinitions.at("ResponsiblePointer<ActorState>").oneOf;

        for (SubschemaRef& actorstate : *actorstateList)
        {
            auto&& actorstateName =
                AT(actorstate->properties, "className")->constValue->get<std::string>();
            auto&& actorstateSchema = *AT(actorstate->properties, "classData");
            actorstateSchema.meta = actorstate->meta;
            schema.actorstates.emplace(actorstateName, &actorstateSchema);
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

    static Node const* getSubScene(Node const* _entity)
    {
        if (auto* subScene = _entity->at("Components")->mapGet("SubScene"))
        {
            return subScene->getUnionData()->at("Embedded");
        }
        return nullptr;
    }

    template <typename N> // N : Node or Node const
    static N* getSceneParentEntity(N* _scene)
    {
        N* entity = nullptr;
        ENTLIB_ASSERT(_scene != nullptr);
        ENTLIB_ASSERT(_scene->getDataType() == DataType::array);
        // subSceneData can be null if rootScene was loaded with loadSceneAsNode
        if (auto subSceneData = _scene->getParentNode())
        {
            ENTLIB_ASSERT(subSceneData != nullptr);
            ENTLIB_ASSERT(subSceneData->getDataType() == DataType::object);
            auto subSceneCpnt = subSceneData->getParentNode(); // SubScene
            ENTLIB_ASSERT(subSceneCpnt != nullptr);
            ENTLIB_ASSERT(subSceneCpnt->getDataType() == DataType::object);
            auto cpntUnion = subSceneCpnt->getParentNode(); // Component union
            ENTLIB_ASSERT(cpntUnion != nullptr);
            ENTLIB_ASSERT(cpntUnion->getDataType() == DataType::oneOf);
            auto components = cpntUnion->getParentNode(); // "Components" property (array)
            ENTLIB_ASSERT(components != nullptr);
            ENTLIB_ASSERT(components->getDataType() == DataType::array);
            entity = components->getParentNode(); // Entity
            ENTLIB_ASSERT(entity != nullptr);
            ENTLIB_ASSERT(entity->getDataType() == DataType::object);
            ENTLIB_ASSERT_MSG(
                entity == nullptr || entity->getSchema()->name == entitySchemaName,
                "current has to be an Entity but is not!");
        }
        return entity;
    }

    static Node const* resolveEntityRefRecursive(
        Node const* _current, Node const* _up, Node const* _down, std::vector<std::string>& _path)
    {
        ENTLIB_ASSERT_MSG(
            _current == nullptr or _current->getSchema()->name == entitySchemaName,
            "_current has to be an Entity but is not!");

        auto& head = _path.front();

        if (head == "..")
        {
            // go up in hierarchy
            if (_up == nullptr)
            {
                // broken ref
                return nullptr;
            }
            _current = getSceneParentEntity(_up);
            ENTLIB_ASSERT_MSG(
                _current == nullptr or _current->getSchema()->name == entitySchemaName,
                "_current has to be an Entity but is not!");
            _down = _up;
            _up = _current == nullptr ? nullptr : _current->getParentNode();
        }
        else if (head != ".")
        {
            // go down in child hierarchy named "head"
            if (_down == nullptr)
            {
                // broken ref
                return nullptr;
            }
            _current = _down->mapGet(head.c_str());
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

    Node const* resolveEntityRefImpl(Node const* _current, const EntityRef& _entityRef)
    {
        ENTLIB_ASSERT(_current != nullptr);
        if (_current->getSchema()->name != entitySchemaName)
        {
            throw ContextException("Can't resolveEntityRef because the Node in not an Entity");
        }
        if (_entityRef.entityPath.empty())
        {
            // empty ref
            return nullptr;
        }

        // split around '/'
        std::vector<std::string> parts = splitString(_entityRef.entityPath.c_str(), '/');

        Node const* down = getSubScene(_current);
        Node const* up = _current->getParentNode();

        return resolveEntityRefRecursive(_current, up, down, parts);
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    Node const* EntityLib::resolveEntityRef(Node const* _node, const EntityRef& _entityRef) const
    {
        if (_node->getDataType() == DataType::array) // This is a scene
        {
            if (_entityRef.entityPath.empty())
            {
                // empty ref
                return nullptr;
            }

            // split around '/'
            std::vector<std::string> parts = splitString(_entityRef.entityPath.c_str(), '/');

            Node const* current = getSceneParentEntity(_node);
            Node const* down = _node;
            Node const* up = current == nullptr ? nullptr : current->getParentNode();

            return resolveEntityRefRecursive(current, up, down, parts);
        }
        else
        {
            return resolveEntityRefImpl(_node, _entityRef);
        }
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    Node* EntityLib::resolveEntityRef(Node* _node, const EntityRef& _entityRef) const
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
        return const_cast<Node*>(resolveEntityRef(static_cast<Node const*>(_node), _entityRef));
    }

    Subschema const* EntityLib::getSchema(char const* _schemaName) const
    {
        if (auto iter = schema.schema.allDefinitions.find(_schemaName);
            iter != schema.schema.allDefinitions.end())
        {
            return &iter->second;
        }
        else
        {
            return nullptr;
        }
    }

    Subschema const* EntityLib::getEntitySchema() const
    {
        return getSchema(entitySchemaName);
    }

    Subschema const* EntityLib::getSceneSchema() const
    {
        return getSchema(sceneSchemaName);
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    void EntityLib::setLogicErrorPolicy(LogicErrorPolicy _LogicErrorPolicy)
    {
        s_LogicErrorPolicy = _LogicErrorPolicy;
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    LogicErrorPolicy EntityLib::getLogicErrorPolicy() const
    {
        return s_LogicErrorPolicy;
    }
    static std::tuple<std::vector<std::string>, Node const*, Node const*>
    getAbsolutePathReversed(Node const* _entity)
    {
        ENTLIB_ASSERT_MSG(
            _entity->getSchema()->name == entitySchemaName,
            "_entity has to be an Entity but is not!");
        Node const* current = _entity;
        Node const* rootEntity = nullptr;
        Node const* rootScene = nullptr;
        std::vector<std::string> path;
        while (current != nullptr)
        {
            ENTLIB_ASSERT(current->getDataType() == DataType::object);
            path.emplace_back(current->at("Name")->getString());
            rootEntity = current;
            rootScene = current->getParentNode();
            current = nullptr;
            if (rootScene != nullptr)
            {
                current = getSceneParentEntity(rootScene);
            }
            ENTLIB_ASSERT_MSG(
                current == nullptr || current->getSchema()->name == entitySchemaName,
                "current has to be an Entity but is not!");
        }
        return {std::move(path), rootEntity, rootScene};
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    EntityRef EntityLib::makeEntityRef(Node const& _from, Node const& _to)
    {
        // get the two absolute path
        auto&& [thisPath, thisRootEntity, thisRootScene] = getAbsolutePathReversed(&_from);
        auto&& [entityPath, entityRootEntity, entityRootScene] = getAbsolutePathReversed(&_to);

        // entities should either share a common root scene
        // or a common root entity if they are in a .entity (i.e there is no root scene)
        if (thisRootScene != entityRootScene
            or thisRootEntity == nullptr and thisRootEntity != entityRootEntity)
        {
            // cannot reference unrelated entities
            return {};
        }

        std::string relativePath = computeRelativePath(thisPath, std::move(entityPath), false);

        return {relativePath};
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    Node* EntityLib::getParentEntity(Node* _node)
    {
        ENTLIB_ASSERT_MSG(
            _node == nullptr || _node->getSchema()->name == entitySchemaName,
            "_node has to be an Entity but is not!");
        if (auto parent = _node->getParentNode())
        {
            return getSceneParentEntity(parent);
        }
        else
        {
            return nullptr;
        }
    }
    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    Node const* EntityLib::getParentEntity(Node const* _node)
    {
        return getSceneParentEntity(_node->getParentNode());
    }

    nlohmann::json& EntityLib::readJsonFile(char const* _filepath, bool canonicalize)
    {
        std::filesystem::path const filepath =
            canonicalize ? very_weakly_canonical(_filepath) : _filepath;
        if (auto iter = m_jsonDatabase.find(filepath); iter != m_jsonDatabase.end())
        {
            return iter->second;
        }
        else
        {
            nlohmann::json data = Ent::loadJsonFile(rawdataPath, filepath);
            return m_jsonDatabase.emplace(filepath, std::move(data)).first->second;
        }
    }

    void EntityLib::saveJsonFile(nlohmann::json const* doc, char const* _filepath)
    {
        std::filesystem::path const filepath = very_weakly_canonical(_filepath);
        std::ofstream ofs(rawdataPath / filepath);
        if (not ofs.is_open())
        {
            throw ContextException("Can't open %s for write", filepath.string().c_str());
        }
        ofs << doc->dump(4);
    }

    struct MergeMapOverride
    {
        Subschema const& _nodeSchema;
        json const& _data;
        Node const* _super;
        json const* _default;
        EntityLib const* entlib;

        // Merge the instance array/map/set with the prefab array/map/set and return the resulting Array
        template <typename GetKeyJson, typename GetKeyNode, typename DoRemoveElement>
        Array operator()(
            GetKeyJson&& getKeyJson, ///< Function to get the key in the json (instance)
            GetKeyNode&& getKeyNode, ///< Function to get the key in the Node (prefab)
            DoRemoveElement&& doRemove)
        {
            using namespace Ent;

            auto&& meta = std::get<Subschema::ArrayMeta>(_nodeSchema.meta);
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
                NodeUniquePtr node;
                OverrideValueLocation loc;
                bool removed;

                NodeWrapper(NodeUniquePtr _node, OverrideValueLocation _loc, bool _removed)
                    : node(std::move(_node))
                    , loc(_loc)
                    , removed(_removed)
                {
                }
            };
            std::vector<std::tuple<KeyType, NodeWrapper, bool>> result; // bool => addedInInstance
            if (_super != nullptr)
            {
                size_t index = 0;
                // Load all Nodes from the _super (overriden or not)
                for (Node const* subSuper : _super->getItems())
                {
                    json const* subDefault = _default == nullptr       ? nullptr :
                                             _default->size() <= index ? nullptr :
                                                                         &_default->at(index);
                    KeyType key = getKeyNode(subSuper);
                    auto loc = subDefault != nullptr ? OverrideValueLocation::Default :
                                                       OverrideValueLocation::Prefab;
                    if (instancePropMap.count(key)) // Overriden in instance
                    {
                        auto tmpNode = entlib->loadNode(
                            _nodeSchema.singularItems->get(),
                            *instancePropMap[key],
                            subSuper,
                            subDefault);
                        if (not doRemove(*instancePropMap[key]))
                        {
                            result.emplace_back(
                                key, NodeWrapper{std::move(tmpNode), loc, false}, false);
                        }
                        else
                        {
                            result.emplace_back(
                                key, NodeWrapper{std::move(tmpNode), loc, true}, false);
                        }
                        instancePropMap.erase(
                            key); // Later we need to know which item are NOT in the prefab
                    }
                    else // Not overriden
                    {
                        auto tmpNode = subSuper->makeInstanceOf();
                        ENTLIB_ASSERT(tmpNode->hasOverride() == false);
                        result.emplace_back(key, NodeWrapper{std::move(tmpNode), loc, false}, false);
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
                        auto tmpNode = entlib->loadNode(
                            _nodeSchema.singularItems->get(),
                            *instancePropMap[key],
                            nullptr,
                            &subDefault);
                        bool const isRemoved = doRemove(*instancePropMap[key]);
                        result.emplace_back(
                            key,
                            NodeWrapper{std::move(tmpNode), OverrideValueLocation::Default, isRemoved},
                            false);
                        instancePropMap.erase(
                            key); // Later we need to know which item are NOT in the prefab
                    }
                    else // Not overriden
                    {
                        auto tmpNode = entlib->loadNode(
                            _nodeSchema.singularItems->get(), json(), nullptr, &subDefault);
                        ENTLIB_ASSERT(tmpNode->hasOverride() == false);
                        result.emplace_back(
                            key,
                            NodeWrapper{std::move(tmpNode), OverrideValueLocation::Default, false},
                            false);
                    }
                    ++index;
                }
            }
            // Load items from instance which are not in prefab neither in default (they are new)
            // Use _data (and not instancePropMap) to keep the order of items inside _data
            for (auto const& item : _data)
            {
                auto key = getKeyJson(item);
                auto keyToString = [&key]()
                {
                    std::stringstream ss;
                    ss << key;
                    return ss.str();
                };
                try
                {
                    if (instancePropMap.count(key))
                    {
                        if (not doRemove(*instancePropMap[key]))
                        {
                            auto node =
                                entlib->loadNode(_nodeSchema.singularItems->get(), item, nullptr);
                            result.emplace_back(
                                key,
                                NodeWrapper{std::move(node), OverrideValueLocation::Override, false},
                                true);
                        }
                        // else? New but removed => Let's ignore them.
                    }
                }
                catch (ContextException& ex)
                {
                    ex.addContextMessage("key : %s", keyToString().c_str());
                    throw;
                }
                catch (...)
                {
                    throw WrapperException(
                        std::current_exception(), "key : %s", keyToString().c_str());
                }
            }
            if (ordered)
            {
                std::sort(
                    begin(result),
                    end(result),
                    [](auto&& a, auto&& b) { return std::get<0>(a) < std::get<0>(b); });
            }
            Array arr{entlib, &_nodeSchema};
            for (auto& [key, node, addedInInstance] : result) // node have to be mutable to be moved
            {
                if (arr.mapGet(key) != nullptr)
                {
                    std::stringstream ss;
                    ss << "Twice the same key in map : " << key;
                    throw InvalidJsonData(ss.str().c_str());
                }
                arr.mapInitInsert(node.loc, key, std::move(node.node), addedInInstance);
                if (node.removed)
                {
                    arr.mapErase(KeyType(key));
                }
            }
            return arr;
        }
    };

    NodeUniquePtr EntityLib::loadPrimitive(
        Subschema const& _nodeSchema, json const& _data, Node const* _super, json const* _default) const
    {
        NodeUniquePtr result;

        switch (_nodeSchema.type)
        {
        case DataType::null: result = newNode(Null{}, &_nodeSchema); break;
        case DataType::string:
        {
            std::string def;
            if (_nodeSchema.constValue.has_value())
            {
                // The default value is always the cons value
                def = _nodeSchema.constValue->get<std::string>();
            }
            else if (_default == nullptr)
            {
                // If enum, the first string is the default
                def = _nodeSchema.enumValues.empty() ? std::string() : _nodeSchema.enumValues.front();
            }
            else
            {
                def = _default->get<std::string>();
            }
            std::optional<std::string> const supVal =
                (_super != nullptr and not _super->hasDefaultValue()) ?
                    std::optional<std::string>(_super->getString()) :
                    std::optional<std::string>(std::nullopt);
            std::optional<std::string> const val =
                _data.is_string() ? std::optional<std::string>(_data.get<std::string>()) :
                                    std::optional<std::string>(std::nullopt);
            result = newNode(Override<String>(def, supVal, val), &_nodeSchema);
        }
        break;
        case DataType::boolean:
        {
            bool const def = _default == nullptr ? bool{} : _default->get<bool>();
            std::optional<bool> const supVal = (_super != nullptr and not _super->hasDefaultValue()) ?
                                                   std::optional<bool>(_super->getBool()) :
                                                   std::optional<bool>(std::nullopt);
            std::optional<bool> const val = _data.is_boolean() ?
                                                std::optional<bool>(_data.get<bool>()) :
                                                std::optional<bool>(std::nullopt);
            result = newNode(Override<bool>(def, supVal, val), &_nodeSchema);
        }
        break;
        case DataType::integer:
        {
            int64_t const def = _default == nullptr ? int64_t{} : _default->get<int64_t>();
            std::optional<int64_t> const supVal =
                (_super != nullptr and not _super->hasDefaultValue()) ?
                    std::optional<int64_t>(_super->getInt()) :
                    std::optional<int64_t>(std::nullopt);
            std::optional<int64_t> const val =
                _data.is_number_integer() or _data.is_number_unsigned() ?
                    std::optional<int64_t>(_data.get<int64_t>()) :
                    std::optional<int64_t>(std::nullopt);
            result = newNode(Override<int64_t>(def, supVal, val), &_nodeSchema);
        }
        break;
        case DataType::number:
        {
            double const def = _default == nullptr ? double{} : _default->get<double>();
            std::optional<double> const supVal =
                (_super != nullptr and not _super->hasDefaultValue()) ?
                    std::optional<double>(_super->getFloat()) :
                    std::optional<double>(std::nullopt);
            std::optional<double> const val =
                _data.is_number_float() or _data.is_number_integer() or _data.is_number_unsigned() ?
                    std::optional<double>(_data.get<double>()) :
                    std::optional<double>(std::nullopt);
            result = newNode(Override<double>(def, supVal, val), &_nodeSchema);
        }
        break;
        case DataType::entityRef:
        {
            EntityRef const def =
                _default == nullptr ? EntityRef() : EntityRef{String(_default->get<std::string>())};

            std::optional<EntityRef> const supVal =
                (_super != nullptr
                 and not _super->hasDefaultValue()) ? // Keep the prefab value if there is
                    std::optional<EntityRef>(_super->getEntityRef()) :
                    std::optional<EntityRef>(std::nullopt);

            std::optional<std::string> const refString =
                _data.is_string() ? _data.get<std::string>() :
                                    std::optional<std::string>(std::nullopt);

            std::optional<EntityRef> const val =
                refString.has_value() ? std::optional<EntityRef>(EntityRef{refString.value()}) :
                                        std::optional<EntityRef>(std::nullopt);

            result = newNode(Override<EntityRef>(def, supVal, val), &_nodeSchema);
        }
        break;
        case DataType::object: [[fallthrough]];
        case DataType::array: [[fallthrough]];
        case DataType::oneOf: [[fallthrough]];
        case DataType::COUNT:
        default: ENTLIB_LOGIC_ERROR("Invalid DataType"); break;
        }
        return result;
    }

    /// Get the index of the \b _field in the object \b _data
    static int getFieldIndex(json const& _data, json const& _field)
    {
        int fieldIdx = 0;
        for (auto& [key, value] : _data.items())
        {
            if (&value == &_field)
            {
                return fieldIdx;
            }
            ++fieldIdx;
        }
        ENTLIB_LOGIC_ERROR("Can't find the field in the json object");
    }

    /// @brief Load the prefab file pointed by the "InstanceOf" field
    /// @return
    ///     - The updated "InstanceOf" field
    ///     - The loaded prefabNode (If there is an "InstanceOf" field)
    ///     - The updated _super
    ///     - The index of the "InstanceOf" field
    template <typename UnderlyingType>
    auto loadInstanceOf(
        EntityLib const* _entlib,
        Subschema const& _nodeSchema,
        json const& _data,
        Node const* _super,
        bool _ignoreInstanceOfField)
    {
        Override<String> newInstanceOf;
        std::shared_ptr<Node const> prefabNode;
        uint32_t objInstanceOfFieldIndex = 0;
        if (auto instanceOfIter = _data.find("InstanceOf");
            not _ignoreInstanceOfField and instanceOfIter != _data.end())
        {
            auto nodeFileName = instanceOfIter->get<std::string>();
            if (not nodeFileName.empty())
            {
                // Do not inherit from _super since the override of InstanceOf reset the Entity
                prefabNode = _entlib->loadNodeReadOnly(_nodeSchema, nodeFileName.c_str());
                _super = prefabNode.get();
                if (_super->getSchema() != &_nodeSchema)
                {
                    throw ContextException(
                        "File %s loaded with two different schemas",
                        formatPath(_entlib->rawdataPath, nodeFileName));
                }
                objInstanceOfFieldIndex = getFieldIndex(_data, *instanceOfIter);
                newInstanceOf =
                    std::get<UnderlyingType>(prefabNode->GetRawValue())
                        ->instanceOf.makeOverridedInstanceOf(instanceOfIter->get<std::string>());
            }
            else
            {
                _super = nullptr;
                newInstanceOf = Override<String>("", std::nullopt, "");
            }
        }
        else if (_super != nullptr and _super->getInstanceOf() != nullptr)
        {
            // we inherit from the super's instanceOf
            newInstanceOf = Override<String>("", _super->getInstanceOf(), std::nullopt);
        }
        return std::tuple(newInstanceOf, prefabNode, _super, objInstanceOfFieldIndex);
    }

    NodeUniquePtr EntityLib::loadObject(
        Subschema const& _nodeSchema,
        json const& _data,
        Node const* _super,
        json const* _default,
        bool _ignoreInstanceOf) const
    {
        {
            ENTLIB_ASSERT(_nodeSchema.type == DataType::object);
            std::vector<ObjField> objNodes;
            bool objHasASuper = false;

            // Read the InstanceOf field
            if (_super != nullptr)
            {
                objHasASuper = true;
            }

            Override<String> objInstanceOf;
            std::shared_ptr<Node const> prefabNode;
            uint32_t objInstanceOfFieldIndex = 0;
            std::tie(objInstanceOf, prefabNode, _super, objInstanceOfFieldIndex) =
                loadInstanceOf<ObjectPtr>(this, _nodeSchema, _data, _super, _ignoreInstanceOf);

            // Read the fields in schema
            objNodes.reserve(_nodeSchema.properties.size());
            for (auto&& [name, propSchemaRef] : _nodeSchema.properties)
            {
                Node const* superProp = (_super != nullptr) ? _super->at(name.c_str()) : nullptr;
                json const* refDefault = propSchemaRef.getRefDefaultValues();
                json const* schemaDefault = nullptr;
                if (_default != nullptr)
                {
                    if (auto iter = _default->find(name); iter != _default->end())
                    {
                        schemaDefault = &(*iter);
                    }
                }
                // The less local default value has the priority
                json const* defaultProp = schemaDefault != nullptr ? schemaDefault : refDefault;
                json const emptyJson;
                json const* prop = &emptyJson;
                uint32_t fieldIdx = 0;
                if (_data.count(name) != 0)
                {
                    prop = &_data.at(name);
                    fieldIdx = getFieldIndex(_data, *prop);
                }
                try
                {
                    auto tmpNode = loadNode(*propSchemaRef, *prop, superProp, defaultProp);
                    objNodes.emplace_back(name.c_str(), std::move(tmpNode), fieldIdx);
                }
                catch (ContextException& ex)
                {
                    ex.addContextMessage("In property : %s", name.c_str());
                    throw;
                }
                catch (...)
                {
                    throw WrapperException(
                        std::current_exception(), "In property : %s", name.c_str());
                }
            }
            std::sort(begin(objNodes), end(objNodes), CompObject());
            Object object(
                &_nodeSchema, std::move(objNodes), objInstanceOf, objInstanceOfFieldIndex, objHasASuper);
            auto result = newNode(std::make_unique<Object>(std::move(object)), &_nodeSchema);
            return result;
        }
    }

    NodeUniquePtr EntityLib::loadArray(
        Subschema const& _nodeSchema,
        nlohmann::json const& _data,
        Node const* _super,
        nlohmann::json const* _default) const
    {
        ENTLIB_ASSERT(_nodeSchema.type == DataType::array);

        Array arr(this, &_nodeSchema);
        auto&& meta = std::get<Subschema::ArrayMeta>(_nodeSchema.meta);
        size_t index = 0;
        if (_nodeSchema.singularItems)
        {
            uint64_t defaultArraySize =
                std::max(_nodeSchema.minItems, _default == nullptr ? 0 : _default->size());
            if (_data.is_null()) // No overrided
            {
                if (_super != nullptr)
                {
                    for (Node const* subSuper : _super->getItems())
                    {
                        json const* defaultItem = (_default != nullptr and index < _default->size()) ?
                                                      &_default->at(index) :
                                                      nullptr;
                        auto tmpNode = subSuper->makeInstanceOf();
                        auto loc = defaultItem == nullptr ? OverrideValueLocation::Prefab :
                                                            OverrideValueLocation::Default;
                        arr.initAdd(loc, std::move(tmpNode), false);
                        ++index;
                    }
                    if (not arr.hasKey())
                    {
                        std::optional<uint64_t> prefabArraySize =
                            defaultArraySize == _super->size() ?
                                std::nullopt :
                                std::optional<uint64_t>{_super->size()};
                        arr.arraySetSize(
                            Override<uint64_t>(defaultArraySize, prefabArraySize, std::nullopt));
                    }
                }
                else if (_default != nullptr)
                {
                    for (json const& subDefault : *_default)
                    {
                        auto& itemSchema = _nodeSchema.singularItems->get();
                        auto tmpNode = loadNode(itemSchema, json(), nullptr, &subDefault);
                        arr.initAdd(OverrideValueLocation::Default, std::move(tmpNode), false);
                        ++index;
                    }
                    if (not arr.hasKey())
                    {
                        arr.arraySetSize(
                            Override<uint64_t>(defaultArraySize, std::nullopt, std::nullopt));
                    }
                }
                else
                {
                    for (size_t i = 0; i < _nodeSchema.minItems; ++i)
                    {
                        auto tmpNode = loadNode(_nodeSchema.singularItems->get(), json(), nullptr);
                        arr.initAdd(OverrideValueLocation::Default, std::move(tmpNode), false);
                        ++index;
                    }
                    if (not arr.hasKey())
                    {
                        arr.arraySetSize(
                            Override<uint64_t>(defaultArraySize, std::nullopt, std::nullopt));
                    }
                }
            }
            else // If it is a singularItems and there is _data, we have to use the overridePolicy
            {
                using namespace Ent;
                MergeMapOverride mergeMapOverride{_nodeSchema, _data, _super, _default, this};
                auto doRemoveDefault = [](json const&)
                {
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
                    DataType keyType = _nodeSchema.singularItems->get().linearItems->at(0)->type;
                    auto doRemove = [](json const& item)
                    {
                        return item[1].is_null();
                    };
#pragma warning(push)
#pragma warning(disable : 4061) // There are switches with missing cases. This is wanted.
                    switch (keyType)
                    {
                    case DataType::string:
                        arr = mergeMapOverride(
                            [](json const& item) { return item[0].get<std::string>(); },
                            [](Node const* tmplItem) { return tmplItem->at(0llu)->getString(); },
                            doRemove);

                        break;
                    case DataType::entityRef:
                        arr = mergeMapOverride(
                            [](json const& item) { return item[0].get<std::string>(); },
                            [](Node const* tmplItem)
                            { return tmplItem->at(0llu)->getEntityRef().entityPath; },
                            doRemove);
                        break;
                    case DataType::integer:
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
                    DataType const keyType = _nodeSchema.singularItems->get().type;
                    switch (keyType)
                    {
                    case DataType::oneOf: // The key is the className string
                    {
                        auto const& unionMeta =
                            std::get<Subschema::UnionMeta>(_nodeSchema.singularItems->get().meta);
                        auto doRemoveUnion = [unionMeta](json const& item)
                        {
                            return item.count(unionMeta.dataField) != 0
                                   and item[unionMeta.dataField].is_null();
                        };
                        arr = mergeMapOverride(
                            [&unionMeta](json const& item)
                            {
                                if (auto iter = item.find(unionMeta.typeField); iter != item.end())
                                {
                                    return iter->get_ref<std::string const&>();
                                }
                                else
                                {
                                    throw BadUnionType(
                                        format("Missing field %s", unionMeta.typeField.c_str()).c_str());
                                }
                            },
                            [](Node const* subSuper) { return subSuper->getUnionType(); },
                            doRemoveUnion);
                    }
                    break;
                    case DataType::string: // The key is the item itself
                        arr = mergeMapOverride(
                            [](json const& item) { return item.get<std::string>(); },
                            [&](Node const* tmplItem)
                            {
                                ENTLIB_ASSERT(
                                    tmplItem->getSchema() == &_nodeSchema.singularItems->get());
                                return tmplItem->getString();
                            },
                            doRemoveDefault);
                        break;
                    case DataType::integer: // The key is the item itself
                        arr = mergeMapOverride(
                            [](json const& item) { return item.get<int64_t>(); },
                            [](Node const* tmplItem) { return tmplItem->getInt(); },
                            doRemoveDefault);
                        break;
                    case DataType::object: // The key is a field in the item
                        if (meta.keyField.has_value())
                        {
                            auto& keyProperty =
                                *_nodeSchema.singularItems->get().properties[*meta.keyField];
                            auto doRemoveSet = [](json const& item)
                            {
                                return item.value("__removed__", false);
                            };
                            switch (keyProperty.type)
                            {
                            case DataType::string:
                                arr = mergeMapOverride(
                                    [key = meta.keyField->c_str()](json const& item)
                                    { return item.at(key).get<std::string>(); },
                                    [key = meta.keyField->c_str()](Node const* tmplItem)
                                    { return tmplItem->at(key)->getString(); },
                                    doRemoveSet);
                                break;
                            case DataType::integer:
                                arr = mergeMapOverride(
                                    [key = meta.keyField->c_str()](json const& item)
                                    { return item.at(key).get<int64_t>(); },
                                    [key = meta.keyField->c_str()](Node const* tmplItem)
                                    { return tmplItem->at(key)->getInt(); },
                                    doRemoveSet);
                                break;
                            default:
                                throw ContextException(
                                    "Wrong type for keyField '%s'", meta.keyField->c_str());
                            }
                            break;
                        }
                        [[fallthrough]];
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
                        Node const* subSuper = (_super != nullptr and (_super->size() > index)) ?
                                                   _super->at(index) :
                                                   nullptr;
                        json const* subDefault =
                            (_default != nullptr and (_default->size() > index)) ?
                                &_default->at(index) :
                                nullptr;
                        auto tmpNode =
                            loadNode(_nodeSchema.singularItems->get(), item, subSuper, subDefault);
                        bool const isDefault = (index < defaultArraySize) or subDefault != nullptr;
                        auto loc = isDefault           ? OverrideValueLocation::Default :
                                   subSuper != nullptr ? OverrideValueLocation::Prefab :
                                                         OverrideValueLocation::Override;
                        auto const addedInInstance =
                            _super != nullptr ? subSuper == nullptr : index >= defaultArraySize;
                        arr.initAdd(loc, std::move(tmpNode), addedInInstance);
                        ++index;
                    }
                    std::optional<uint64_t> prefabArraySize =
                        (_super != nullptr and _super->size() != defaultArraySize) ?
                            std::optional<uint64_t>{_super->size()} :
                            std::nullopt;
                    const uint64_t sizeInPrefab = prefabArraySize.value_or(defaultArraySize);
                    std::optional<uint64_t> overrideArraySize =
                        _data.size() == sizeInPrefab ? std::nullopt :
                                                       std::optional<uint64_t>{_data.size()};
                    arr.arraySetSize(
                        Override<uint64_t>(defaultArraySize, prefabArraySize, overrideArraySize));
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
            for (SubschemaRef const& sub : *_nodeSchema.linearItems)
            {
                Node const* subSuper =
                    (_super != nullptr and _super->size() > index) ? _super->at(index) : nullptr;
                json const* subDefault = (_default != nullptr and _default->size() > index) ?
                                             &_default->at(index) :
                                             nullptr;
                json const emptyJson;
                json const& prop = _data.size() > index ? _data.at(index) : emptyJson;
                auto tmpNode = loadNode(*sub, prop, subSuper, subDefault);
                arr.arrayInitPush(std::move(tmpNode), false); // It is a tuple, so the item is never new
                ++index;
            }
            uint64_t defaultArraySize = _nodeSchema.linearItems->size();
            arr.arraySetSize(Override<uint64_t>(defaultArraySize, std::nullopt, std::nullopt));
        }
        return newNode(std::make_unique<Array>(std::move(arr)), &_nodeSchema);
    }

    NodeUniquePtr EntityLib::loadUnion(
        Subschema const& _nodeSchema, json const& _data, Node const* _super, json const* _default) const
    {
        ENTLIB_ASSERT(_nodeSchema.type == DataType::oneOf);

        NodeUniquePtr result;

        std::shared_ptr<Node const> prefabNode;
        Override<String> unionInstanceOf;
        [[maybe_unused]] uint32_t objInstanceOfFieldIndex = 0;
        std::tie(unionInstanceOf, prefabNode, _super, objInstanceOfFieldIndex) =
            loadInstanceOf<UnionPtr>(this, _nodeSchema, _data, _super, false);

        auto&& meta = std::get<Subschema::UnionMeta>(_nodeSchema.meta);
        std::string const& typeField = meta.typeField;
        if (typeField.empty())
        {
            auto message = format("%s has no meta/unionTypeField", _nodeSchema.name.c_str());
            throw IllFormedSchema(message.c_str());
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
                dataType = _nodeSchema.getUnionDefaultTypeName();
            }
        }
        bool typeFound = false;
        int subSchemaIndex = -1;
        for (SubschemaRef const& schemaTocheck : *_nodeSchema.oneOf)
        {
            ++subSchemaIndex;
            auto propIter = schemaTocheck->properties.find(typeField);
            if (propIter == schemaTocheck->properties.end())
            {
                auto message = format(
                    "%dth subschema of %s has no typeField named '%s'",
                    subSchemaIndex,
                    _nodeSchema.name.c_str(),
                    typeField.c_str());
                throw IllFormedSchema(message.c_str());
            }
            auto&& schemaType = propIter->second.get().constValue->get<std::string>();
            if (schemaType == dataType)
            {
                Node const* superUnionDataWrapper =
                    _super != nullptr ? _super->getUnionDataWrapper() : nullptr;
                ENTLIB_ASSERT(
                    superUnionDataWrapper == nullptr
                    or &schemaTocheck.get() == superUnionDataWrapper->getSchema());
                if (_default != nullptr)
                {
                    if (auto typeInDefault = _default->find(typeField);
                        typeInDefault != _default->end())
                    {
                        if (typeInDefault->get_ref<std::string const&>() != schemaType)
                        {
                            _default = nullptr;
                        }
                    }
                }
                // We know it is an object (the union wrapper)
                // Dont need to loads the InstanceOf since it was already loaded at the Union level
                auto dataNode =
                    loadObject(schemaTocheck.get(), _data, superUnionDataWrapper, _default, true);
                Union un{
                    this,
                    &_nodeSchema,
                    std::move(dataNode),
                    size_t(subSchemaIndex),
                    std::move(unionInstanceOf)};
                result = newNode(std::make_unique<Union>(std::move(un)), &_nodeSchema);
                typeFound = true;
            }
        }
        if (not typeFound)
        {
            throw BadType(Ent::staticFormat(
                "Can't find type %s in schema %s", dataType.c_str(), _nodeSchema.name.c_str()));
        }
        return result;
    }

    NodeUniquePtr EntityLib::loadNode(
        Subschema const& _nodeSchema, json const& _data, Node const* _super, json const* _default) const
    {
        ENTLIB_ASSERT(_super == nullptr or &_nodeSchema == _super->getSchema());

        if (_default == nullptr and not _nodeSchema.defaultValue.is_null())
        {
            _default = &_nodeSchema.defaultValue;
        }

        switch (_nodeSchema.type)
        {
        case DataType::null: [[fallthrough]];
        case DataType::string: [[fallthrough]];
        case DataType::boolean: [[fallthrough]];
        case DataType::integer: [[fallthrough]];
        case DataType::number: [[fallthrough]];
        case DataType::entityRef: return loadPrimitive(_nodeSchema, _data, _super, _default);
        case DataType::object: return loadObject(_nodeSchema, _data, _super, _default);
        case DataType::array: return loadArray(_nodeSchema, _data, _super, _default);
        case DataType::oneOf: return loadUnion(_nodeSchema, _data, _super, _default);
        case DataType::COUNT: [[fallthrough]];
        default: ENTLIB_LOGIC_ERROR("Invalid DataType"); break;
        }
    }

    static double round_n(double value, double multiplier)
    {
        const auto scaled_value = value * multiplier;
        return std::round(scaled_value) / multiplier;
    }

    static double truncFloat(float _val)
    {
        if (not std::isnormal(_val))
        {
            return _val;
        }

        double result{};
        for (size_t multiplier = 0; multiplier < 100; ++multiplier)
        {
            result = round_n(_val, pow(10, multiplier));
            if (float(result) == _val)
            {
                break;
            }
        }
        ENTLIB_ASSERT(float(result) == _val);

        return result;
    }

    json EntityLib::dumpNode(
        Subschema const& _schema,
        Node const& _node,
        OverrideValueSource _dumpedValueSource,
        bool _superKeyIsTypeName,
        std::function<void(EntityRef&)> const& _entityRefPreProc,
        bool _saveUnionIndex,
        bool _forceWriteKey)
    {
        json data;
        switch (_schema.type)
        {
        case DataType::null: break;
        case DataType::string: data = _node.getString(); break;
        case DataType::boolean: data = _node.getBool(); break;
        case DataType::integer: data = _node.getInt(); break;
        case DataType::number:
            if (std::get<Subschema::NumberMeta>(_node.getSchema()->meta).bitDepth == 32)
            {
                data = truncFloat(static_cast<float>(_node.getFloat()));
            }
            else
            {
                data = _node.getFloat();
            }
            break;
        case DataType::object:
        {
            data = json::object();
            struct JsonField
            {
                char const* name = nullptr;
                json data;
                uint32_t index = 0;

                // TODO : Remove when C++20
                JsonField(char const* _name, json _data, uint32_t _index = 0)
                    : name(_name)
                    , data(std::move(_data))
                    , index(_index)
                {
                }
            };
            std::vector<JsonField> fieldMap;
            auto& internObj = std::get<ObjectPtr>(_node.value);
            for (auto const& [name, sub] : _schema.properties)
            {
                Node const* subNode = _node.at(name.c_str());
                // If the field isKeyField, write the field even if it is not overriden
                if (subNode->matchValueSource(_dumpedValueSource) or sub.get().isKeyField)
                {
                    json subJson = dumpNode(
                        *sub, *subNode, _dumpedValueSource, _superKeyIsTypeName, _entityRefPreProc);
                    // handle "Super" special key
                    if (_superKeyIsTypeName and name == "Super")
                    {
                        const auto* typeName = getRefTypeName(subNode->getTypeName());
                        auto const fieldIdx = internObj->at(name.c_str()).fieldIdx;
                        fieldMap.emplace_back(typeName, std::move(subJson), fieldIdx);
                    }
                    else
                    {
                        auto const fieldIdx = internObj->at(name.c_str()).fieldIdx;
                        fieldMap.emplace_back(name.c_str(), std::move(subJson), fieldIdx);
                    }
                }
            }
            auto const& instanceOf = std::get<ObjectPtr>(_node.value)->instanceOf;
            if (_dumpedValueSource == OverrideValueSource::Override and instanceOf.isSet())
            {
                fieldMap.emplace_back(
                    "InstanceOf", instanceOf.get(), internObj->instanceOfFieldIndex);
            }
            std::sort(
                begin(fieldMap),
                end(fieldMap),
                [](JsonField const& a, JsonField const& b)
                {
                    if (a.index != b.index)
                    {
                        return a.index < b.index;
                    }
                    else
                    {
                        return strcmp(a.name, b.name) < 0;
                    }
                });
            for (JsonField& field : fieldMap)
            {
                data[field.name] = std::move(field.data);
            }
        }
        break;
        case DataType::array:
        {
            data = json::array();
            auto&& meta = std::get<Subschema::ArrayMeta>(_schema.meta);
            bool const fullWrite = meta.isMapItem;
            auto const& arr = *std::get<ArrayPtr>(_node.value);
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

                                if (item->getSchema()->type == DataType::oneOf)
                                {
                                    auto& unionMeta =
                                        std::get<Subschema::UnionMeta>(item->getSchema()->meta);
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
                                    item->getSchema()->type == DataType::object
                                    and meta.keyField.has_value())
                                {
                                    if (std::get<ObjectPtr>(item->GetRawValue())->hasASuper)
                                    {
                                        json tmpNode;
                                        auto key = arr.getChildKey(item);
                                        std::visit(
                                            [&](auto&& k) { tmpNode[*meta.keyField] = k; }, key);
                                        tmpNode["__removed__"] = true;
                                        data.emplace_back(std::move(tmpNode));
                                    }
                                    // [[fallthrough]]
                                }
                                else
                                {
                                    throw ContextException(
                                        R"(Can't write an erased element in a set of non-union)");
                                }
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
                            _entityRefPreProc,
                            _saveUnionIndex,
                            meta.overridePolicy == "set"); // White key if in set
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
        case DataType::entityRef:
        {
            EntityRef ref = _node.getEntityRef();
            if (_entityRefPreProc)
            {
                _entityRefPreProc(ref);
            }
            data = ref.entityPath.c_str();
        }
        break;
        case DataType::oneOf:
        {
            auto&& meta = std::get<Subschema::UnionMeta>(_schema.meta);
            data = json::object();
            auto&& un = *std::get<UnionPtr>(_node.GetRawValue());
            if (_dumpedValueSource == OverrideValueSource::Override and un.instanceOf.isSet())
            {
                data["InstanceOf"] = un.instanceOf.get();
            }
            // If it has no indexField, it is a (Responsible)pointer type.
            // The default (first) type is not explicited by the coder, so it can change accidentally.
            // This is why it is better to always write the type. (And also Wild expect it)
            auto const isPointerType = not meta.indexField.has_value();
            if (un.typeOverriden or un.wrapper->hasOverride() or _forceWriteKey or isPointerType)
            {
                Node const* dataInsideUnion = _node.getUnionData();
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
        }
        break;
        case DataType::COUNT:
        default: ENTLIB_LOGIC_ERROR("DataType is Invalid!!"); break;
        }
        return data;
    }

    /// Exception thrown when a method is called on legacy data (or vice versa)
    struct UnsupportedFormat : ContextException
    {
        UnsupportedFormat() = default;
    };

    template <typename Type, typename Cache, typename ValidateFunc, typename LoadFunc>
    std::shared_ptr<Type const> EntityLib::loadEntityOrScene(
        std::filesystem::path const& _path,
        Cache& cache,
        ValidateFunc&& validate,
        LoadFunc&& load,
        Type const* _super) const
    {
        auto const absPath = getAbsolutePath(_path);
        std::filesystem::path relPath = std::filesystem::relative(absPath, rawdataPath);
        if (relPath.empty() || (*relPath.begin() == ".."))
        {
            relPath = absPath;
        }
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
                if (validationEnabled)
                {
                    validate(schema.schema, toolsDir, document);
                }

                auto entity = load(*this, document, _super);
                auto file = typename Cache::mapped_type{std::move(entity), timestamp};
                auto [newiter, inserted] = cache.insert_or_assign(relPath, std::move(file));
                return newiter->second.data;
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

    std::shared_ptr<Node const> EntityLib::loadNodeReadOnly(
        Subschema const& _nodeSchema, char const* _nodePath, Node const* _super) const
    {
        auto loadFunc =
            [&_nodeSchema](EntityLib const& _entLib, json const& _document, Node const* _super)
        {
            return _entLib.loadNode(_nodeSchema, _document, _super);
        };
        auto validate = [&_nodeSchema](
                            Schema const& _schema,
                            std::filesystem::path const& _toolsDir,
                            nlohmann::json const& _entity)
        {
            // Validate with the right type of the Node
            return validateJson(_schema, _toolsDir, _entity, _nodeSchema.name.c_str());
        };
        return loadEntityOrScene<Node>(_nodePath, m_nodeCache, validate, loadFunc, _super);
    }

    std::shared_ptr<Node const> EntityLib::loadNodeEntityReadOnly(char const* _nodePath) const
    {
        return loadNodeReadOnly(*getSchema(entitySchemaName), _nodePath);
    }

    NodeUniquePtr EntityLib::loadEntityAsNode(std::filesystem::path const& _entityPath) const
    {
        Subschema const& entitySchema = AT(schema.schema.allDefinitions, entitySchemaName);
        return loadFileAsNode(_entityPath, entitySchema);
    }

    NodeUniquePtr EntityLib::loadSceneAsNode(std::filesystem::path const& _scenePath) const
    {
        Subschema const& entitySchema = AT(schema.schema.allDefinitions, entitySchemaName);
        auto ent = loadNodeReadOnly(entitySchema, _scenePath.string().c_str());
        if (auto* components = ent->at("Components"))
        {
            if (auto subscene = components->mapGet("SubScene"))
            {
                if (auto scene = subscene->getUnionData()->at("Embedded"))
                {
                    return scene->clone();
                }
            }
        }
        Subschema const& sceneSchema = AT(schema.schema.allDefinitions, sceneSchemaName);
        m_nodeCache.erase(getRelativePath(_scenePath));
        auto scene = loadNodeReadOnly(sceneSchema, _scenePath.string().c_str());
        return scene->at("Objects")->clone();
    }

    NodeUniquePtr
    EntityLib::loadFileAsNode(std::filesystem::path const& _path, Subschema const& _schema) const
    {
        return loadNodeReadOnly(_schema, _path.string().c_str())->clone();
    }

    NodeUniquePtr EntityLib::loadFileAsNode(std::filesystem::path const& _nodePath) const
    {
        auto loadFunc =
            [this, &_nodePath](EntityLib const& _entLib, json const& _document, Node const* _super)
        {
            Subschema const* schema = nullptr;
            std::string schemaFound;
            bool tryToLower = false;
            if (auto schemaName = _document.find("$schema"); schemaName != _document.end())
            {
                // If $schema found, use it
                schemaFound = getRefTypeName(schemaName->get_ref<json::string_t const&>().c_str());
            }
            else if (auto schemaName2 = _document.find("schema_name"); schemaName2 != _document.end())
            {
                // If schema_name found, use it
                schemaFound = getRefTypeName(schemaName2->get_ref<json::string_t const&>().c_str());
            }
            else if (_nodePath.extension().string() == ".entity" or _nodePath.extension().string() == ".scene")
            {
                // If extention is entity or scene, we know it is an Entity
                schemaFound = "Entity";
            }
            else
            {
                // Search in filename
                schemaFound = _nodePath.stem().extension().string(); // Get pre-extention
                schemaFound.erase(schemaFound.begin()); // remove dot
                schemaFound = strToLower(schemaFound);
                tryToLower = true;
            }
            if (auto dotPos = schemaFound.find('.'); dotPos != std::string::npos)
            {
                schemaFound.erase(dotPos);
            }
            for (auto const& [name, schema2] : this->schema.schema.allDefinitions)
            {
                // Try to lower only if the type was extracted from a file name
                if ((tryToLower and strToLower(getRefTypeName(name.c_str())) == schemaFound)
                    or (not tryToLower and getRefTypeName(name.c_str()) == schemaFound))
                {
                    schema = &schema2;
                    break;
                }
            }

            if (schema == nullptr)
            {
                throw UnknownSchema(_entLib.rawdataPath.string().c_str(), _nodePath.string().c_str());
            }
            if (validationEnabled)
            {
                // Validate with the right type of the Node
                validateJson(
                    _entLib.schema.schema, _entLib.toolsDir, _document, schema->name.c_str());
            }
            return _entLib.loadNode(*schema, _document, _super);
        };
        auto validate = [](Schema const&, std::filesystem::path const&, nlohmann::json const&) {
        };
        return loadEntityOrScene<Node>(_nodePath, m_nodeCache, validate, loadFunc, nullptr)->clone();
    }

    NodeUniquePtr EntityLib::makeNodeInstanceOf(char const* _schemaName, char const* _prefab) const
    {
        auto node = makeNode(_schemaName);
        node->resetInstanceOf(_prefab);
        return node;
    }

    NodeUniquePtr EntityLib::makeEntityNodeInstanceOf(char const* _prefab) const
    {
        return makeNodeInstanceOf(entitySchemaName, _prefab);
    }

    NodeUniquePtr EntityLib::makeNode(char const* _schemaName) const
    {
        return loadNode(*getSchema(_schemaName), json(), nullptr);
    }

    NodeUniquePtr EntityLib::newNode(Node::Value val, Subschema const* _subschema) const
    {
        return std::unique_ptr<Node, NodeDeleter>(new (nodePool.alloc())
                                                      Node(std::move(val), _subschema));
    }

    PropImplPtr EntityLib::newPropImpl()
    {
        auto property = new (propertyPool.alloc()) Cursor();
        return property->shared_from_this();
    }

    PropImplPtr EntityLib::newPropImpl(
        PropImplPtr _parent, Ent::Subschema const* _schema, char const* _filename, nlohmann::json* _doc)
    {
        auto property =
            new (propertyPool.alloc()) Cursor(this, std::move(_parent), _schema, _filename, _doc);
        return property->shared_from_this();
    }

    NodeUniquePtr EntityLib::makeEntityNode() const
    {
        return makeNode(entitySchemaName);
    }

    std::filesystem::path EntityLib::getAbsolutePath(std::filesystem::path const& _path) const
    {
        if (_path.is_absolute())
        {
            return very_weakly_canonical(_path);
        }
        else
        {
            std::filesystem::path absPath = rawdataPath;
            absPath /= _path;
            return very_weakly_canonical(absPath);
        }
    }

    std::filesystem::path EntityLib::getRelativePath(std::filesystem::path const& _path) const
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

    std::map<std::filesystem::path, EntityLib::NodeFile> const& EntityLib::getNodeCache() const
    {
        return m_nodeCache;
    }

    auto EntityLib::HashPath::operator()(std::filesystem::path const& p) const
    {
        return std::filesystem::hash_value(p);
    }

    std::unordered_map<std::filesystem::path, nlohmann::json, EntityLib::HashPath> const&
    EntityLib::getJsonDatabase() const
    {
        return m_jsonDatabase;
    }

    void EntityLib::clearCache()
    {
        m_nodeCache.clear();
        m_jsonDatabase.clear();
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    void EntityLib::saveNodeAsEntity(Node const* _entity, char const* _relEntityPath) const
    {
        _entity->saveNode(_relEntityPath);
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    void EntityLib::saveNodeAsScene(Node const* _scene, char const* _scenePath) const
    {
        _scene->saveNode(_scenePath);
    }

    /// \endcond
} // namespace Ent
