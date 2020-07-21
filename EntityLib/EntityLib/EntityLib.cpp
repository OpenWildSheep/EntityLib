#include "include/EntityLib.h"

#pragma warning(push, 0)
#include <iostream>
#include <fstream>

#include "external/json.hpp"
#ifdef ENTLIB_LOADSCHEMA
#include <valijson/adapters/nlohmann_json_adapter.hpp>
#include <valijson/utils/nlohmann_json_utils.hpp>
#include <valijson/schema.hpp>
#include <valijson/schema_parser.hpp>
#endif
#pragma warning(pop)

using namespace nlohmann;

char schemaPath[2048] = {};

static json loadJsonFile(std::filesystem::path const& path)
{
    std::ifstream file(path);
    if (not file.is_open())
    {
        throw std::runtime_error("Can't open file for read: " + path.u8string());
    }
    json doc;
    doc << file;
    return doc;
};

static Ent::Node loadNode(Ent::Subschema const& nodeSchema, json const& data, Ent::Node const* super);

#ifdef ENTLIB_LOADSCHEMA

json const* fetchDocument(const std::string& uri)
{
    std::string const cleanPath =
        schemaPath + ("/" + (uri.substr(0, 7) == "file://" ? uri.substr(7, uri.size()) : uri));

    json* fetchedRoot = new json{};
    if (!valijson::utils::loadDocument(cleanPath, *fetchedRoot))
    {
        fprintf(stderr, "Can't load file %s\n", cleanPath.c_str());
        return nullptr;
    }

    return fetchedRoot;
}

void freeDocument(json const* adapter)
{
    delete adapter;
}

json const& getFrozenValue(valijson::adapters::FrozenValue const* val)
{
    class NlohmannJsonFrozenValue : public valijson::adapters::FrozenValue
    {
    public:
        nlohmann::json m_value;
    };

    auto val2 = (NlohmannJsonFrozenValue const*)val;
    return val2->m_value;
}

/// Interface to allow usage of the visitor pattern with Constraints
class FillDefinition : public valijson::constraints::ConstraintVisitor
{
public:
    int subSceneLevel; // Are we in the special case of the Embeded in SubScene ?
    Ent::Subschema schema;

    FillDefinition(int _subSceneLevel)
        : subSceneLevel(_subSceneLevel)
    {
    }

    bool visit(const AllOfConstraint&) final
    {
        assert(false && "Unexpected constraint AllOfConstraint");
        return true;
    }
    bool visit(const AnyOfConstraint&) final
    {
        assert(false && "Unexpected constraint AnyOfConstraint");
        return true;
    }
    bool visit(const ConditionalConstraint&) final
    {
        assert(false && "Unexpected constraint ConditionalConstraint");
        return true;
    }
    bool visit(const ConstConstraint&) final
    {
        assert(false && "Unexpected constraint ConstConstraint");
        return true;
    }
    bool visit(const DefaultConstraint& c) final
    {
        schema.defaultValue = getFrozenValue(c.getValue());
        return true;
    }
    bool visit(const ContainsConstraint&) final
    {
        assert(false && "Unexpected constraint ContainsConstraint");
        return true;
    }
    bool visit(const DependenciesConstraint&) final
    {
        assert(false && "Unexpected constraint DependenciesConstraint");
        return true;
    }
    bool visit(const EnumConstraint& c) final
    {
        c.applyToValues([this](valijson::adapters::FrozenValue const& v) {
            schema.enumValues.push_back(getFrozenValue(&v));
            return true;
        });
        return true;
    }
    bool visit(const LinearItemsConstraint& c) final
    {
        schema.linearItems = std::vector<Ent::Subschema>();
        c.applyToItemSubschemas([this](unsigned int index, valijson::Subschema const* sc) {
            FillDefinition fillDef(0);
            auto visitor = valijson::Schema::ApplyFunction(
                [&fillDef](valijson::constraints::Constraint const& constraint) {
                    return constraint.accept(fillDef);
                });
            bool ok = sc->apply(visitor);
            if (schema.linearItems->size() <= index)
                schema.linearItems->resize(index + 1);
            (*schema.linearItems)[index] = std::move(fillDef.schema);
            return ok;
        });
        return true;
    }
    bool visit(const MaximumConstraint&) final
    {
        assert(false && "Unexpected constraint MaximumConstraint");
        return true;
    }
    bool visit(const MaxItemsConstraint& c) final
    {
        schema.maxItems = c.getMaxItems();
        return true;
    }
    bool visit(const MaxLengthConstraint&) final
    {
        assert(false && "Unexpected constraint MaxLengthConstraint");
        return true;
    }
    bool visit(const MaxPropertiesConstraint&) final
    {
        assert(false && "Unexpected constraint MaxPropertiesConstraint");
        return true;
    }
    bool visit(const MinimumConstraint&) final
    {
        assert(false && "Unexpected constraint MinimumConstraint");
        return true;
    }
    bool visit(const MinItemsConstraint& c) final
    {
        schema.minItems = c.getMinItems();
        return true;
    }
    bool visit(const MinLengthConstraint&) final
    {
        assert(false && "Unexpected constraint MinLengthConstraint");
        return true;
    }
    bool visit(const MinPropertiesConstraint&) final
    {
        assert(false && "Unexpected constraint MinPropertiesConstraint");
        return true;
    }
    bool visit(const MultipleOfDoubleConstraint&) final
    {
        assert(false && "Unexpected constraint MultipleOfDoubleConstraint");
        return true;
    }
    bool visit(const MultipleOfIntConstraint&) final
    {
        assert(false && "Unexpected constraint MultipleOfIntConstraint");
        return true;
    }
    bool visit(const NotConstraint&) final
    {
        assert(false && "Unexpected constraint NotConstraint");
        return true;
    }
    bool visit(const OneOfConstraint&) final
    {
        assert(false && "Unexpected constraint OneOfConstraint");
        return true;
    }
    bool visit(const PatternConstraint&) final
    {
        assert(false && "Unexpected constraint PatternConstraint");
        return true;
    }
    bool visit(const PolyConstraint&) final
    {
        assert(false && "Unexpected constraint PolyConstraint");
        return true;
    }
    bool visit(const PropertiesConstraint& c) final
    {
        c.applyToProperties([this](auto const& propName, valijson::Subschema const* sc) {
            FillDefinition fillDef(propName == "Embedded" ? subSceneLevel + 1 : 0);
            auto visitor = valijson::Schema::ApplyFunction(
                [&fillDef](valijson::constraints::Constraint const& constraint) {
                    return constraint.accept(fillDef);
                });
            bool ok = sc->apply(visitor);
            schema.properties.emplace(propName.c_str(), std::move(fillDef.schema));
            return ok;
        });
        return true;
    }
    bool visit(const PropertyNamesConstraint&) final
    {
        assert(false && "Unexpected constraint PropertyNamesConstraint");
        return true;
    }
    bool visit(const RequiredConstraint&) final
    {
        // TODO : load RequiredConstraint
        return true;
    }
    bool visit(const SingularItemsConstraint& c) final
    {
        auto sc = c.getItemsSubschema();
        if (subSceneLevel == 2) // We are in the "SubScene"/"properties"/"Embedded"/"items"
        {
            Ent::Subschema sub;
            sub.type = Ent::DataType::freeobject;
            schema.singularItems = std::make_unique<Ent::Subschema>(std::move(sub));
        }
        else
        {
            FillDefinition itemDef(0);
            auto visitor = valijson::Schema::ApplyFunction(
                [&itemDef](valijson::constraints::Constraint const& constraint) {
                    return constraint.accept(itemDef);
                });
            sc->apply(visitor);
            schema.singularItems = std::make_unique<Ent::Subschema>(std::move(itemDef.schema));
        }
        return true;
    }
    bool visit(const TypeConstraint& c) final
    {
        c.applyToNamedTypes([this](valijson::constraints::TypeConstraint::JsonType type) {
            assert((schema.type == Ent::DataType::null) && "Multiple type in Subschema is Unexpected");
            switch (type)
            {
            case valijson::constraints::TypeConstraint::kAny:
                assert("Unexpected JSON schema type : Any");
                break;
            case valijson::constraints::TypeConstraint::kArray:
                schema.type = Ent::DataType::array;
                break;
            case valijson::constraints::TypeConstraint::kBoolean:
                schema.type = Ent::DataType::boolean;
                break;
            case valijson::constraints::TypeConstraint::kInteger:
                schema.type = Ent::DataType::integer;
                break;
            case valijson::constraints::TypeConstraint::kNull:
                schema.type = Ent::DataType::null;
                break;
            case valijson::constraints::TypeConstraint::kNumber:
                schema.type = Ent::DataType::number;
                break;
            case valijson::constraints::TypeConstraint::kObject:
                schema.type = Ent::DataType::object;
                break;
            case valijson::constraints::TypeConstraint::kString:
                schema.type = Ent::DataType::string;
                break;
            }
            return true;
        });

        return true;
    }
    bool visit(const UniqueItemsConstraint&) final
    {
        assert(false && "Unexpected constraint UniqueItemsConstraint");
        return true;
    }
};

// ******************************* Utilities to search in schema **********************************

template <typename Cons>
Cons const* findConstraint(valijson::Subschema const* sc)
{
    Cons const* foundConstraint = nullptr;
    valijson::Schema::ApplyFunction findPropConstF = [&](valijson::constraints::Constraint const& c) {
        if (Cons const* found = dynamic_cast<Cons const*>(&c))
        {
            foundConstraint = found;
            return false;
        }
        return true;
    };
    sc->apply(findPropConstF);
    return foundConstraint;
}

valijson::Subschema const* findProperty(valijson::Subschema const* sc, char const* name)
{
    auto props = findConstraint<valijson::constraints::PropertiesConstraint>(sc);
    valijson::Subschema const* result = nullptr;
    props->applyToProperties([name, &result](auto const& propName, valijson::Subschema const* prop) {
        if (propName == name)
        {
            result = prop;
            return false;
        }
        return true;
    });
    return result;
}

#endif

namespace Ent
{
    BadType::BadType()
        : std::runtime_error("Bad node type")
    {
    }

#ifdef ENTLIB_LOADSCHEMA
    EntityLib loadStaticData(std::filesystem::path const& toolsDir) // Read schema and dependencies
    {
        sprintf_s(schemaPath, std::size(schemaPath), "%ls/WildPipeline/Schema", toolsDir.c_str());

        json schemaDocument;
        if (!valijson::utils::loadDocument(
                (toolsDir / "WildPipeline/Schema/Scene-schema.json").u8string(), schemaDocument))
        {
            return EntityLib{};
        }

        // Parse the json schema into an internal schema format
        valijson::Schema schema;
        valijson::SchemaParser parser;
        valijson::adapters::NlohmannJsonAdapter schemaDocumentAdapter(schemaDocument);
        try
        {
            parser.populateSchema(schemaDocumentAdapter, schema, fetchDocument, freeDocument);
        }
        catch (std::exception& e)
        {
            std::cerr << "Failed to parse schema: " << e.what() << std::endl;
            return EntityLib{};
        }

        Schema entSchema;

        // Find PropertiesConstraint named Objects
        auto objects = findProperty(schema.root(), "Objects");
        // find SingularItemsConstraint
        auto objItem = findConstraint<valijson::constraints::SingularItemsConstraint>(objects);
        // find PropertiesConstraint named Components
        auto components = findProperty(objItem->getItemsSubschema(), "Components");
        // find SingularItemsConstraint
        auto compoItem = findConstraint<valijson::constraints::SingularItemsConstraint>(components);
        auto oneOf =
            findConstraint<valijson::constraints::OneOfConstraint>(compoItem->getItemsSubschema());
        // For each
        oneOf->applyToSubschemas([&entSchema](int, valijson::Subschema const* sc) {
            //      Find PropertiesConstraint
            auto type = findProperty(sc, "Type");
            //      Find Type to get the name of the componant
            auto constConst = findConstraint<valijson::constraints::ConstConstraint>(type);
            std::string compName = getFrozenValue(constConst->getValue()).get<std::string>();

            // if (compName == "SubScene")
            //    return true;
            //      Find Data
            valijson::Subschema const* data = findProperty(sc, "Data");

            FillDefinition visitConstraint(compName == "SubScene" ? 1 : 0);

            valijson::Subschema::ApplyFunction func =
                [&visitConstraint](valijson::constraints::Constraint const& c) {
                    return c.accept(visitConstraint);
                };
            data->apply(func);

            entSchema.definitions.emplace(compName, std::move(visitConstraint.schema));

            return true;
        });

        json dependencies = loadJsonFile(toolsDir / "WildPipeline/Schema/Dependencies.json");
        std::map<std::string, std::vector<std::string>> componentDependencies;
        for (json const& comp : dependencies["Dependencies"])
        {
            auto name = comp["className"].get<std::string>();
            std::vector<std::string> deps;
            for (json const& dep : comp["dependencies"])
            {
                if (dep["Optional"].get<bool>() == false)
                {
                    deps.push_back(dep["Name"].get<std::string>());
                }
            }
            componentDependencies.emplace(std::move(name), std::move(deps));
        }

        return EntityLib{ std::move(entSchema), std::move(componentDependencies) };
    }
#endif

    Node::Node(Value val, Subschema const* _schema)
        : schema(_schema)
        , value(std::move(val))
    {
    }

    DataType Node::getDataType() const
    {
        return (DataType)value.which();
    }

    Node* Node::at(char const* field)
    {
        if (value.is<Object>())
        {
            return value.get<Object>().at(field).get();
        }
        throw BadType();
    }
    Node const* Node::at(char const* field) const
    {
        if (value.is<Object>())
        {
            return value.get<Object>().at(field).get();
        }
        throw BadType();
    }
    bool Node::count(char const* field) const
    {
        if (value.is<Object>())
        {
            return value.get<Object>().count(field) != 0;
        }
        throw BadType();
    }
    Node* Node::at(size_t index)
    {
        if (value.is<Array>())
        {
            return value.get<Array>().data[index].get();
        }
        throw BadType();
    }
    Node const* Node::at(size_t index) const
    {
        if (value.is<Object>())
        {
            auto iter = value.get<Object>().begin();
            std::advance(iter, index);
            return iter->second.get();
        }
        if (value.is<Array>())
        {
            return value.get<Array>().data[index].get();
        }
        throw BadType();
    }
    size_t Node::size() const
    {
        if (value.is<Array>())
        {
            return value.get<Array>().data.size();
        }
        throw BadType();
    }

    float Node::getFloat() const
    {
        if (value.is<Override<float>>())
        {
            return value.get<Override<float>>().get();
        }
        if (value.is<Override<int64_t>>())
        {
            return static_cast<float>(value.get<Override<int64_t>>().get());
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
        if (value.is<Override<std::string>>())
        {
            return value.get<Override<std::string>>().get().c_str();
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

    void Node::setNone()
    {
        value = Null{};
    }
    void Node::setFloat(float val)
    {
        value.get<Override<float>>().set(val);
    }
    void Node::setInt(int64_t val)
    {
        value.get<Override<int64_t>>().set(val);
    }
    void Node::setString(char const* val)
    {
        value.get<Override<std::string>>().set(val);
    }
    void Node::setBool(bool val)
    {
        value.get<Override<bool>>().set(val);
    }

    struct UnSet
    {
        template <typename T>
        void operator()(Override<T>& ov) const
        {
            ov.unset();
        }

        template <typename U>
        void operator()(U& notOverride) const
        {
            (void*)&notOverride;
            throw BadType();
        }
    };

    void Node::unset()
    {
        std::apply_visitor(UnSet{}, value);
    }

    struct IsSet
    {
        template <typename T>
        bool operator()(Override<T> const& ov) const
        {
            return ov.isSet();
        }

        template <typename U>
        bool operator()(U const& notOverride) const
        {
            (void*)&notOverride;
            // throw BadType();
            return true; // Object and Array are always considered as overrided
        }
    };

    bool Node::isSet() const
    {
        return std::apply_visitor(IsSet{}, value);
    }

    bool Node::isArraySizeSet() const
    {
        if (value.is<Array>())
        {
            return value.get<Array>().size.isSet();
        }
        throw BadType();
    }

    std::vector<char const*> Node::getFieldNames() const
    {
        if (value.is<Object>())
        {
            std::vector<char const*> fields;
            for (auto&& f : value.get<Object>())
            {
                fields.push_back(f.first.c_str());
            }
            return fields;
        }
        throw BadType();
    }

    std::vector<Node const*> Node::getItems() const
    {
        if (value.is<Array>())
        {
            std::vector<Node const*> items;
            for (auto&& n : value.get<Array>().data)
            {
                items.push_back(n.get());
            }
            return items;
        }
        throw BadType();
    }

    Node* Node::push()
    {
        if (value.is<Array>())
        {
            if (auto itemSchema = schema->singularItems.get())
            {
                value.get<Array>().data.emplace_back(
                    std::make_unique<Node>(loadNode(*itemSchema, json(), nullptr)));
                return value.get<Array>().data.back().get();
            }
        }
        throw BadType();
    }
    void Node::pop()
    {
        if (value.is<Array>())
        {
            value.get<Array>().data.pop_back();
        }
        throw BadType();
    }

    // ********************************* Entity ***************************************************

    Entity::Entity(
        std::string _name,
        std::array<uint8_t, 4> _color,
        std::map<std::string, Component> _components,
        tl::optional<std::string> _instanceOf)
        : name(std::move(_name))
        , color(_color)
        , components(std::move(_components))
        , instanceOf(std::move(_instanceOf))
    {
    }

    char const* Entity::getName() const
    {
        return name.c_str();
    }
    void Entity::setName(std::string _name)
    {
        name = _name;
    }
    char const* Entity::getInstanceOf() const
    {
        return instanceOf.has_value() ? instanceOf->c_str() : nullptr;
    }
    std::array<uint8_t, 4> Entity::getColor() const
    {
        return color;
    }
    void Entity::setColor(std::array<uint8_t, 4> _color)
    {
        color = _color;
    }
    Component* Entity::addComponent(EntityLib const& entlib, char const* type)
    {
        if (entlib.componentDependencies.count(type)) // Could be an editor componant
        {
            for (auto&& dep : entlib.componentDependencies.at(type))
            {
                addComponent(entlib, dep.c_str());
            }
        }
        Ent::Subschema const& compSchema = entlib.schema.definitions.at(type);
        Ent::Component comp{ type, loadNode(compSchema, json(), nullptr), 1, components.size() };
        auto iter_bool = components.emplace(type, std::move(comp));
        return &(iter_bool.first->second);
    }
    Component const* Entity::getComponent(char const* type) const
    {
        auto iter = components.find(type);
        return iter == components.end() ? nullptr : &(iter->second);
    }
    Component* Entity::getComponent(char const* type)
    {
        auto iter = components.find(type);
        return iter == components.end() ? nullptr : &(iter->second);
    }
    void Entity::removeComponent(char const* type)
    {
        // TODO : Use dependencies
        components.erase(type);
    }

    std::vector<char const*> Entity::getComponentTypes() const
    {
        std::vector<char const*> types;
        for (auto&& type_comp : components)
            types.push_back(type_comp.first.c_str());
        return types;
    }

    std::map<std::string, Component> const& Entity::getComponents() const
    {
        return components;
    }

} // namespace Ent

// ********************************** Load/Save ***********************************************

static Ent::Node loadFreeObjectNode(json const& data)
{
    Ent::Node result;
    switch (data.type())
    {
    case nlohmann::detail::value_t::null: result = Ent::Node(Ent::Null{}, nullptr); break;
    case nlohmann::detail::value_t::string:
        result = Ent::Node(Ent::Override<std::string>(data.get<std::string>()), nullptr);
        break;
    case nlohmann::detail::value_t::boolean:
        result = Ent::Node(Ent::Override<bool>(data.get<bool>()), nullptr);
        break;
    case nlohmann::detail::value_t::number_integer:
    case nlohmann::detail::value_t::number_unsigned:
        result = Ent::Node(Ent::Override<int64_t>(data.get<int64_t>()), nullptr);
        break;
    case nlohmann::detail::value_t::number_float:
        result = Ent::Node(Ent::Override<float>(data.get<float>()), nullptr);
        break;
    case nlohmann::detail::value_t::object:
    {
        Ent::Object object;
        for (auto const& field : data.items())
        {
            std::string const& name = field.key();
            json const& value = field.value();
            Ent::Node tmpNode = loadFreeObjectNode(value);
            object.emplace(name, std::make_unique<Ent::Node>(std::move(tmpNode)));
        }
        result = Ent::Node(std::move(object), nullptr);
    }
    break;
    case nlohmann::detail::value_t::array:
    {
        Ent::Array arr;
        for (auto const& item : data)
        {
            Ent::Node tmpNode = loadFreeObjectNode(item);
            arr.data.emplace_back(std::make_unique<Ent::Node>(std::move(tmpNode)));
        }
        arr.size = static_cast<int64_t>(data.size());
        result = Ent::Node(std::move(arr), nullptr);
    }
    break;
    case nlohmann::detail::value_t::discarded: break;
    }
    return result;
}

static Ent::Node const emptyNode(Ent::Null(), nullptr);

static Ent::Node loadNode(Ent::Subschema const& nodeSchema, json const& data, Ent::Node const* super)
{
    Ent::Node result;

    switch (nodeSchema.type)
    {
    case Ent::DataType::null: result = Ent::Node(Ent::Null{}, &nodeSchema); break;
    case Ent::DataType::string:
    {
        std::string const def = nodeSchema.defaultValue.is_null() ?
                                    std::string() :
                                    nodeSchema.defaultValue.get<std::string>();
        std::string const supVal = super ? super->getString() : def;
        result = Ent::Node(Ent::Override<std::string>(supVal), &nodeSchema);
        if (data.is_string())
            result.setString(data.get<std::string>().c_str());
    }
    break;
    case Ent::DataType::boolean:
    {
        bool const def =
            nodeSchema.defaultValue.is_null() ? false : nodeSchema.defaultValue.get<bool>();
        bool const supVal = super ? super->getBool() : def;
        result = Ent::Node(Ent::Override<bool>(supVal), &nodeSchema);
        if (data.is_boolean())
            result.setBool(data.get<bool>());
    }
    break;
    case Ent::DataType::integer:
    {
        int64_t const def =
            nodeSchema.defaultValue.is_null() ? false : nodeSchema.defaultValue.get<int64_t>();
        int64_t const supVal = super ? super->getInt() : def;
        result = Ent::Node(Ent::Override<int64_t>(supVal), &nodeSchema);
        if (data.is_number_integer() or data.is_number_unsigned())
            result.setInt(data.get<int64_t>());
    }
    break;
    case Ent::DataType::number:
    {
        float const def =
            nodeSchema.defaultValue.is_null() ? false : nodeSchema.defaultValue.get<float>();
        float const supVal = super ? super->getFloat() : def;
        result = Ent::Node(Ent::Override<float>(supVal), &nodeSchema);
        if (data.is_number_float())
            result.setFloat(data.get<float>());
    }
    break;
    case Ent::DataType::object:
    {
        Ent::Object object;

        for (auto&& name_sub : nodeSchema.properties)
        {
            std::string const& name = std::get<0>(name_sub);
            Ent::Node const* superProp = super ? super->at(name.c_str()) : nullptr;
            static json const emptyJson;
            json const& prop = data.count(name) ? data.at(name) : emptyJson;
            Ent::Node tmpNode = loadNode(std::get<1>(name_sub), prop, superProp);
            object.emplace(name, std::make_unique<Ent::Node>(std::move(tmpNode)));
        }
        result = Ent::Node(std::move(object), &nodeSchema);
    }
    break;
    case Ent::DataType::array:
    {
        Ent::Array arr;
        size_t index = 0;
        if (nodeSchema.singularItems)
        {
            for (auto const& item : data)
            {
                Ent::Node const* subSuper =
                    (super and (super->size() > index)) ? super->at(index) : nullptr;
                Ent::Node tmpNode = loadNode(*nodeSchema.singularItems, item, subSuper);
                arr.data.emplace_back(std::make_unique<Ent::Node>(std::move(tmpNode)));
                ++index;
            }
            arr.size = static_cast<int64_t>(data.size());
        }
        else
        {
            assert(nodeSchema.linearItems.has_value());
            for (Ent::Subschema const& sub : *nodeSchema.linearItems)
            {
                Ent::Node const* subSuper =
                    (super and super->size() > index) ? super->at(index) : nullptr;
                static json const emptyJson;
                json const& prop = data.size() > index ? data.at(index) : emptyJson;
                Ent::Node tmpNode = loadNode(sub, prop, subSuper);
                arr.data.emplace_back(std::make_unique<Ent::Node>(std::move(tmpNode)));
                ++index;
            }
            arr.size = static_cast<int64_t>(nodeSchema.linearItems->size());
        }
        result = Ent::Node(std::move(arr), &nodeSchema);
    }
    break;
    case Ent::DataType::freeobject:
    {
        Ent::Object object;
        for (auto const& field : data.items())
        {
            std::string const& name = field.key();
            json const& value = field.value();
            Ent::Node tmpNode = loadFreeObjectNode(value);
            object.emplace(name, std::make_unique<Ent::Node>(std::move(tmpNode)));
        }
        result = Ent::Node(std::move(object), &nodeSchema);
    }
    break;
    }
    return result;
}

static json saveFreeObjectNode(Ent::Node const& node)
{
    json data;
    switch (node.getDataType())
    {
    case Ent::DataType::null: break;
    case Ent::DataType::string: data = node.getString(); break;
    case Ent::DataType::boolean: data = node.getBool(); break;
    case Ent::DataType::integer: data = node.getInt(); break;
    case Ent::DataType::number: data = node.getFloat(); break;
    case Ent::DataType::object:
    case Ent::DataType::freeobject:
    {
        data = json::object();
        for (auto const& name : node.getFieldNames())
        {
            Ent::Node const* subNode = node.at(name);
            json subJson = saveFreeObjectNode(*subNode);
            data[name] = std::move(subJson);
        }
    }
    break;
    case Ent::DataType::array:
    {
        data = json::array();
        for (Ent::Node const* item : node.getItems())
        {
            json tmpNode = saveFreeObjectNode(*item);
            data.emplace_back(std::move(tmpNode));
        }
    }
    break;
    }
    return data;
}

static json saveNode(Ent::Subschema const& schema, Ent::Node const& node)
{
    json data;
    switch (schema.type)
    {
    case Ent::DataType::null: break;
    case Ent::DataType::string: data = node.getString(); break;
    case Ent::DataType::boolean: data = node.getBool(); break;
    case Ent::DataType::integer: data = node.getInt(); break;
    case Ent::DataType::number: data = node.getFloat(); break;
    case Ent::DataType::object:
    {
        data = json::object();
        for (auto const& name_sub : schema.properties)
        {
            auto&& name = std::get<0>(name_sub);
            Ent::Node const* subNode = node.at(name.c_str());
            if (subNode->isSet())
            {
                json subJson = saveNode(std::get<1>(name_sub), *subNode);
                data[name] = std::move(subJson);
            }
        }
    }
    break;
    case Ent::DataType::freeobject:
    {
        data = json::object();
        for (auto const& name : node.getFieldNames())
        {
            Ent::Node const* subNode = node.at(name);
            json subJson = saveFreeObjectNode(*subNode);
            data[name] = std::move(subJson);
        }
    }
    break;
    case Ent::DataType::array:
    {
        data = json::array();
        for (Ent::Node const* item : node.getItems())
        {
            if (item->isSet())
            {
                json tmpNode = saveNode(*schema.singularItems, *item);
                data.emplace_back(std::move(tmpNode));
            }
            else
            {
                data.emplace_back(json());
            }
        }
    }
    break;
    }
    return data;
}

static Ent::Entity loadEntity(Ent::EntityLib const& entlib, Ent::Schema const& schema, json const& entNode)
{
    // TODO override, types and default values

    tl::optional<std::string> instanceOf;
    Ent::Entity superEntity;
    if (entNode.count("InstanceOf"))
    {
        instanceOf = entNode.at("InstanceOf").get<std::string>();
        superEntity = entlib.loadEntity(*instanceOf);
    }

    auto name = entNode.at("Name").get<std::string>();

    std::array<uint8_t, 4> color{}; // {} => init to zero
    if (entNode.contains("Color"))
    {
        json const& colorNode = entNode.at("Color");
        colorNode[0].get_to(color[0]);
        colorNode[1].get_to(color[1]);
        colorNode[2].get_to(color[2]);
        colorNode[3].get_to(color[3]);
    }

    std::map<std::string, Ent::Component> components;
    json const& componentsNode = entNode.at("Components");
    size_t index = 0;
    for (json const& compNode : componentsNode)
    {
        auto const cmpType = compNode.at("Type").get<std::string>();
        Ent::Component* superComp = superEntity.getComponent(cmpType.c_str());
        auto const version = compNode.at("Version").get<size_t>();
        json const& data = compNode.at("Data");

        Ent::Subschema const& compSchema = schema.definitions.at(cmpType);

        Ent::Component comp{ cmpType,
                             loadNode(compSchema, data, (superComp ? &superComp->root : nullptr)),
                             version,
                             index };

        components.emplace(cmpType, std::move(comp));
        ++index;
    }
    return Ent::Entity(std::move(name), color, std::move(components), instanceOf);
}

Ent::Entity Ent::EntityLib::loadEntity(std::filesystem::path const& entityPath) const
{
    std::ifstream file(entityPath);
    if (not file.is_open())
    {
        constexpr size_t MessSize = 1024;
        std::array<char, MessSize> message = {};
        sprintf_s(message.data(), MessSize, "Can't open file for read: %ls", entityPath.c_str());
        throw std::runtime_error(message.data());
    }
    json document;
    file >> document;

    Ent::Entity ent = ::loadEntity(*this, schema, document);
    return ent;
}

Ent::Scene Ent::EntityLib::loadScene(std::filesystem::path const& scenePath) const
{
    json document;
    {
        std::ifstream file(scenePath);
        if (not file.is_open())
        {
            constexpr size_t MessSize = 1024;
            std::array<char, MessSize> message = {};
            sprintf_s(message.data(), MessSize, "Can't open file for read: %ls", scenePath.c_str());
            throw std::runtime_error(message.data());
        }
        file >> document;
    }

    // Reformat input to make diff easier
    /*{
        std::ofstream file(scenePath);
        file << document.dump(4);
    }*/

    Scene scene;

    for (json const& entNode : document.at("Objects"))
    {
        Ent::Entity ent = ::loadEntity(*this, schema, entNode);
        scene.objects.emplace_back(std::move(ent));
    }

    return scene;
}

static json saveEntity(Ent::Schema const& schema, Ent::Entity const& entity)
{
    // TODO override, types and default values
    json entNode;

    entNode.emplace("Name", entity.getName());

    if (char const* instanceOf = entity.getInstanceOf())
    {
        entNode.emplace("InstanceOf", instanceOf);
    }

    entNode.emplace("Color", entity.getColor());

    json& componentsNode = entNode["Components"];
    std::vector<Ent::Component const*> sortedComp;
    for (auto&& type_comp : entity.getComponents())
    {
        sortedComp.push_back(&std::get<1>(type_comp));
    }
    std::sort(
        begin(sortedComp), end(sortedComp), [](Ent::Component const* cmp, Ent::Component const* cmp2) {
            return cmp->index < cmp2->index;
        });
    for (Ent::Component const* comp : sortedComp)
    {
        json compNode;
        compNode.emplace("Version", comp->version);
        compNode.emplace("Type", comp->type);
        compNode.emplace("Data", saveNode(schema.definitions.at(comp->type), comp->root));

        componentsNode.emplace_back(std::move(compNode));
    }
    return entNode;
}

void Ent::EntityLib::saveEntity(Entity const& entity, std::filesystem::path const& entityPath) const
{
    std::ofstream file(entityPath);
    if (not file.is_open())
    {
        constexpr size_t MessSize = 1024;
        std::array<char, MessSize> message = {};
        sprintf_s(message.data(), MessSize, "Can't open file for write: %ls", entityPath.c_str());
        throw std::runtime_error(message.data());
    }
    json document = ::saveEntity(schema, entity);

    file << document.dump(4);
}

void Ent::EntityLib::saveScene(Scene const& scene, std::filesystem::path const& scenePath) const
{
    std::ofstream file(scenePath);
    if (not file.is_open())
    {
        constexpr size_t MessSize = 1024;
        std::array<char, MessSize> message = {};
        sprintf_s(message.data(), MessSize, "Can't open file for write: %ls", scenePath.c_str());
        throw std::runtime_error(message.data());
    }
    json document;

    document.emplace("Version", 2);
    json& objects = document["Objects"];

    for (Ent::Entity const& ent : scene.objects)
    {
        objects.emplace_back(::saveEntity(schema, ent));
    }

    file << document.dump(4);
}

Ent::Component* Ent::EntityLib::addComponent(Entity& entity, char const* type) const
{
    return entity.addComponent(*this, type);
}

void Ent::mergeComponants(std::filesystem::path const& toolsDir)
{
    json runtimeCompSch = loadJsonFile(toolsDir / "WildPipeline/Schema/RuntimeComponants.json");
    json editionCompSch = loadJsonFile(toolsDir / "WildPipeline/Schema/EditionComponents.json");
    auto sceneSchemaPath = toolsDir / "WildPipeline/Schema/Scene-schema.json";
    json sceneSch = loadJsonFile(sceneSchemaPath);
    json dependencies = loadJsonFile(toolsDir / "WildPipeline/Schema/Dependencies.json");

    runtimeCompSch = runtimeCompSch["definitions"];
    editionCompSch = editionCompSch["definitions"];

    auto&& compList = sceneSch["definitions"]["Component"]["oneOf"];
    compList = json();

    // Looking for components with same name and merge them
    std::map<std::string, json const*> editionCompMap;
    std::set<std::string> alreadyInsertedComponents;
    for (auto&& name_comp : editionCompSch.items())
    {
        editionCompMap.emplace(name_comp.key(), &(name_comp.value()));
    }

    for (json const& dep : dependencies["Dependencies"])
    {
        auto name = dep["className"].get<std::string>();
        auto iter = editionCompMap.find(name);
        if (iter != editionCompMap.end())
        {
            json merged = dep.value("properties", json());
            merged.update(*iter->second);

            json newComp;
            auto&& prop = newComp["properties"];
            prop["Type"]["const"] = name;
            prop["Data"] = std::move(merged);

            compList.push_back(std::move(newComp));
            alreadyInsertedComponents.insert(name);
        }
    }

    // Add other components
    auto addComponent = [&](std::string const& name, char const* filename) {
        if (alreadyInsertedComponents.count(name))
            return;
        json newComp;
        auto&& prop = newComp["properties"];
        prop["Type"]["const"] = name;
        prop["Data"]["$ref"] = "file://" + (filename + ("#/definitions/" + name));

        compList.push_back(std::move(newComp));
    };
    for (auto&& name_comp : editionCompSch.items())
    {
        addComponent(name_comp.key(), "EditionComponents.json");
    }

    for (json const& dep : dependencies["Dependencies"])
    {
        auto name = dep["className"].get<std::string>();
        addComponent(name, "RuntimeComponants.json");
    }

    std::ofstream file(sceneSchemaPath);
    if (not file.is_open())
    {
        throw std::runtime_error("Can't open file for write: " + sceneSchemaPath.u8string());
    }
    file << sceneSch.dump(4);
}
