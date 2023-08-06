#include "SchemaLoader.h"
#include "Tools.h"

#include <sstream>
#include <utility>
#include <ciso646>

/// \cond PRIVATE

using namespace nlohmann;

namespace Ent
{

    SchemaLoader::SchemaLoader(std::filesystem::path _schemaPath)
        : m_schemaPath(std::move(_schemaPath))
    {
    }

    static char const* entityRefSchemaName = "#/definitions/EntityRef";

    void SchemaLoader::parseSchema(
        std::string const& _filename, json const& _fileRoot, json const& _data, Visitor& vis, int depth)
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
                vis.setJsonType(JsonType::entityRef);
                vis.closeSubschema();
                return;
            }
            // Use absolute path to avoid name collision
            auto const absRef = (ref.front() == '#') ? ("./" + _filename + ref) : ref;
            vis.openRef(absRef.c_str());

            // default values beside a "$ref" are "special".
            // They are not attached to the pointed class, but to the $ref itself.
            // So let's call setRefDefaultValue
            // + setRefDefaultValue has to be called even if the referenced type has already been parsed
            if (_data.count("default") != 0u)
            {
                json const& def = _data.at("default");
                vis.setRefDefaultValue(def);
            }

            if (auto const titleIter = _data.find("title"); titleIter != _data.end())
            {
                vis.setRefTitle(titleIter->get_ref<json::string_t const&>());
            }

            if (auto const descrIter = _data.find("description"); descrIter != _data.end())
            {
                vis.setRefDescription(descrIter->get_ref<json::string_t const&>());
            }

            if (parsedRef.count(absRef) != 0) // Was already parsed
            {
                vis.closeRef();
                return;
            }
            parsedRef.insert(absRef);
            // ref look like this : "./EditionComponents.json#/definitions/HeightObj"
            if (ref.find("./") == 0)
            {
                ref = ref.substr(strlen("./"));
            }
            auto const sharp = ref.find('#');
            auto fileName = ref.substr(0, sharp);
            try
            {
                std::filesystem::path objectPath = ref.substr(sharp + 2);

                json const* refRoot{};
                if (fileName.empty())
                {
                    refRoot = &_fileRoot;
                    fileName = _filename;
                }
                else
                {
                    auto const iter = m_schemaMap.find(fileName);
                    if (iter == m_schemaMap.end())
                    {
                        m_schemaMap[fileName] = loadJsonFile(m_schemaPath, fileName);
                    }
                    refRoot = &m_schemaMap[fileName];
                }
                json const* node = refRoot;
                objectPath.make_preferred();
                for (auto const& token :
                     splitString(objectPath.string(), std::filesystem::path::preferred_separator))
                {
                    if (auto iter = node->find(token); iter != node->end())
                    {
                        node = &(*iter);
                    }
                    else
                    {
                        fprintf(
                            stderr,
                            "ERROR : Definition for \"%s\" is referenced but not defined\n",
                            token.c_str());
                    }
                }
                parseSchemaNoRef(fileName, *refRoot, *node, vis, depth);
            }
            catch (ContextException& ex)
            {
                ex.addContextMessage(
                    "Loading '%s' in file : %s", ref.c_str(), formatPath({}, fileName));
                throw;
            }
            catch (...)
            {
                throw WrapperException(
                    std::current_exception(),
                    "Loading '%s' in file : %s",
                    ref.c_str(),
                    formatPath({}, fileName));
            }

            vis.closeRef();
        }
        else
        {
            vis.openSubschema();
            parseSchemaNoRef(_filename, _fileRoot, _data, vis, depth);
            vis.closeSubschema();
        }
    }

    Subschema::Meta parseMetaForType(json const& _data, JsonType _type)
    {
        auto const setBaseMetas = [&](Subschema::BaseMeta* _meta)
        {
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

        auto const setNumberMetas = [&](Subschema::NumberMeta& _meta)
        {
            if (_data.count("bitdepth") != 0u)
            {
                _meta.bitDepth = _data["bitdepth"].get<uint32_t>();
            }
            if (_data.count("signed") != 0u)
            {
                _meta.isSigned = _data["signed"].get<bool>();
            }
        };
        auto const setUnionMetas = [&](Subschema::UnionMeta& _meta)
        {
            if (_data.count("unionDataField") != 0u)
            {
                _meta.dataField = _data["unionDataField"].get<std::string>();
            }
            if (_data.count("unionTypeField") != 0u)
            {
                _meta.typeField = _data["unionTypeField"].get<std::string>();
            }
            if (_data.count("unionIndexField") != 0u)
            {
                _meta.indexField = _data["unionIndexField"].get<std::string>();
            }
        };
        auto const setArrayMetas = [&](Subschema::ArrayMeta& _meta)
        {
            _meta.overridePolicy = _data.value("overridePolicy", "");
            _meta.ordered = _data.value("ordered", true);
            if (_data.count("keyField") != 0)
            {
                _meta.keyField = _data.at("keyField").get<std::string>();
            }
        };
        switch (_type)
        {
        case JsonType::integer:
        case JsonType::number:
        {
            Subschema::NumberMeta meta;
            setBaseMetas(&meta);
            setNumberMetas(meta);
            return meta;
        }
        case JsonType::string:
        case JsonType::object:
        case JsonType::boolean:
        case JsonType::entityRef:
        {
            Subschema::GenericMeta meta;
            setBaseMetas(&meta);
            return meta;
        }
        case JsonType::array:
        {
            Subschema::ArrayMeta meta;
            setBaseMetas(&meta);
            setArrayMetas(meta);
            return meta;
        }
        case JsonType::oneOf:
        {
            Subschema::UnionMeta meta;
            setBaseMetas(&meta);
            setUnionMetas(meta);
            return meta;
        }
        case JsonType::null:
        case JsonType::COUNT:
        default: ENTLIB_ASSERT_MSG(false, "Invalid JsonType when parsing meta"); return {};
        }
    }

    void SchemaLoader::parseSchemaNoRef(
        std::string const& _filename, json const& _rootFile, json const& _data, Visitor& vis, int depth)
    {
        auto currentType = JsonType::null;
        auto const setJsonType = [&](JsonType _type)
        {
            currentType = _type;
            vis.setJsonType(_type);
        };
        // type
        if (_data.count("type") != 0u)
        {
            auto const& type = _data["type"].get<std::string>();
            if (type == "anyOf")
            {
                ENTLIB_ASSERT("Unexpected JSON schema type : Any");
            }
            else if (type == "array")
            {
                setJsonType(JsonType::array);
            }
            else if (type == "boolean")
            {
                setJsonType(JsonType::boolean);
            }
            else if (type == "integer")
            {
                setJsonType(JsonType::integer);
            }
            else if (type == "null")
            {
                setJsonType(JsonType::null);
            }
            else if (type == "number")
            {
                setJsonType(JsonType::number);
            }
            else if (type == "object")
            {
                setJsonType(JsonType::object);
            }
            else if (type == "string")
            {
                setJsonType(JsonType::string);
            }
            else
            {
                ENTLIB_LOGIC_ERROR("Unknown type %s", type.c_str());
            }
        }
        // properties
        if (_data.count("properties") != 0u)
        {
            setJsonType(JsonType::object);
            for (auto&& name_prop : _data["properties"].items())
            {
                auto const& propName = name_prop.key();
                auto const& prop = name_prop.value();
                vis.openProperty(propName.c_str());
                parseSchema(_filename, _rootFile, prop, vis, depth + 1);
                vis.closeProperty();
            }
            // Add a _comment property on all objects
            auto const prop = R"({"type" : "string"})"_json;
            vis.openProperty("_comment");
            parseSchema(_filename, _rootFile, prop, vis, depth + 1);
            vis.closeProperty();
        }
        // default
        if (_data.count("default") != 0u)
        {
            json const& def = _data.at("default");
            vis.setDefaultValue(def);
            switch (def.type())
            {
            case json::value_t::null: setJsonType(JsonType::null); break;
            case json::value_t::object: setJsonType(JsonType::object); break;
            case json::value_t::array: setJsonType(JsonType::array); break;
            case json::value_t::binary:
            case json::value_t::discarded: break;
            case json::value_t::string: setJsonType(JsonType::string); break;
            case json::value_t::boolean: setJsonType(JsonType::boolean); break;
            case json::value_t::number_integer:
            case json::value_t::number_unsigned: setJsonType(JsonType::integer); break;
            case json::value_t::number_float: setJsonType(JsonType::number); break;
            }
        }
        if (auto const minIterator = _data.find("minimum"); minIterator != _data.end())
        {
            json const& def = minIterator.value();
            vis.setMinimumValue(def);
        }
        if (auto const maxIterator = _data.find("maximum"); maxIterator != _data.end())
        {
            json const& def = maxIterator.value();
            vis.setMaximumValue(def);
        }
        if (_data.count("const") != 0u)
        {
            json const& def = _data.at("const");
            vis.setConstValue(def);
            switch (def.type())
            {
            case json::value_t::null: setJsonType(JsonType::null); break;
            case json::value_t::object: setJsonType(JsonType::object); break;
            case json::value_t::array: setJsonType(JsonType::array); break;
            case json::value_t::binary:
            case json::value_t::discarded: break;
            case json::value_t::string: setJsonType(JsonType::string); break;
            case json::value_t::boolean: setJsonType(JsonType::boolean); break;
            case json::value_t::number_integer:
            case json::value_t::number_unsigned: setJsonType(JsonType::integer); break;
            case json::value_t::number_float: setJsonType(JsonType::number); break;
            }
        }
        if (_data.count("items") != 0u)
        {
            setJsonType(JsonType::array);
            auto const& items = _data["items"];
            // items linear
            if (items.type() == json::value_t::array)
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
            else if (items.type() == json::value_t::object)
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
            setJsonType(JsonType::oneOf);
            auto const& items = _data["oneOf"];
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
        if (_data.count("title") != 0u)
        {
            vis.setTitle(_data["title"].get_ptr<json::string_t const*>()->c_str());
        }
        if (_data.count("description") != 0u)
        {
            vis.setDescription(_data["description"].get_ptr<json::string_t const*>()->c_str());
        }
        if (_data.count("meta") != 0u)
        {
            if (!_data["meta"].is_object())
            {
                ENTLIB_LOGIC_ERROR(
                    "Unexpected json items type for \"meta\" : %s", _data["meta"].type_name());
            }
            if (currentType == JsonType::null)
            {
                // Unions doesn't have "type" field in RuntimeComponents.json
                setJsonType(JsonType::object);
            }
            vis.setMeta(
                parseMetaForType(_data["meta"], currentType),
                _data["meta"].value("user", json::object()));
        }
        else if (currentType != JsonType::null)
        {
            // Set Meta to default values for the currentType
            vis.setMeta(parseMetaForType(json::object(), currentType), json::object());
        }
        if (_data.count("name") != 0u)
        {
            // manually specified type name (typically used for enums properties that are inlined)
            vis.setName(_data["name"].get<std::string>());
        }
    }

    // TODO Loïc : (Low prio) It could be good to use a real logger system. (like spdlog for example)
#ifdef ENTLIB_DEBUG_READSCHEMA
#define ENTLIB_DEBUG_PRINTF(...) printf(__VA_ARGS__);
#else
#define ENTLIB_DEBUG_PRINTF(...)
#endif

    DataKind computeDataKind(Subschema const& _subschema)
    {
        switch (_subschema.jsonType)
        {
        case JsonType::string: return DataKind::string;
        case JsonType::number: return DataKind::number;
        case JsonType::integer: return DataKind::integer;
        case JsonType::object: return DataKind::object;
        case JsonType::boolean: return DataKind::boolean;
        case JsonType::entityRef: return DataKind::entityRef;
        case JsonType::oneOf: return DataKind::union_;
        case JsonType::array:
            switch (hash(std::get<Subschema::ArrayMeta>(_subschema.meta).overridePolicy))
            {
            case "map"_hash: return DataKind::map;
            case "set"_hash:
                switch (_subschema.singularItems->get().jsonType)
                {
                case JsonType::integer: [[fallthrough]];
                case JsonType::entityRef: [[fallthrough]];
                case JsonType::string: return DataKind::primitiveSet;
                case JsonType::oneOf: return DataKind::unionSet;
                case JsonType::object: return DataKind::objectSet;
                default: return DataKind::array;
                }
            case ""_hash: return DataKind::array;
            }
            ENTLIB_LOGIC_ERROR("Unexpected overridePolicy !");
        case JsonType::COUNT: break;
        case JsonType::null: break;
        }
        ENTLIB_LOGIC_ERROR("Unexpected JsonType !");
    }

    void SchemaLoader::readSchema(
        Schema* globalSchema, std::string const& _filename, json const& _fileRoot, json const& _data)
    {
        std::vector<SubschemaRef*> stack;
        stack.reserve(1000);

        struct FillSchema : Visitor
        {
            Schema* globalSchema;
            std::vector<SubschemaRef*>& stack;
            std::string tab;

            FillSchema(Schema* _globalSchema, std::vector<SubschemaRef*>& _stack)
                : globalSchema(_globalSchema)
                , stack(_stack)
            {
            }

            char const* getTab()
            {
                tab.assign(stack.size() * 4, ' ');
                return tab.c_str();
            };

            void checkWholeStack() const
            {
                for (SubschemaRef const* ref : stack)
                {
                    ENTLIB_ASSERT(ref->deleteCheck.state_ == DeleteCheck::State::VALID);
                }
            };

#define CHECK_WHOLE_STACK // checkWholeStack() // Call checkWholeStack to debug readSchema

            void addEnumValue(char const* val) override
            {
                stack.back()->get().enumValues.emplace_back(val);
            }
            void closeLinearItem() override
            {
                CHECK_WHOLE_STACK;
                ENTLIB_ASSERT(
                    stack.back()->get().jsonType != JsonType::array
                    or stack.back()->get().singularItems != nullptr
                    or stack.back()->get().linearItems.has_value());
                stack.pop_back();
                CHECK_WHOLE_STACK;
                ENTLIB_DEBUG_PRINTF("%sloseLinearItem\n", getTab());
            }
            void closeProperty() override
            {
                CHECK_WHOLE_STACK;
                ENTLIB_ASSERT(
                    stack.back()->get().jsonType != JsonType::array
                    or stack.back()->get().singularItems != nullptr
                    or stack.back()->get().linearItems.has_value());
                stack.pop_back();
                CHECK_WHOLE_STACK;
                ENTLIB_DEBUG_PRINTF("%scloseProperty\n", getTab());
            }
            void closeSingularItem() override
            {
                CHECK_WHOLE_STACK;
                ENTLIB_ASSERT(
                    stack.back()->get().jsonType != JsonType::array
                    or stack.back()->get().singularItems != nullptr
                    or stack.back()->get().linearItems.has_value());
                stack.pop_back();
                CHECK_WHOLE_STACK;
                ENTLIB_DEBUG_PRINTF("%scloseSingularItem\n", getTab());
            }
            void openLinearItem(size_t index) override
            {
                CHECK_WHOLE_STACK;
                ENTLIB_DEBUG_PRINTF("%sopenLinearItem %zu\n", getTab(), index);
                SubschemaRef& lin = stack.back()->get().linearItems->at(index);
                stack.push_back(&lin);
                CHECK_WHOLE_STACK;
            }
            void openProperty(char const* propName) override
            {
                CHECK_WHOLE_STACK;
                ENTLIB_DEBUG_PRINTF("%sopenProperty %s\n", getTab(), propName);
                SubschemaRef& subSchema = stack.back()->get().properties[propName];
                stack.push_back(&subSchema);
                CHECK_WHOLE_STACK;
            }
            void openSingularItem() override
            {
                CHECK_WHOLE_STACK;
                ENTLIB_DEBUG_PRINTF("%sopenSingularItem\n", getTab());
                stack.back()->get().singularItems = std::make_unique<SubschemaRef>();
                CHECK_WHOLE_STACK;
                stack.push_back(&(*stack.back()->get().singularItems));
                CHECK_WHOLE_STACK;
            }
            void setConstValue(Subschema::DefaultValue val) override
            {
                CHECK_WHOLE_STACK;
                stack.back()->get().constValue = val;
            }
            void setDefaultValue(Subschema::DefaultValue val) override
            {
                CHECK_WHOLE_STACK;
                stack.back()->get().defaultValue = std::move(val);
            }
            void setMinimumValue(Subschema::DefaultValue val) override
            {
                CHECK_WHOLE_STACK;
                stack.back()->get().minimum = std::move(val);
            }
            void setMaximumValue(Subschema::DefaultValue val) override
            {
                CHECK_WHOLE_STACK;
                stack.back()->get().maximum = std::move(val);
            }
            void setRefDefaultValue(Subschema::DefaultValue val) override
            {
                CHECK_WHOLE_STACK;
                std::get<SubschemaRef::Ref>(stack.back()->subSchemaOrRef).defaultValue =
                    std::move(val);
            }
            void setRefTitle(std::string val) override
            {
                CHECK_WHOLE_STACK;
                std::get<SubschemaRef::Ref>(stack.back()->subSchemaOrRef).title = std::move(val);
            }
            void setRefDescription(std::string val) override
            {
                CHECK_WHOLE_STACK;
                std::get<SubschemaRef::Ref>(stack.back()->subSchemaOrRef).description =
                    std::move(val);
            }
            void setLinearItem(size_t size) override
            {
                CHECK_WHOLE_STACK;
                stack.back()->get().linearItems = std::vector<SubschemaRef>();
                stack.back()->get().linearItems->resize(size);
            }
            void setMaxItems(size_t val) override
            {
                CHECK_WHOLE_STACK;
                stack.back()->get().maxItems = val;
            }
            void setMinItems(size_t val) override
            {
                CHECK_WHOLE_STACK;
                stack.back()->get().minItems = val;
            }
            void setJsonType(JsonType type) override
            {
                ENTLIB_DEBUG_PRINTF("%ssetType %d\n", getTab(), (int)type);
                CHECK_WHOLE_STACK;
                stack.back()->get().jsonType = type;
            }
            void setOneOf(size_t size) override
            {
                ENTLIB_DEBUG_PRINTF("%ssetOneOf %zu\n", getTab(), size);
                CHECK_WHOLE_STACK;
                stack.back()->get().jsonType = JsonType::oneOf;
                stack.back()->get().oneOf = std::vector<SubschemaRef>();
                stack.back()->get().oneOf->resize(size);
            }
            void openOneOfItem(size_t index) override
            {
                ENTLIB_DEBUG_PRINTF("%sopenOneOfItem %zu\n", getTab(), index);
                CHECK_WHOLE_STACK;
                SubschemaRef& lin = stack.back()->get().oneOf->at(index);
                stack.push_back(&lin);
                CHECK_WHOLE_STACK;
            }
            void closeOneOfItem() override
            {
                CHECK_WHOLE_STACK;
                stack.pop_back();
                CHECK_WHOLE_STACK;
                ENTLIB_DEBUG_PRINTF("%scloseOneOfItem\n", getTab());
            }

            void openRef(char const* link) override
            {
                CHECK_WHOLE_STACK;
                ENTLIB_DEBUG_PRINTF("%sopenRef %s\n", getTab(), link);
                auto const typeName = std::string(getRefTypeName(link));
                // Force to create the definition (do nothing if already exist)
                auto& subschema = globalSchema->allDefinitions[typeName];
                ENTLIB_ASSERT(not typeName.empty());
                subschema.name = typeName;
                subschema.rootSchema = globalSchema;
                auto& ref = stack.back()->subSchemaOrRef;
                ENTLIB_ASSERT(std::holds_alternative<Null>(ref));
                ref = SubschemaRef::Ref{globalSchema, typeName};
            }

            static void finalizeSubschema(Subschema& lastSchema)
            {
                if (not lastSchema.unionTypeMap.empty())
                {
                    return;
                }
                // Fill the Subschema::unionTypeMap
                if (lastSchema.jsonType == JsonType::oneOf)
                {
                    if (auto const* un = std::get_if<Subschema::UnionMeta>(&lastSchema.meta))
                    {
                        size_t index = 0;
                        for (SubschemaRef const& wrapperSchema : *lastSchema.oneOf)
                        {
                            Subschema::UnionSubTypeInfo info{};
                            info.wrapperSchema = &wrapperSchema.get();
                            info.index = index;
                            info.dataSchema = &info.wrapperSchema->properties.at(un->dataField).get();
                            auto const& typeSchema =
                                info.wrapperSchema->properties.at(un->typeField).get();
                            auto const& typeName =
                                typeSchema.constValue->get_ref<std::string const&>();
                            lastSchema.unionTypeMap.emplace(typeName.c_str(), info);
                            ++index;
                        }
                        ENTLIB_ASSERT(lastSchema.unionTypeMap.size() == lastSchema.oneOf->size());
                    }
                }
            }

            void closeRef() override
            {
                auto& lastSchema = stack.back()->get();
                finalizeSubschema(lastSchema);

                CHECK_WHOLE_STACK;
                ENTLIB_DEBUG_PRINTF("%scloseRef\n", getTab());
            }
            void openSubschema() override
            {
                ENTLIB_DEBUG_PRINTF("%sopenSubschema\n", getTab());
                CHECK_WHOLE_STACK;
                ENTLIB_ASSERT(std::holds_alternative<Null>(stack.back()->subSchemaOrRef));
                if (std::holds_alternative<Null>(stack.back()->subSchemaOrRef))
                {
                    Subschema subschema{};
                    subschema.rootSchema = globalSchema;
                    stack.back()->subSchemaOrRef = std::move(subschema);
                }
                ENTLIB_DEBUG_PRINTF("%sopenSubschema2\n", getTab());
                CHECK_WHOLE_STACK;
            }
            void closeSubschema() override
            {
                if (stack.size() > 1)
                {
                    auto const& lastSchema = stack.back()->get();
                    if (lastSchema.jsonType == JsonType::array)
                    {
                        auto const& lastMeta = std::get<Subschema::ArrayMeta>(lastSchema.meta);
                        if (lastMeta.overridePolicy == "map")
                        {
                            if (lastSchema.singularItems == nullptr)
                            {
                                throw ContextException(
                                    "Invalid schema. 'map' override polocy is only valid with a "
                                    "singularItem array",
                                    lastMeta.keyField->c_str());
                            }
                            std::get<Subschema::ArrayMeta>(lastSchema.singularItems->get().meta).isMapItem =
                                true;
                        }
                        if (lastMeta.keyField.has_value())
                        {
                            if (lastSchema.singularItems == nullptr)
                            {
                                throw ContextException(
                                    "Invalid schema. keyField ('%s') meta data is only valid with "
                                    "a "
                                    "singularItem array",
                                    lastMeta.keyField->c_str());
                            }
                            auto&& props = lastSchema.singularItems->get().properties;
                            if (props.count(*lastMeta.keyField) != 0)
                            {
                                props.at(*lastMeta.keyField)->isKeyField = true;
                            }
                            // The key can be absent when an object contain itself (like Entities).
                            // Sometimes the object can be incomplete, but will be completed later.
                        }
                    }
                }
                {
                    auto& lastSchema = stack.back()->get();
                    lastSchema.setDataKind(computeDataKind(lastSchema));
                    finalizeSubschema(lastSchema);
                }
                ENTLIB_DEBUG_PRINTF("%scloseSubschema\n", getTab());
            }
            void setMeta(Subschema::Meta meta, json user) override
            {
                CHECK_WHOLE_STACK;
                auto&& subSchema = stack.back()->get();
                subSchema.meta = std::move(meta);
                subSchema.userMeta = std::move(user);
            }
            void setName(std::string name) override
            {
                ENTLIB_DEBUG_PRINTF("%ssetName %s\n", getTab(), name.c_str());
                CHECK_WHOLE_STACK;
                auto&& subSchema = stack.back()->get();
                ENTLIB_ASSERT_MSG(
                    subSchema.name.empty(),
                    "Subschema is already named '%s' (new name: '%s')",
                    subSchema.name.c_str(),
                    name.c_str());
                subSchema.name = std::move(name);
            }
            void setTitle(char const* _title) override
            {
                auto&& subSchema = stack.back()->get();
                subSchema.title = _title;
            }
            void setDescription(char const* _description) override
            {
                auto&& subSchema = stack.back()->get();
                subSchema.description = _description;
            }
        };
        FillSchema vis{globalSchema, stack};

        // Parse all definitions
        for (auto& [name, def] : _data["definitions"].items())
        {
            SubschemaRef ref;
            vis.stack.push_back(&ref);
            auto absRef = "./" + _filename + "#/definitions/" + name;
            parsedRef.insert(absRef);
            vis.openSubschema();
            parseSchemaNoRef(_filename, _fileRoot, def, vis, 0);
            vis.closeSubschema();

            auto& subschema = globalSchema->allDefinitions[name];
            subschema.name = name;
            subschema.rootSchema = globalSchema;
            subschema = std::move(vis.stack.back()->get());

            vis.stack.pop_back();
        }

        // Add names
        for (auto&& [name, def] : globalSchema->allDefinitions)
        {
            def.name = name;
        }
    }

    /// \endcond
} // namespace Ent
