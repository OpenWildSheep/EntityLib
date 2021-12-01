#include "SchemaLoader.h"
#include "Tools.h"

#pragma warning(push, 0)
#include <sstream>
#include <utility>
#include <ciso646>
#pragma warning(pop)

/// \cond PRIVATE

using namespace nlohmann;

namespace Ent
{

    SchemaLoader::SchemaLoader(std::filesystem::path _toolsdir, std::filesystem::path _schemaPath)
        : m_schemaPath(std::move(_schemaPath))
        , m_toolsdir(std::move(_toolsdir))
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
                vis.setType(DataType::entityRef);
                vis.closeSubschema();
                return;
            }
            // Use absolute path to avoid name collision
            auto absRef = (ref.front() == '#') ? ("./" + _filename + ref) : ref;
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

            if (auto titleIter = _data.find("title"); titleIter != _data.end())
            {
                vis.setRefTitle(titleIter->get_ref<json::string_t const&>());
            }

            if (auto descrIter = _data.find("description"); descrIter != _data.end())
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
            auto sharp = ref.find('#');
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
                    auto iter = m_schemaMap.find(fileName);
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
                    if (auto iter = node->find(token.c_str()); iter != node->end())
                    {
                        node = &(*iter);
                        ENTLIB_ASSERT(node->is_object());
                    }
                    else
                    {
                        ENTLIB_LOGIC_ERROR("Schema error");
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

    Subschema::Meta parseMetaForType(json const& _data, DataType _type)
    {
        const auto setBaseMetas = [&](Subschema::BaseMeta* _meta)
        {
            if (_data.is_null())
            {
                return;
            }
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

        const auto setNumberMetas = [&](Subschema::NumberMeta& _meta)
        {
            if (_data.is_null())
            {
                return;
            }
            if (_data.count("bitdepth") != 0u)
            {
                _meta.bitDepth = _data["bitdepth"].get<uint32_t>();
            }
            if (_data.count("signed") != 0u)
            {
                _meta.isSigned = _data["signed"].get<bool>();
            }
        };
        const auto setUnionMetas = [&](Subschema::UnionMeta& _meta)
        {
            if (_data.is_null())
            {
                return;
            }
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
        const auto setArrayMetas = [&](Subschema::ArrayMeta& _meta)
        {
            if (_data.is_null())
            {
                return;
            }
            auto ovPol = _data.find("overridePolicy");
            _meta.overridePolicy = ovPol != _data.end() ? ovPol->get_ref<std::string const&>() : "";
            auto ordered = _data.find("ordered");
            _meta.ordered = ordered != _data.end() ? ordered->get<bool>() : true;
            if (_data.count("keyField") != 0)
            {
                _meta.keyField = _data.at("keyField").get<std::string>();
            }
        };
        switch (_type)
        {
        case DataType::integer:
        case DataType::number:
        {
            Subschema::NumberMeta meta;
            setBaseMetas(&meta);
            setNumberMetas(meta);
            return meta;
        }
        case DataType::string:
        case DataType::object:
        case DataType::boolean:
        case DataType::entityRef:
        {
            Subschema::GenericMeta meta;
            setBaseMetas(&meta);
            return meta;
        }
        case DataType::array:
        {
            Subschema::ArrayMeta meta;
            setBaseMetas(&meta);
            setArrayMetas(meta);
            return meta;
        }
        case DataType::oneOf:
        {
            Subschema::UnionMeta meta;
            setBaseMetas(&meta);
            setUnionMetas(meta);
            return meta;
        }
        case DataType::null:
        case DataType::COUNT:
        default: ENTLIB_ASSERT_MSG(false, "Invalid DataType when parsing meta"); return {};
        }
    }

    void SchemaLoader::parseSchemaNoRef(
        std::string const& _filename, json const& _rootFile, json const& _data, Visitor& vis, int depth)
    {
        DataType currentType = DataType::null;
        const auto setType = [&](DataType _type)
        {
            currentType = _type;
            vis.setType(_type);
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
                setType(DataType::array);
            }
            else if (type == "boolean")
            {
                setType(DataType::boolean);
            }
            else if (type == "integer")
            {
                setType(DataType::integer);
            }
            else if (type == "null")
            {
                setType(DataType::null);
            }
            else if (type == "number")
            {
                setType(DataType::number);
            }
            else if (type == "object")
            {
                setType(DataType::object);
            }
            else if (type == "string")
            {
                setType(DataType::string);
            }
            else
            {
                ENTLIB_LOGIC_ERROR("Unknown type %s", type.c_str());
            }
        }
        // properties
        if (_data.count("properties") != 0u)
        {
            setType(DataType::object);
            for (auto&& [propName, prop] : _data["properties"].items())
            {
                vis.openProperty(propName.c_str());
                parseSchema(_filename, _rootFile, prop, vis, depth + 1);
                vis.closeProperty();
            }
            // Add a _comment property on all objects
            json prop = R"({"type" : "string"})"_json;
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
            case nlohmann::json::value_t::null: setType(DataType::null); break;
            case nlohmann::json::value_t::object: setType(DataType::object); break;
            case nlohmann::json::value_t::array: setType(DataType::array); break;
            case nlohmann::json::value_t::binary:
            case nlohmann::json::value_t::discarded: break;
            case nlohmann::json::value_t::string: setType(DataType::string); break;
            case nlohmann::json::value_t::boolean: setType(DataType::boolean); break;
            case nlohmann::json::value_t::number_integer:
            case nlohmann::json::value_t::number_unsigned: setType(DataType::integer); break;
            case nlohmann::json::value_t::number_float: setType(DataType::number); break;
            }
        }
        if (_data.count("const") != 0u)
        {
            json const& def = _data.at("const");
            vis.setConstValue(def);
            switch (def.type())
            {
            case nlohmann::json::value_t::null: setType(DataType::null); break;
            case nlohmann::json::value_t::object: setType(DataType::object); break;
            case nlohmann::json::value_t::array: setType(DataType::array); break;
            case nlohmann::json::value_t::binary:
            case nlohmann::json::value_t::discarded: break;
            case nlohmann::json::value_t::string: setType(DataType::string); break;
            case nlohmann::json::value_t::boolean: setType(DataType::boolean); break;
            case nlohmann::json::value_t::number_integer:
            case nlohmann::json::value_t::number_unsigned: setType(DataType::integer); break;
            case nlohmann::json::value_t::number_float: setType(DataType::number); break;
            }
        }
        if (_data.count("items") != 0u)
        {
            setType(DataType::array);
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
            setType(DataType::oneOf);
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
            else
            {
                if (currentType == DataType::null)
                {
                    // Unions doesn't have "type" field in RuntimeComponents.json
                    setType(DataType::object);
                }
                vis.setMeta(
                    parseMetaForType(_data["meta"], currentType),
                    _data["meta"].value("user", json::object()));
            }
        }
        else if (currentType != DataType::null)
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
#define ENTLIB_DEBUG_PRINTF(message, ...) printf(message, __VA_ARGS__);
#else
#define ENTLIB_DEBUG_PRINTF(message, ...)
#endif

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

            void checkWholeStack()
            {
                for (SubschemaRef* ref : stack)
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
                    stack.back()->get().type != DataType::array
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
                    stack.back()->get().type != DataType::array
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
                    stack.back()->get().type != DataType::array
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
            void setType(DataType type) override
            {
                ENTLIB_DEBUG_PRINTF("%ssetType %d\n", getTab(), (int)type);
                CHECK_WHOLE_STACK;
                stack.back()->get().type = type;
            }
            void setOneOf(size_t size) override
            {
                ENTLIB_DEBUG_PRINTF("%ssetOneOf %zu\n", getTab(), size);
                CHECK_WHOLE_STACK;
                stack.back()->get().type = DataType::oneOf;
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
                char const* typeName = getRefTypeName(link);
                // Force to create the definition (do nothing if already exist)
                ENTLIB_ASSERT_MSG(typeName != nullptr, "Can't get type name in '%s'!!", link);
                auto& subschema = globalSchema->allDefinitions[typeName];
                ENTLIB_ASSERT(strlen(typeName) != 0);
                subschema.name = typeName;
                subschema.rootSchema = globalSchema;
                auto& ref = stack.back()->subSchemaOrRef;
                ENTLIB_ASSERT(std::holds_alternative<Null>(ref));
                ref = SubschemaRef::Ref{globalSchema, typeName};
            }

            void finalizeSubschema(Subschema& lastSchema)
            {
                if (not lastSchema.unionTypeMap.empty())
                {
                    return;
                }
                // Fill the Subschema::unionTypeMap
                if (lastSchema.type == DataType::oneOf)
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
                            auto& typeSchema = info.wrapperSchema->properties.at(un->typeField).get();
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
                    auto& lastSchema = stack.back()->get();
                    if (lastSchema.type == DataType::array)
                    {
                        auto& lastMeta = std::get<Subschema::ArrayMeta>(lastSchema.meta);
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
                    finalizeSubschema(lastSchema);
                }
                ENTLIB_DEBUG_PRINTF("%scloseSubschema\n", getTab());
            }
            void setMeta(Subschema::Meta meta, nlohmann::json user) override
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
            if (vis.stack.back()->get().oneOf.has_value())
            {
                ENTLIB_ASSERT(
                    vis.stack.back()->get().unionTypeMap.size()
                    == vis.stack.back()->get().oneOf->size());
            }

            auto& subschema = globalSchema->allDefinitions[name];
            subschema.name = name;
            subschema.rootSchema = globalSchema;
            if (vis.stack.back()->get().oneOf.has_value())
                ENTLIB_ASSERT(
                    vis.stack.back()->get().unionTypeMap.size()
                    == vis.stack.back()->get().oneOf->size());
            subschema = std::move(vis.stack.back()->get());
            if (subschema.oneOf.has_value())
                ENTLIB_ASSERT(subschema.unionTypeMap.size() == subschema.oneOf->size());

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
