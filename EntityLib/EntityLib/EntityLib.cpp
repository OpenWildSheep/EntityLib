#include "include/EntityLib.h"

#include <iostream>
#include <fstream>

#pragma warning(push, 0)
#include "external/json.hpp"
#ifdef ENTLIB_LOADSCHEMA
#include <valijson/adapters/nlohmann_json_adapter.hpp>
#include <valijson/utils/nlohmann_json_utils.hpp>
#include <valijson/schema.hpp>
#include <valijson/schema_parser.hpp>
#endif
#pragma warning(pop)

using namespace nlohmann;
// using valijson::Schema;
// using valijson::SchemaParser;

#ifdef ENTLIB_LOADSCHEMA

json const* fetchDocument(const std::string& uri)
{
    std::cout << "Fetching " << uri << "..." << std::endl;
    json* fetchedRoot = new json{};
    if (!valijson::utils::loadDocument(
            uri.substr(0, 7) == "file://" ? uri.substr(7, uri.size()) : uri, *fetchedRoot))
    {
        return nullptr;
    }

    return fetchedRoot;
}

void freeDocument(json const* adapter)
{
    delete adapter;
}

std::string indent;

void iterateJsonObject(const valijson::adapters::NlohmannJsonAdapter& adapter)
{
    if (adapter.maybeObject())
    {
        std::cout << "Object members:" << std::endl;

        // JSON objects are an unordered collection of key-value pairs,
        // so the members of the object may be printed in an order that is
        // different to that in the source JSON document.
        for (auto member : adapter.asObject())
        {
            // The key is a std::string that can be accessed using 'first'
            std::cout << indent << member.first << ": " << std::endl;

            // The value is just another Adapter, and can be accessed using 'second'
            const valijson::adapters::NlohmannJsonAdapter& value = member.second;
            /*if (value.maybeString())
            {
                std::cout << value.asString();
            }
            std::cout << std::endl;*/

            indent += "  ";
            valijson::adapters::NlohmannJsonAdapter adapter2(value);
            iterateJsonObject(adapter2);
            indent.resize(indent.size() - 2);
        }
        return;
    }
    if (adapter.maybeArray())
    {

        for (auto member : adapter.asArray())
        {
            // The key is a std::string that can be accessed using 'first'
            // std::cout << "  " << member.first << ": ";

            // The value is just another Adapter, and can be accessed using 'second'
            const valijson::adapters::NlohmannJsonAdapter& value = member;
            /*if (value.maybeString())
            {
                std::cout << value.asString();
            }
            std::cout << std::endl;*/

            indent += "  ";
            valijson::adapters::NlohmannJsonAdapter adapter2(value);
            iterateJsonObject(adapter2);
            indent.resize(indent.size() - 2);
        }
    }
    if (adapter.maybeBool())
    {
        std::cout << indent << adapter.asBool() << std::endl;
        return;
    }
    if (adapter.maybeString())
    {
        std::cout << indent << adapter.asString() << std::endl;
        return;
    }
    if (adapter.maybeInteger())
    {
        std::cout << indent << adapter.asInteger() << std::endl;
        return;
    }
    if (adapter.maybeDouble())
    {
        std::cout << indent << adapter.asDouble() << std::endl;
        return;
    }
}

static bool schemaVisitor(valijson::constraints::Constraint const& constraint);

class NlohmannJsonFrozenValue : public valijson::adapters::FrozenValue
{
public:
    nlohmann::json m_value;
};

json const& getConstValue(const valijson::constraints::ConstConstraint& c)
{
    valijson::adapters::FrozenValue const* val = c.getValue();
    auto val2 = reinterpret_cast<NlohmannJsonFrozenValue const*>(val);
    return val2->m_value;
}

/// Interface to allow usage of the visitor pattern with Constraints
class EntConstraintPrint : public valijson::constraints::ConstraintVisitor
{
public:
    bool visit(const AllOfConstraint& c) final
    {
        std::cout << indent << "AllOfConstraint" << std::endl;
        indent += "  ";
        c.applyToSubschemas([](int i, valijson::Subschema const* sc) {
            std::cout << indent << i << std::endl;
            auto visitor = valijson::Schema::ApplyFunction(&schemaVisitor);
            return sc->apply(visitor);
        });
        indent.resize(indent.size() - 2);
        return true;
    }
    bool visit(const AnyOfConstraint& c) final
    {
        std::cout << indent << "AnyOfConstraint" << std::endl;
        indent += "  ";
        c.applyToSubschemas([](int i, valijson::Subschema const* sc) {
            std::cout << indent << i << std::endl;
            auto visitor = valijson::Schema::ApplyFunction(&schemaVisitor);
            return sc->apply(visitor);
        });
        indent.resize(indent.size() - 2);
        return true;
    }
    bool visit(const ConditionalConstraint&) final
    {
        std::cout << indent << "ConditionalConstraint" << std::endl;
        return true;
    }
    bool visit(const ConstConstraint& c) final
    {
        std::cout << indent << "ConstConstraint : ";
        std::cout << getConstValue(c).get<std::string>() << std::endl;
        return true;
    }
    bool visit(const ContainsConstraint&) final
    {
        return true;
    }
    bool visit(const DependenciesConstraint&) final
    {
        return true;
    }
    bool visit(const EnumConstraint&) final
    {
        return true;
    }
    bool visit(const LinearItemsConstraint&) final
    {
        return true;
    }
    bool visit(const MaximumConstraint&) final
    {
        return true;
    }
    bool visit(const MaxItemsConstraint& c) final
    {
        std::cout << indent << "MaxItemsConstraint : " << c.getMaxItems() << std::endl;
        return true;
    }
    bool visit(const MaxLengthConstraint&) final
    {
        return true;
    }
    bool visit(const MaxPropertiesConstraint&) final
    {
        return true;
    }
    bool visit(const MinimumConstraint&) final
    {
        return true;
    }
    bool visit(const MinItemsConstraint& c) final
    {
        std::cout << indent << "MinItemsConstraint : " << c.getMinItems() << std::endl;
        return true;
    }
    bool visit(const MinLengthConstraint&) final
    {
        return true;
    }
    bool visit(const MinPropertiesConstraint&) final
    {
        return true;
    }
    bool visit(const MultipleOfDoubleConstraint&) final
    {
        return true;
    }
    bool visit(const MultipleOfIntConstraint&) final
    {
        return true;
    }
    bool visit(const NotConstraint&) final
    {
        return true;
    }
    bool visit(const OneOfConstraint& c) final
    {
        std::cout << indent << "OneOfConstraint" << std::endl;
        indent += "  ";
        c.applyToSubschemas([](int i, valijson::Subschema const* sc) {
            std::cout << indent << i << std::endl;
            auto visitor = valijson::Schema::ApplyFunction(&schemaVisitor);
            return sc->apply(visitor);
        });
        indent.resize(indent.size() - 2);
        return true;
    }
    bool visit(const PatternConstraint&) final
    {
        return true;
    }
    bool visit(const PolyConstraint&) final
    {
        return true;
    }
    bool visit(const PropertiesConstraint& c) final
    {
        std::cout << indent << "PropertiesConstraint" << std::endl;
        indent += "  ";
        c.applyToProperties([](auto const& propName, valijson::Subschema const* sc) {
            std::cout << indent << propName << std::endl;
            indent += "  ";
            auto visitor = valijson::Schema::ApplyFunction(&schemaVisitor);
            bool ok = sc->apply(visitor);
            indent.resize(indent.size() - 2);
            return ok;
        });
        indent.resize(indent.size() - 2);
        return true;
    }
    bool visit(const PropertyNamesConstraint&) final
    {
        return true;
    }
    bool visit(const RequiredConstraint& c) final
    {
        std::cout << indent << "RequiredConstraint" << std::endl;
        indent += "  ";
        c.applyToRequiredProperties([](auto const& propName) {
            std::cout << indent << propName << std::endl;
            return true;
        });
        indent.resize(indent.size() - 2);
        return true;
    }
    bool visit(const SingularItemsConstraint& c) final
    {
        std::cout << indent << "SingularItemsConstraint" << std::endl;
        indent += "  ";
        auto sc = c.getItemsSubschema();
        auto visitor = valijson::Schema::ApplyFunction(&schemaVisitor);
        auto ok = sc->apply(visitor);
        indent.resize(indent.size() - 2);
        return ok;
    }
    bool visit(const TypeConstraint& c) final
    {
        static char const* JsonTypeStr[]{ "kAny",  "kArray",  "kBoolean", "kInteger",
                                          "kNull", "kNumber", "kObject",  "kString" };
        std::cout << indent << "TypeConstraint" << std::endl;
        indent += "  ";
        c.applyToNamedTypes([](valijson::constraints::TypeConstraint::JsonType type) {
            std::cout << indent << JsonTypeStr[type] << std::endl;
            return true;
        });

        c.applyToSchemaTypes([](int i, valijson::Subschema const* sc) {
            std::cout << indent << i << std::endl;
            indent += "  ";
            auto visitor = valijson::Schema::ApplyFunction(&schemaVisitor);
            auto ok = sc->apply(visitor);
            indent.resize(indent.size() - 2);
            return ok;
        });
        indent.resize(indent.size() - 2);
        return true;
    }
    bool visit(const UniqueItemsConstraint&) final
    {
        return true;
    }
};

/// Interface to allow usage of the visitor pattern with Constraints
class FillDefinition : public valijson::constraints::ConstraintVisitor
{
public:
    Ent::Property prop;

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
    bool visit(const EnumConstraint&) final
    {
        assert(false && "Unexpected constraint EnumConstraint");
        return true;
    }
    bool visit(const LinearItemsConstraint&) final
    {
        assert(false && "Unexpected constraint LinearItemsConstraint");
        return true;
    }
    bool visit(const MaximumConstraint&) final
    {
        assert(false && "Unexpected constraint MaximumConstraint");
        return true;
    }
    bool visit(const MaxItemsConstraint&) final
    {
        assert(false && "Unexpected constraint MaxItemsConstraint");
        // std::cout << indent << "MaxItemsConstraint : " << c.getMaxItems() << std::endl;
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
    bool visit(const MinItemsConstraint&) final
    {
        assert(false && "Unexpected constraint MinItemsConstraint");
        // std::cout << indent << "MinItemsConstraint : " << c.getMinItems() << std::endl;
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
        Ent::PropObject propObj;
        c.applyToProperties([&propObj](auto const& propName, valijson::Subschema const* sc) {
            FillDefinition fillDef;
            auto visitor = valijson::Schema::ApplyFunction(
                [&fillDef](valijson::constraints::Constraint const& constraint) {
                    return constraint.accept(fillDef);
                });
            propObj.properties.emplace(propName.c_str(), fillDef.prop);
            return sc->apply(visitor);
        });
        prop = Ent::Property("", std::move(propObj));
        return true;
    }
    bool visit(const PropertyNamesConstraint&) final
    {
        assert(false && "Unexpected constraint PropertyNamesConstraint");
        return true;
    }
    bool visit(const RequiredConstraint&) final
    {
        assert(false && "Unexpected constraint RequiredConstraint");
        return true;
    }
    bool visit(const SingularItemsConstraint& c) final
    {
        std::cout << indent << "SingularItemsConstraint" << std::endl;
        indent += "  ";
        auto sc = c.getItemsSubschema();
        auto visitor = valijson::Schema::ApplyFunction(&schemaVisitor);
        auto ok = sc->apply(visitor);
        indent.resize(indent.size() - 2);
        return ok;
    }
    bool visit(const TypeConstraint& c) final
    {
        static char const* JsonTypeStr[]{ "kAny",  "kArray",  "kBoolean", "kInteger",
                                          "kNull", "kNumber", "kObject",  "kString" };
        std::cout << indent << "TypeConstraint" << std::endl;
        indent += "  ";
        c.applyToNamedTypes([](valijson::constraints::TypeConstraint::JsonType type) {
            std::cout << indent << JsonTypeStr[type] << std::endl;
            return true;
        });

        c.applyToSchemaTypes([](int i, valijson::Subschema const* sc) {
            std::cout << indent << i << std::endl;
            indent += "  ";
            auto visitor = valijson::Schema::ApplyFunction(&schemaVisitor);
            auto ok = sc->apply(visitor);
            indent.resize(indent.size() - 2);
            return ok;
        });
        indent.resize(indent.size() - 2);
        return true;
    }
    bool visit(const UniqueItemsConstraint&) final
    {
        assert(false && "Unexpected constraint UniqueItemsConstraint");
        return true;
    }
};

template <typename Cons>
class FindConstaraintVisitor : public valijson::constraints::ConstraintVisitor
{
public:
    Cons* constraint = nullptr;
    bool visit(const Cons& c) final
    {
        constraint = &c;
        return true;
    }
};

valijson::constraints::Constraint const* foundConstraint = nullptr;

template <typename Cons>
bool findConstraintImpl(valijson::constraints::Constraint const& c)
{
    if (Cons const* found = dynamic_cast<Cons const*>(&c))
    {
        foundConstraint = found;
        return false;
    }
    return true;
}

template <typename Cons>
Cons const* findConstraint(valijson::Subschema const* sc)
{
    auto findPropConstF = valijson::Schema::ApplyFunction(findConstraintImpl<Cons>);
    sc->apply(findPropConstF);
    return (Cons const*)foundConstraint;
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

static bool schemaVisitor(valijson::constraints::Constraint const& constraint)
{
    if (indent.size() > 20)
        return true;
    EntConstraintPrint visitConstraint;
    return constraint.accept(visitConstraint);
}

#endif

namespace Ent
{
#ifdef ENTLIB_LOADSCHEMA
    StaticData loadStaticData() // Read schema and dependencies
    {
        // char const* schemaPath = "E:/code/Wild/Bin/WildEngineStatic/WildEngine/x64/Release/"
        //                         "JsonSchemas.jsn";
        // TODO : Read schema
        // TODO : Read componentDependencies

        json schemaDocument;
        if (!valijson::utils::loadDocument(
                "E:/code/WildShared/EntityLib/Test/Scene-schema.json", schemaDocument))
        {
            return StaticData{};
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
            return StaticData{};
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
        oneOf->applyToSubschemas([](int, valijson::Subschema const* sc) {
            //      Find PropertiesConstraint
            auto type = findProperty(sc, "Type");
            //      Find Type to get the name of the componant
            auto constConst = findConstraint<valijson::constraints::ConstConstraint>(type);
            std::string compName = getConstValue(*constConst).get<std::string>();
            //      Find Data
            auto data = findProperty(sc, "Data");

            Definition definition;

            std::cout << "comp : " << compName << " " << data << std::endl;
            //      Find PropertiesConstraint
            return true;
        });

        auto visitor = valijson::Schema::ApplyFunction(&schemaVisitor);
        std::cout << schema.root()->getTitle() << std::endl;
        // schema.root()->na
        schema.root()->apply(visitor);

        std::vector<std::string> cmpNames;

        std::vector<json const*> compJsons;

        /*json const& componants = schema.at("definitions").at("Component").at("oneOf");
        for (json const& comp : componants)
        {
            std::string name = comp.at("properties").at("Type").at("const").get<std::string>();
            cmpNames.emplace_back(std::move(name));
            json const& compJson = comp.at("properties").at("Data").at("$ref");
            compJsons.push_back(&compJson);
        }*/

        return StaticData{};
    }
#endif

    Node::Node(Value val)
        : value(std::move(val))
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
        value = Override<float>{ val };
    }
    void Node::setInt(int64_t val)
    {
        value = Override<int64_t>{ val };
    }
    void Node::setString(char const* val)
    {
        value = Override<std::string>{ val };
    }
    void Node::setBool(bool val)
    {
        value = Override<bool>{ val };
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
            throw BadType();
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

    // ********************************* Schema ***************************************************

    Property::Property(std::string _name, PropData _val)
        : name(std::move(_name))
        , value(std::move(_val))
    {
    }

    // ********************************* Entity ***************************************************

    char const* Entity::getName() const
    {
        return name.c_str();
    }
    void Entity::setName(std::string _name)
    {
        name = _name;
    }
    std::array<uint8_t, 4> Entity::getColor() const
    {
        return color;
    }
    void Entity::setColor(std::array<uint8_t, 4> _color)
    {
        color = _color;
    }
    Component* Entity::addComponent(char const*) // type
    {
        // TODO (check dependencies)
        return nullptr;
    }
    Component const* Entity::getComponent(char const* type) const
    {
        return &(components.at(type));
    }
    Component* Entity::getComponent(char const* type)
    {
        return &(components.at(type));
    }
    void Entity::removeComponent(char const*) // type
    {
        // TODO (check dependencies)
    }

} // namespace Ent

// ********************************** Load/Save ***********************************************

static Ent::Node loadNode(json const& data)
{
    Ent::Node result;
    switch (data.type())
    {
    case nlohmann::detail::value_t::null: result = Ent::Node(Ent::Null{}); break;
    case nlohmann::detail::value_t::string:
        result = Ent::Node(Ent::Override<std::string>(data.get<std::string>()));
        break;
    case nlohmann::detail::value_t::boolean:
        result = Ent::Node(Ent::Override<bool>(data.get<bool>()));
        break;
    case nlohmann::detail::value_t::number_integer:
    case nlohmann::detail::value_t::number_unsigned:
        result = Ent::Node(Ent::Override<int64_t>(data.get<int64_t>()));
        break;
    case nlohmann::detail::value_t::number_float:
        result = Ent::Node(Ent::Override<float>(data.get<float>()));
        break;
    case nlohmann::detail::value_t::object:
    {
        Ent::Object object;
        for (auto const& field : data.items())
        {
            std::string const& name = field.key();
            json const& value = field.value();
            Ent::Node tmpNode = loadNode(value);
            object.emplace(name, std::make_unique<Ent::Node>(std::move(tmpNode)));
        }
        result = Ent::Node(std::move(object));
    }
    break;
    case nlohmann::detail::value_t::array:
    {
        Ent::Array arr;
        for (auto const& item : data)
        {
            Ent::Node tmpNode = loadNode(item);
            arr.data.emplace_back(std::make_unique<Ent::Node>(std::move(tmpNode)));
        }
        arr.size = data.size();
        result = Ent::Node(std::move(arr));
    }
    break;
    case nlohmann::detail::value_t::discarded: break;
    }
    return result;
}

static json saveNode(Ent::Node const& node)
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
    {
        data = json::object();
        for (auto const& name : node.getFieldNames())
        {
            Ent::Node const* subNode = node.at(name);
            json subJson = saveNode(*subNode);
            data[name] = std::move(subJson);
        }
    }
    break;
    case Ent::DataType::array:
    {
        data = json::array();
        for (Ent::Node const* item : node.getItems())
        {
            json tmpNode = saveNode(*item);
            data.emplace_back(std::move(tmpNode));
        }
    }
    break;
    }
    return data;
}

static Ent::Entity loadEntity(json const& entNode)
{
    // TODO override, types and default values

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
        auto const version = compNode.at("Version").get<size_t>();
        json const& data = compNode.at("Data");
        Ent::Component comp{ cmpType, loadNode(data), version, index };

        components.emplace(cmpType, std::move(comp));
        ++index;
    }
    return Ent::Entity{ std::move(name), color, std::move(components) };
}

Ent::Entity Ent::loadEntity(std::filesystem::path const& entityPath)
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

    Ent::Entity ent = ::loadEntity(document);
    return ent;
}

Ent::Scene Ent::loadScene(std::filesystem::path const& scenePath)
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
        Ent::Entity ent = ::loadEntity(entNode);
        scene.objects.emplace_back(std::move(ent));
    }

    return scene;
}

static json saveEntity(Ent::Entity const& entity)
{
    // TODO override, types and default values
    json entNode;
    entNode.emplace("Name", entity.getName());

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
        compNode.emplace("Data", saveNode(comp->root));

        componentsNode.emplace_back(std::move(compNode));
    }
    return entNode;
}

void Ent::saveEntity(Entity const& entity, std::filesystem::path const& entityPath)
{
    std::ofstream file(entityPath);
    if (not file.is_open())
    {
        constexpr size_t MessSize = 1024;
        std::array<char, MessSize> message = {};
        sprintf_s(message.data(), MessSize, "Can't open file for write: %ls", entityPath.c_str());
        throw std::runtime_error(message.data());
    }
    json document = ::saveEntity(entity);

    file << document.dump(4);
}

void Ent::saveScene(Scene const& scene, std::filesystem::path const& scenePath)
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
        objects.emplace_back(::saveEntity(ent));
    }

    file << document.dump(4);
}
