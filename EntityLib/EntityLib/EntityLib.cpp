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
    Ent::Node makeDefaultColorField(EntityLib const& _entlib)
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

        auto&& actorstateList = schema.schema.allDefinitions
                                    .at("./RuntimeComponents.json#/definitions/"
                                        "ResponsiblePointer<ActorState>")
                                    .oneOf;

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
        if (_super != nullptr)
        {
            object.hasASuper = true;
        }
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
                                if (item->GetRawValue().get<Object>().hasASuper)
                                {
                                    json tmpNode;
                                    auto key = arr.getChildKey(item);
                                    mapbox::util::apply_visitor(
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
    auto superEntityOfThisEntity = std::make_unique<Ent::Entity>(_entlib, "Prefab");
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
                subSceneComp->embedded = Ent::Scene::loadScene(
                    _entlib,
                    data["Embedded"],
                    (superComp != nullptr ? superComp->embedded.get() : nullptr));
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

std::unique_ptr<Ent::Scene>
Ent::Scene::loadScene(Ent::EntityLib const& _entLib, json const& _entities, Ent::Scene const* _super)
{
    auto scene = std::make_unique<Ent::Scene>(&_entLib);

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
            bool const removed = instEntNode != nullptr and instEntNode->count("__removed__") != 0;
            std::unique_ptr<Ent::Entity> ent = (instEntNode == nullptr) ?
                                                   superEnt->makeInstanceOf() :
                                                   ::loadEntity(_entLib, *instEntNode, superEnt);
            auto entName = ent->getName();

            ent->setCanBeRenamed(false);
            scene->objects.emplace(entName, std::move(ent), OverrideValueLocation::Prefab);
            if (removed)
            {
                scene->removeEntity(entName);
            }
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
        if (entNode.count("__removed__") != 0) // Strange to remove a new entity. Let's ignore it.
        {
            continue;
        }
        std::unique_ptr<Ent::Entity> ent = ::loadEntity(_entLib, entNode, nullptr);
        ENTLIB_ASSERT(ent != nullptr);
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
        return Scene::loadScene(_entLib, _document.at("Objects"), _super);
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
    if (getInstanceOf() == nullptr)
    {
        throw ContextException("This entity has no prefab");
    }
    std::string prefabPath = getInstanceOf();
    auto prefab = entlib->loadEntity(prefabPath);
    auto prefabName = prefab->name;
    auto instanceName = name;

    // When the value is overridden is the source, we want to make it overridden in the dest => CopyOverride
    applyAllValuesButPrefab(*prefab, CopyMode::CopyOverride);
    // Asked by the maxscript team because they don't want to change the name this way
    prefab->name = prefabName;
    // Need to save the prefab before "resetInstanceOf"
    // because "resetInstanceOf" will use the new prefab
    entlib->saveEntity(*prefab, prefabPath.c_str());
    resetInstanceOf(prefabPath.c_str()); // Reset 'this' to a vanilla instance of prefab
    name = instanceName;
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
    size_t cmpIndex = 0;
    for (auto const& type_comp : getComponents())
    {
        auto const& type = std::get<0>(type_comp);
        auto const& comp = std::get<1>(type_comp);

        Ent::Component detachedComp{comp.rawData, false, type, comp.root.detach(), 1, cmpIndex};

        detComponents.emplace(type, std::move(detachedComp));
        ++cmpIndex;
    }
    std::unique_ptr<SubSceneComponent> detSubSceneComponent;
    if (SubSceneComponent const* subscene = getSubSceneComponent())
    {
        detSubSceneComponent = std::make_unique<SubSceneComponent>(entlib);
        detSubSceneComponent->embedded = std::make_unique<Ent::Scene>(entlib);
        for (auto const& subEntity : subscene->embedded->getObjects())
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
    std::unique_ptr<Ent::Entity> inst = std::make_unique<Ent::Entity>(*this, nullptr);
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
        return very_weakly_canonical(_path);
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

    std::vector<EntityMap::value_type const*> orderedEntities;
    orderedEntities.reserve(objects.map.size());
    for (auto& name_ent : objects.map)
    {
        orderedEntities.push_back(&name_ent);
    }
    std::stable_sort(
        begin(orderedEntities),
        end(orderedEntities),
        [](EntityMap::value_type const* a, EntityMap::value_type const* b) {
            return a->second.index < b->second.index; // Try to keep ordering
        });
    for (auto const* name_ent : orderedEntities)
    {
        if (name_ent->second.isPresent.get())
        {
            if (name_ent->second.hasOverride())
            {
                jsnObjects.emplace_back(name_ent->second.value->saveEntity());
            }
        }
        else if (name_ent->second.isPresent.getPrefab())
        {
            // isPresent is false but it was true in the prefab
            json removedObj;
            removedObj["Name"] = name_ent->first;
            removedObj["__removed__"] = true;
            jsnObjects.emplace_back(std::move(removedObj));
        }
    }

    return document;
}

void Ent::EntityLib::saveScene(Scene const& _scene, std::filesystem::path const& _scenePath) const
{
    // scene entity is named after scene base file name
    Ent::Entity sceneEntity{*this, _scenePath.stem().string().c_str()};

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

/// \endcond
