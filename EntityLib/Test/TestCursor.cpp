#include "TestCursor.h"
#include <EntityLib.h>
#include <../Tools.h>
#include <fstream>
#include <variant>
#include <iostream>

#include <EntityLib/Visitor.h>
#include <EntityLib/CopyProperty.h>
#include <EntityLib/Property.h>

using namespace Ent;

class PrintNode : public RecursiveVisitor
{
    size_t tab = 0;

    [[nodiscard]] std::string getTab() const
    {
        return std::string(tab * 4, ' ');
    }

public:
    void inObject([[maybe_unused]] Property& _prop) override
    {
        ++tab;
    }
    bool inObjectField([[maybe_unused]] Property& _prop, char const* key) override
    {
        // std::cout << "dksflghjdfjg" << getTab() << '"' << key << "\": " << std::endl;
        std::cout << getTab() << '"' << key << "\": " << std::endl;
        ++tab;
        return true;
    }
    void outObjectField([[maybe_unused]] Property& _prop, [[maybe_unused]] char const* _key) override
    {
        --tab;
    }
    void outObject([[maybe_unused]] Property& _prop) override
    {
        --tab;
    }
    void inUnion([[maybe_unused]] Property& _prop, char const* type) override
    {
        std::cout << getTab() << '"' << type << "\": " << std::endl;
        ++tab;
    }
    void outUnion([[maybe_unused]] Property& _prop) override
    {
        --tab;
    }
    void inMap([[maybe_unused]] Property& _prop) override
    {
        ++tab;
    }
    void outMap([[maybe_unused]] Property& _prop) override
    {
        --tab;
    }
    void inMapElement([[maybe_unused]] Property& _prop, char const* key) override
    {
        ++tab;
        std::cout << getTab() << '"' << key << "\": " << std::endl;
    }
    void inMapElement([[maybe_unused]] Property& _prop, int64_t key) override
    {
        ++tab;
        std::cout << getTab() << key << ": " << std::endl;
    }
    void outMapElement([[maybe_unused]] Property& _prop) override
    {
        --tab;
    }
    void inPrimSet([[maybe_unused]] Property& _prop, DataType /*_dataType*/) override
    {
        ++tab;
    }
    void inArrayElement([[maybe_unused]] Property& _prop, size_t /*_index*/) override
    {
    }
    void outArrayElement([[maybe_unused]] Property& _prop) override
    {
    }
    void key([[maybe_unused]] Property& _prop, char const* _key) override
    {
        std::cout << getTab() << '"' << _key << '"' << std::endl;
    }
    void key([[maybe_unused]] Property& _prop, int64_t _key) override
    {
        std::cout << getTab() << _key << std::endl;
    }
    void outPrimSet([[maybe_unused]] Property& _prop) override
    {
        --tab;
    }
    void inUnionSet([[maybe_unused]] Property& _prop) override
    {
        ++tab;
    }
    void inUnionSetElement([[maybe_unused]] Property& _prop, char const* key) override
    {
        std::cout << getTab() << '"' << key << '"' << std::endl;
        ++tab;
    }
    void outUnionSetElement([[maybe_unused]] Property& _prop) override
    {
        --tab;
    }
    void outUnionSet([[maybe_unused]] Property& _prop) override
    {
        --tab;
    }
    void inObjectSet([[maybe_unused]] Property& _prop) override
    {
        ++tab;
    }
    void outObjectSet([[maybe_unused]] Property& _prop) override
    {
        --tab;
    }
    void inObjectSetElement([[maybe_unused]] Property& _prop, char const* key) override
    {
        std::cout << getTab() << '"' << key << '"' << std::endl;
    }
    void inObjectSetElement([[maybe_unused]] Property& _prop, int64_t key) override
    {
        std::cout << getTab() << key << std::endl;
    }
    void outObjectSetElement([[maybe_unused]] Property& _prop) override
    {
    }
    void inArray([[maybe_unused]] Property& _prop) override
    {
        ++tab;
    }
    void outArray([[maybe_unused]] Property& _prop) override
    {
        --tab;
    }
    void nullProperty([[maybe_unused]] Property& _prop) override
    {
        std::cout << getTab() << "null" << std ::endl;
    }
    void boolProperty(Property& _prop) override
    {
        std::cout << getTab() << _prop.getBool() << std::endl;
    }
    void intProperty(Property& _prop) override
    {
        std::cout << getTab() << _prop.getInt() << std::endl;
    }
    void floatProperty(Property& _prop) override
    {
        std::cout << getTab() << _prop.getFloat() << std::endl;
    }
    void stringProperty(Property& _prop) override
    {
        std::cout << getTab() << '"' << _prop.getString() << '"' << std::endl;
    }
    void entityRefProperty(Property& _prop) override
    {
        std::cout << getTab() << '"' << _prop.getEntityRef().entityPath.c_str() << '"' << std::endl;
    }
};

class CompareNode : public RecursiveVisitor
{
    std::vector<Node*> nodes;

public:
    explicit CompareNode(Node* n)
        : nodes({n})
    {
    }
    void inObject([[maybe_unused]] Property& _prop) override
    {
        // ENTLIB_ASSERT(nodes.back()->getFieldNames().size() == expl.get);
    }
    bool inObjectField([[maybe_unused]] Property& _prop, char const* key) override
    {
        nodes.push_back(nodes.back()->at(key));
        ENTLIB_ASSERT(nodes.back() != nullptr);
        return true;
    }
    void outObjectField([[maybe_unused]] Property& _prop, [[maybe_unused]] char const* _key) override
    {
        nodes.pop_back();
    }
    void outObject([[maybe_unused]] Property& _prop) override
    {
    }
    void inUnion([[maybe_unused]] Property& _prop, char const* /*_type*/) override
    {
        //ENTLIB_ASSERT(strcmp(expl.getUnionType(), nodes.back()->getUnionType()) == 0);
        //ENTLIB_ASSERT(strcmp(nodes.back()->getUnionType(), type) == 0);
        nodes.push_back(nodes.back()->getUnionData());
        // expl.getUnionData();
        // std::cout << "expl : UnionData : " << expl.getSchema()->name << std::endl;
        // std::cout << "inUnion : UnionData : " << nodes.back()->getSchema()->name << std::endl;
        //if (expl.getSchema()->name != nodes.back()->getSchema()->name)
        //{
        //    expl.exit();
        //    expl.getUnionData();
        //}
        //expl.exit();
        ENTLIB_ASSERT(nodes.back() != nullptr);
    }
    void outUnion([[maybe_unused]] Property& _prop) override
    {
        nodes.pop_back();
    }
    void inMap(Property& expl) override
    {
        ENTLIB_ASSERT(nodes.back()->size() == expl.size());
        switch (expl.getMapKeyType())
        {
        case DataType::string:
            if (nodes.back()->getKeysString().size() != expl.getMapKeysString().size())
            {
                std::cout << nodes.back()->getKeysString().size() << " "
                          << expl.getMapKeysString().size() << std::endl;
            }
            ENTLIB_ASSERT(nodes.back()->getKeysString().size() == expl.getMapKeysString().size());
            break;
        case DataType::integer:
            ENTLIB_ASSERT(nodes.back()->getKeysInt().size() == expl.getMapKeysInt().size());

            break;
        default: ENTLIB_LOGIC_ERROR("Unexpected key type");
        }
    }
    void outMap([[maybe_unused]] Property& _prop) override
    {
    }
    void inMapElement([[maybe_unused]] Property& _prop, char const* key) override
    {
        nodes.push_back(nodes.back()->mapGet(key));
        ENTLIB_ASSERT(nodes.back() != nullptr);
    }
    void inMapElement([[maybe_unused]] Property& _prop, int64_t key) override
    {
        nodes.push_back(nodes.back()->mapGet(key));
        ENTLIB_ASSERT(nodes.back() != nullptr);
    }
    void outMapElement([[maybe_unused]] Property& _prop) override
    {
        nodes.pop_back();
    }
    void inPrimSet(Property& expl, DataType /*_dataType*/) override
    {
        ENTLIB_ASSERT(nodes.back()->size() == expl.size());
        auto const& itemType = expl.getSchema()->singularItems->get();
        switch (itemType.type)
        {
        case DataType::string:
            ENTLIB_ASSERT(nodes.back()->getKeysString().size() == expl.getPrimSetKeysString().size());
            break;
        case DataType::integer:
            ENTLIB_ASSERT(nodes.back()->getKeysInt().size() == expl.getPrimSetKeysInt().size());
            break;
        default: ENTLIB_LOGIC_ERROR("Unexpected key type");
        }
    }
    void inArrayElement([[maybe_unused]] Property& _prop, size_t i) override
    {
        nodes.push_back(nodes.back()->at(i));
        ENTLIB_ASSERT(nodes.back() != nullptr);
    }
    void outArrayElement([[maybe_unused]] Property& _prop) override
    {
        nodes.pop_back();
    }
    void key([[maybe_unused]] Property& _prop, char const* key) override
    {
        ENTLIB_ASSERT(nodes.back()->mapGet(key) != nullptr);
    }
    void key([[maybe_unused]] Property& _prop, int64_t key) override
    {
        ENTLIB_ASSERT(nodes.back()->mapGet(key) != nullptr);
    }
    void outPrimSet([[maybe_unused]] Property& _prop) override
    {
    }
    void inUnionSet(Property& expl) override
    {
        auto const a = nodes.back()->getKeysString();
        auto const b = expl.getUnionSetKeysString();
        ENTLIB_ASSERT(a.size() == b.size());
        ENTLIB_ASSERT(nodes.back()->size() == expl.size());
        ENTLIB_ASSERT(nodes.back()->getSchema() == expl.getSchema());
    }
    void inUnionSetElement([[maybe_unused]] Property& _prop, char const* type) override
    {
        auto* const union_ = nodes.back()->mapGet(type);
        ENTLIB_ASSERT(union_ != nullptr);
        nodes.push_back(union_->getUnionData());
        ENTLIB_ASSERT(nodes.back() != nullptr);
    }
    void outUnionSetElement([[maybe_unused]] Property& _prop) override
    {
        nodes.pop_back();
    }
    void outUnionSet([[maybe_unused]] Property& _prop) override
    {
    }
    void inObjectSet(Property& expl) override
    {
        ENTLIB_ASSERT(nodes.back()->size() == expl.size());
        switch (nodes.back()->getKeyType())
        {
        case DataType::string:
            ENTLIB_ASSERT(
                nodes.back()->getKeysString().size() == expl.getObjectSetKeysString().size());
            break;
        case DataType::integer:
            ENTLIB_ASSERT(nodes.back()->getKeysInt().size() == expl.getObjectSetKeysInt().size());

            break;
        default: ENTLIB_LOGIC_ERROR("Unexpected key type");
        }
    }
    void outObjectSet([[maybe_unused]] Property& _prop) override
    {
    }
    void inObjectSetElement([[maybe_unused]] Property& _prop, char const* key) override
    {
        nodes.push_back(nodes.back()->mapGet(key));
        ENTLIB_ASSERT(nodes.back() != nullptr);
    }
    void inObjectSetElement([[maybe_unused]] Property& _prop, int64_t key) override
    {
        nodes.push_back(nodes.back()->mapGet(key));
        ENTLIB_ASSERT(nodes.back() != nullptr);
    }
    void outObjectSetElement([[maybe_unused]] Property& _prop) override
    {
        nodes.pop_back();
    }
    void inArray(Property& expl) override
    {
        ENTLIB_ASSERT(nodes.back()->size() == expl.size());
        if (nodes.back()->size() != expl.size())
        {
            [[maybe_unused]] auto size = expl.size();
        }
        ENTLIB_ASSERT(nodes.back()->size() == expl.size());
    }
    void outArray([[maybe_unused]] Property& _prop) override
    {
    }
    void nullProperty([[maybe_unused]] Property& _prop) override
    {
    }
    void boolProperty(Property& expl) override
    {
        // std::cout << elt.getBool() << " " << nodes.back()->getBool() << std::endl;
        ENTLIB_ASSERT(expl.getBool() == nodes.back()->getBool());
    }
    void intProperty(Property& expl) override
    {
        if (expl.getInt() != nodes.back()->getInt())
        {
            std::cout << expl.getInt() << " " << nodes.back()->getInt() << std::endl;
            [[maybe_unused]] auto val = expl.getInt();
        }
        ENTLIB_ASSERT(expl.getInt() == nodes.back()->getInt());
    }
    void floatProperty(Property& expl) override
    {
        // std::cout << elt.getFloat() << " " << nodes.back().getFloat() << std::endl;
        if (fabs(expl.getFloat() - nodes.back()->getFloat()) >= FLT_EPSILON)
        {
            [[maybe_unused]] auto val = expl.getFloat();
        }
        // ENTLIB_ASSERT(fabs(elt.getFloat() - nodes.back().getFloat()) < FLT_EPSILON);
    }
    void stringProperty(Property& expl) override
    {
        if (strcmp(expl.getString(), nodes.back()->getString()) != 0)
        {
            std::cout << expl.getString() << " " << nodes.back()->getString() << std::endl;
            [[maybe_unused]] auto const* val = expl.getString();
        }
        ENTLIB_ASSERT(strcmp(expl.getString(), nodes.back()->getString()) == 0);
    }
    void entityRefProperty(Property& expl) override
    {
        //std::cout << elt.getEntityRef().entityPath.c_str() << " "
        //          << nodes.back()->getEntityRef().entityPath.c_str() << std::endl;
        ENTLIB_ASSERT(expl.getEntityRef() == nodes.back()->getEntityRef());
    }
};

class CompareCursor : public RecursiveVisitor
{
    Property expl2;

    void push(Property _prop)
    {
        expl2 = std::move(_prop);
    }
    void pop()
    {
        expl2 = expl2.getParent();
    }

public:
    explicit CompareCursor(Property _expl2)
        : expl2(std::move(_expl2))
    {
    }
    void inObject(Property& _prop) override
    {
        if (_prop.hasPrefab())
        {
            ENTLIB_ASSERT(expl2.hasPrefab());
            ENTLIB_ASSERT(_prop.getPrefab().getRawJson() == expl2.getPrefab().getRawJson());
        }
        auto const* const a = _prop.getInstanceOf();
        auto const* const b = expl2.getInstanceOf();
        ENTLIB_ASSERT(
            (a == nullptr and b == nullptr)
            or (a != nullptr and b != nullptr and a == std::string_view(b)));
    }
    bool inObjectField(Property& _prop, char const* key) override
    {
        expl2 = expl2.getObjectField(key);
        if (_prop.hasPrefab())
        {
            ENTLIB_ASSERT(expl2.hasPrefab());
            ENTLIB_ASSERT(_prop.getPrefab().getRawJson() == expl2.getPrefab().getRawJson());
        }
        return true;
    }
    void outObjectField([[maybe_unused]] Property& _prop, [[maybe_unused]] char const* _key) override
    {
        pop();
    }
    void inUnion([[maybe_unused]] Property& _prop, char const* _type) override
    {
        expl2 = expl2.getUnionData(_type);
    }
    void outUnion([[maybe_unused]] Property& _prop) override
    {
        pop();
    }
    void inMap(Property& _prop) override
    {
        ENTLIB_ASSERT(expl2.size() == _prop.size());
        switch (_prop.getMapKeyType())
        {
        case DataType::string:
            ENTLIB_ASSERT(expl2.getMapKeysString().size() == _prop.getMapKeysString().size());
            break;
        case DataType::integer:
            ENTLIB_ASSERT(expl2.getMapKeysInt().size() == _prop.getMapKeysInt().size());
            break;
        default: ENTLIB_LOGIC_ERROR("Unexpected key type");
        }
    }
    void inMapElement([[maybe_unused]] Property& _prop, char const* _key) override
    {
        expl2 = expl2.getMapItem(_key);
    }
    void inMapElement([[maybe_unused]] Property& _prop, int64_t _key) override
    {
        expl2 = expl2.getMapItem(_key);
    }
    void outMapElement([[maybe_unused]] Property& _prop) override
    {
        pop();
    }
    void inPrimSet(Property& _prop, DataType /*_dataType*/) override
    {
        ENTLIB_ASSERT(expl2.size() == _prop.size());
        auto const& itemType = _prop.getSchema()->singularItems->get();
        switch (itemType.type)
        {
        case DataType::string:
            ENTLIB_ASSERT(expl2.getPrimSetKeysString() == _prop.getPrimSetKeysString());
            break;
        case DataType::integer:
            ENTLIB_ASSERT(expl2.getPrimSetKeysInt() == _prop.getPrimSetKeysInt());
            break;
        default: ENTLIB_LOGIC_ERROR("Unexpected key type");
        }
    }
    void inArrayElement([[maybe_unused]] Property& _prop, size_t i) override
    {
        expl2 = expl2.getArrayItem(i);
    }
    void outArrayElement([[maybe_unused]] Property& _prop) override
    {
        pop();
    }
    void inUnionSet(Property& _prop) override
    {
        if (_prop.hasPrefab())
        {
            ENTLIB_ASSERT(expl2.hasPrefab());
            ENTLIB_ASSERT(_prop.getPrefab().getRawJson() == expl2.getPrefab().getRawJson());
        }
        auto a = expl2.getUnionSetKeysString();
        auto const b = _prop.getUnionSetKeysString();
        ENTLIB_ASSERT(a.size() == b.size());
        ENTLIB_ASSERT(expl2.getSchema() == _prop.getSchema());
        for (auto [name, type] : a)
        {
            ENTLIB_ASSERT(b.at(name) == type);
        }
    }
    void inUnionSetElement([[maybe_unused]] Property& _prop, char const* _type) override
    {
        expl2 = expl2.getUnionSetItem(_type);
    }
    void outUnionSetElement([[maybe_unused]] Property& _prop) override
    {
        pop();
    }
    void inObjectSet(Property& _prop) override
    {
        if (_prop.hasPrefab())
        {
            ENTLIB_ASSERT(expl2.hasPrefab());
            ENTLIB_ASSERT(_prop.getPrefab().getRawJson() == expl2.getPrefab().getRawJson());
        }
        ENTLIB_ASSERT(expl2.size() == _prop.size());
        switch (expl2.getObjectSetKeyType())
        {
        case DataType::string:
        {
            auto const a = expl2.getObjectSetKeysString();
            auto const b = _prop.getObjectSetKeysString();
            ENTLIB_ASSERT(a.size() == b.size());
            ENTLIB_ASSERT(expl2.getSchema() == _prop.getSchema());
            for (auto const* name : a)
            {
                ENTLIB_ASSERT(b.count(name));
            }
            break;
        }
        case DataType::integer:
            ENTLIB_ASSERT(expl2.getObjectSetKeysInt() == _prop.getObjectSetKeysInt());
            break;
        default: ENTLIB_LOGIC_ERROR("Unexpected key type");
        }
    }
    void inObjectSetElement(Property& _prop, char const* _key) override
    {
        expl2 = expl2.getObjectSetItem(_key);
        if (_prop.hasPrefab())
        {
            ENTLIB_ASSERT(expl2.hasPrefab());
            auto const* const a = _prop.getPrefab().getRawJson();
            auto const* const b = expl2.getPrefab().getRawJson();
            ENTLIB_ASSERT(a == b);
        }
    }
    void inObjectSetElement([[maybe_unused]] Property& _prop, int64_t _key) override
    {
        expl2 = expl2.getObjectSetItem(_key);
    }
    void outObjectSetElement([[maybe_unused]] Property& _prop) override
    {
        pop();
    }
    void inArray(Property& _prop) override
    {
        ENTLIB_ASSERT(expl2.size() == _prop.size());
    }
    void nullProperty([[maybe_unused]] Property& _prop) override
    {
        ENTLIB_ASSERT(expl2.getDataType() == DataType::null);
    }
    void boolProperty([[maybe_unused]] Property& _prop) override
    {
        ENTLIB_ASSERT(_prop.isSet() == expl2.isSet());
        ENTLIB_ASSERT(_prop.getBool() == expl2.getBool());
    }
    void intProperty([[maybe_unused]] Property& _prop) override
    {
        ENTLIB_ASSERT(_prop.isSet() == expl2.isSet());
        ENTLIB_ASSERT(_prop.getInt() == expl2.getInt());
    }
    void floatProperty(Property& _prop) override
    {
        ENTLIB_ASSERT(_prop.isSet() == expl2.isSet());
        if (_prop.getFloat() != expl2.getFloat())
        {
            std::cout << _prop.isSet() << " " << expl2.isSet() << std::endl;
            std::cout << _prop.getFloat() << " " << expl2.getFloat() << std::endl;
            if (_prop.hasPrefab())
            {
                ENTLIB_ASSERT(expl2.hasPrefab());
                ENTLIB_ASSERT(_prop.getPrefab().getRawJson() == expl2.getPrefab().getRawJson());
            }
        }
        ENTLIB_ASSERT(_prop.getFloat() == expl2.getFloat());
    }
    void stringProperty([[maybe_unused]] Property& _prop) override
    {
        ENTLIB_ASSERT(_prop.isSet() == expl2.isSet());
        ENTLIB_ASSERT(_prop.getString() == std::string_view(expl2.getString()));
    }
    void entityRefProperty([[maybe_unused]] Property& _prop) override
    {
        ENTLIB_ASSERT(_prop.isSet() == expl2.isSet());
        ENTLIB_ASSERT(_prop.getEntityRef() == expl2.getEntityRef());
    }
};

class PrimitiveCounterVisitor : public RecursiveVisitor
{
public:
    size_t primitiveCount = 0;

    void key([[maybe_unused]] Property& _prop, char const* /*_key*/) override
    {
        ++primitiveCount;
    }
    void key([[maybe_unused]] Property& _prop, int64_t /*_key*/) override
    {
        ++primitiveCount;
    }
    void nullProperty([[maybe_unused]] Property& _prop) override
    {
        ++primitiveCount;
    }
    void boolProperty([[maybe_unused]] Property& _prop) override
    {
        ++primitiveCount;
    }
    void intProperty([[maybe_unused]] Property& _prop) override
    {
        ++primitiveCount;
    }
    void floatProperty([[maybe_unused]] Property& _prop) override
    {
        ++primitiveCount;
    }
    void stringProperty([[maybe_unused]] Property& _prop) override
    {
        ++primitiveCount;
    }
    void entityRefProperty([[maybe_unused]] Property& _prop) override
    {
        ++primitiveCount;
    }
};

size_t countNodes(Node* node)
{
    size_t nodeCount = 0;
    switch (node->getDataType())
    {
    case DataType::null: ++nodeCount; break;
    case DataType::string: ++nodeCount; break;
    case DataType::number: ++nodeCount; break;
    case DataType::integer: ++nodeCount; break;
    case DataType::object:
        for (auto&& [name, prop] : node->getSchema()->properties)
        {
            nodeCount += countNodes(node->at(name.c_str()));
        }
        break;
    case DataType::array:
    {
        auto meta = std::get<Subschema::ArrayMeta>(node->getSchema()->meta);
        switch (hash(meta.overridePolicy))
        {
        case "map"_hash:
            switch (node->getKeyType())
            {
            case DataType::string:
                for (auto&& key : node->getKeysString())
                {
                    nodeCount += countNodes(node->mapGet(key.c_str()));
                }
                break;
            case DataType::integer:
                for (int64_t const key : node->getKeysInt())
                {
                    nodeCount += countNodes(node->mapGet(key));
                }
                break;
            default: ENTLIB_LOGIC_ERROR("Unexpected key type");
            }
            break;
        case "set"_hash:
        {
            auto& itemType = node->getSchema()->singularItems->get();
            switch (itemType.type)
            {
            case DataType::integer:
                for (int64_t const key : node->getKeysInt())
                {
                    nodeCount += countNodes(node->mapGet(key));
                }
                break;
            case DataType::string:
                for (auto&& key : node->getKeysString())
                {
                    nodeCount += countNodes(node->mapGet(key.c_str()));
                }
                break;
            case DataType::oneOf:
                for (auto&& type : node->getKeysString())
                {
                    nodeCount += countNodes(node->mapGet(type.c_str())->getUnionData());
                }
                break;
            case DataType::object:
                auto const& keyFieldSchema = itemType.properties.at(*meta.keyField).get();
                switch (keyFieldSchema.type)
                {
                case DataType::string:
                    for (auto&& key : node->getKeysString())
                    {
                        nodeCount += countNodes(node->mapGet(key.c_str()));
                    }
                    break;
                case DataType::integer:
                    for (auto&& key : node->getKeysInt())
                    {
                        nodeCount += countNodes(node->mapGet(key));
                    }
                    break;
                default: ENTLIB_LOGIC_ERROR("Unexpected key type");
                }
                break;
            }
        }
        break;
        case ""_hash:
            auto const size = node->size();
            for (size_t i = 0; i < size; ++i)
            {
                nodeCount += countNodes(node->at(i));
            }
            break;
        }
    }
    break;
    case DataType::boolean: ++nodeCount; break;
    case DataType::entityRef: ++nodeCount; break;
    case DataType::oneOf: nodeCount += countNodes(node->getUnionData()); break;
    case DataType::COUNT:
    default: ENTLIB_LOGIC_ERROR("Unexpected datatype");
    }
    return nodeCount;
}

void testCursor(EntityLib& entlib)
{
    {
        auto storage = nlohmann::json::object();
        Property entity(&entlib, entlib.getEntitySchema(), nullptr, &storage);
        auto name = entity.getObjectField("Name");
        name.setString("Debug Quick Creatures Switch");
    }
    {
        std::ifstream ifstr("test.SeedPatch.node");
        std::string filedata;
        std::getline(ifstr, filedata, static_cast<char>(0));
        auto& d = entlib.readJsonFile("test.SeedPatch.node");
        auto const& schema = d["$schema"].get_ref<nlohmann::json::string_t const&>();
        auto typeName = std::string(getRefTypeName(schema.c_str()));
        Property simpleObject(&entlib, entlib.getSchema(typeName.c_str()), "test.SeedPatch.node", &d);
        ENTLIB_ASSERT(simpleObject.getObjectField("NoiseSizeX").getFloat() == 1.f);
        ENTLIB_ASSERT(simpleObject.getObjectField("NoiseSizeY").getFloat() == 2.f);
    }
    {
        std::ifstream ifstr("test.SeedPatch.node");
        std::string filedata;
        std::getline(ifstr, filedata, static_cast<char>(0));
        auto& d = entlib.readJsonFile("test.SeedPatch.node");
        auto typeName =
            std::string(getRefTypeName(d["$schema"].get_ref<std::string const&>().c_str()));
        Property simpleObject(&entlib, entlib.getSchema(typeName.c_str()), "test.SeedPatch.node", &d);
        ENTLIB_ASSERT(simpleObject.getObjectField("NoiseSizeX").getFloat() == 1.f);
        simpleObject.getObjectField("NoiseSizeX").setFloat(2.);
        ENTLIB_ASSERT(simpleObject.getObjectField("NoiseSizeX").getFloat() == 2.);
        ENTLIB_ASSERT(simpleObject.getObjectField("NoiseSizeY").getFloat() == 2.f);
    }
    {
        Property expl(&entlib, entlib.getSchema(entitySchemaName), "prefab.entity");
        ENTLIB_ASSERT(expl.getObjectField("Name").getString() == std::string("PlayerSpawner_"));
        {
            ENTLIB_ASSERT(
                expl.getObjectField("Components")
                    .getUnionSetItem("NetworkNode")
                    .getObjectField("Type")
                    .getString()
                == std::string("Spawner"));
        }
        auto posX = expl.getObjectField("Components")
                        .getUnionSetItem("TransformGD")
                        .getObjectField("Position")
                        .getArrayItem(0llu);
        std::cout << posX.getFloat() << std::endl;
        ENTLIB_ASSERT(posX.getFloat() == 105.2244);
        auto& entityRung = expl;
        auto floatA = entityRung.getObjectField("Components")
                          .getUnionSetItem("TransformGD")
                          .getObjectField("Position")
                          .getArrayItem(0llu)
                          .getFloat();
        auto floatB = entityRung.getObjectField("Components")
                          .getUnionSetItem("TransformGD")
                          .getObjectField("Position")
                          .getArrayItem(0llu)
                          .getFloat();
        ENTLIB_ASSERT(floatA == 105.2244);
        ENTLIB_ASSERT(floatB == 105.2244);

        ENTLIB_ASSERT(
            expl.getObjectField("Components")
                .getUnionSetItem("SubScene")
                .getObjectField("Embedded")
                .getObjectSetItem("EP1-Spout_LINK_001")
                .getObjectField("Name")
                .getString()
            == std::string("EP1-Spout_LINK_001"));
    }
    {
        Property expl(&entlib, entlib.getSchema(entitySchemaName), "instance.entity");
        ENTLIB_ASSERT(expl.getObjectField("Name").getString() == std::string("PlayerSpawner_"));
        auto type =
            expl.getObjectField("Components").getUnionSetItem("NetworkNode").getObjectField("Type");
        std::cout << type.getString() << std::endl;
        ENTLIB_ASSERT(
            expl.getObjectField("Components").getUnionSetItem("NetworkNode").getObjectField("Type").getString()
            == std::string("Spawner"));
        std::cout << expl.getObjectField("Components")
                         .getUnionSetItem("TransformGD")
                         .getObjectField("Matrix")
                         .getArrayItem(3llu)
                         .getFloat()
                  << std::endl;
        auto pos2 = expl.getObjectField("Components")
                        .getUnionSetItem("TransformGD")
                        .getObjectField("Position")
                        .getArrayItem(2llu)
                        .getFloat();
        ENTLIB_ASSERT(fabs(pos2 - 29.6635) < FLT_EPSILON);
        ENTLIB_ASSERT(
            expl.getObjectField("Components")
                .getUnionSetItem("SubScene")
                .getObjectField("Embedded")
                .getObjectSetItem("EP1-Spout_LINK_001")
                .getObjectField("Name")
                .getString()
            == std::string("EP1-Spout_LINK_001"));
        ENTLIB_ASSERT(
            expl.getObjectField("ActorStates")
                .getUnionSetItem("ActorStateHoldingItem")
                .getObjectField("ItemEntityRef")
                .getString()
            == std::string("tutu"));
        auto components = expl.getObjectField("Components");
        auto ori3 =
            components.getUnionSetItem("TransformGD").getObjectField("Orientation").getArrayItem(3llu);
        ENTLIB_ASSERT(fabs(ori3.getFloat() - 0.9916236400604248) < FLT_EPSILON);
        ori3.setFloat(2.);
        ENTLIB_ASSERT(ori3.getFloat() == 2.);
        auto soundAreaGD = expl.getObjectField("Components").getUnionSetItem("SoundAreaGD");
        ENTLIB_ASSERT(soundAreaGD.isSet() == false);
        ENTLIB_ASSERT(soundAreaGD.isDefault() == true);
        auto keys = components.getUnionSetKeysString();
        keys = components.getUnionSetKeysString();
        auto staffVertebrasGD = expl.getObjectField("Components").getUnionSetItem("StaffVertebrasGD");
        ENTLIB_ASSERT(staffVertebrasGD.isSet() == false);
        ENTLIB_ASSERT(staffVertebrasGD.isDefault() == true);
        keys = components.getUnionSetKeysString();

        expl.save("instance.prout.entity");
        // Must not crash
        Property prefab2(&entlib, entlib.getSchema(entitySchemaName), "instance.prout.entity");
        auto comp2 = prefab2.getObjectField("Components");
        auto characterControllerGD = comp2.getUnionSetItem("CharacterControllerGD");
        auto clamberData = characterControllerGD.getObjectField("ClamberData");
        auto vertOriRatio = clamberData.getObjectField("VerticalOrientationRatio");
        auto in = vertOriRatio.getObjectField("in");
        auto in0 = in.getArrayItem(0);
        in0.setFloat(3.33);
    }
    {
        std::cout << "Read instance.entity with LazyLib" << std::endl;
        clock_t start = clock();
        Property expl(&entlib, entlib.getSchema(entitySchemaName), "instance.entity");
        clock_t end = clock();

        auto ent = entlib.loadEntityAsNode(R"(instance.entity)");

        std::cout << static_cast<float>(end - start) / CLOCKS_PER_SEC << std::endl;
        CompareNode compare(ent.get());
        std::cout << "Visit all" << std::endl;
        start = clock();
        visitRecursive(expl, compare);
        end = clock();
        std::cout << static_cast<float>(end - start) / CLOCKS_PER_SEC << std::endl;

        nlohmann::json newDoc = nlohmann::json::object();
        Property destExpl(&entlib, expl.getSchema(), "", &newDoc);
        CopyProperty copier(destExpl, OverrideValueSource::OverrideOrPrefab, true);
        visitRecursive(expl, copier);
        entlib.saveJsonFile(&newDoc, "instance.cursor.entity", "Entity");
    }
    bool testLoading = true;
    if (testLoading)
    {
        entlib.rawdataPath = "X:/RawData";
        std::cout << "Read SceneKOM.scene with LazyLib" << std::endl;
        clock_t start = clock();
        Property expl(
            &entlib,
            entlib.getSchema(entitySchemaName),
            R"(X:\RawData\20_scene\KOM2021\SceneKOM\SceneKOM\editor\SceneKOM.scene)");
        clock_t end = clock();
        std::cout << static_cast<float>(end - start) / CLOCKS_PER_SEC << std::endl;

        bool testCopy = true;
        if (testCopy)
        {
            std::cout << "Copy SceneKOM.scene with LazyLib" << std::endl;
            nlohmann::json newDoc = nlohmann::json::object();
            Property destExpl(&entlib, expl.getSchema(), "", &newDoc);
            CopyProperty copier(destExpl, OverrideValueSource::Override, true);
            visitRecursive(expl, copier);

            std::cout << "Save SceneKOM.scene with LazyLib" << std::endl;
            entlib.saveJsonFile(&newDoc, "SceneKOM.scene", expl.getSchema()->name.c_str());

            std::cout << "CompareCursor SceneKOM.scene wth the clone" << std::endl;
            CompareCursor comparator(destExpl);
            visitRecursive(expl, comparator);
        }

        std::cout << "Read SceneKOM.scene with NodeLib" << std::endl;
        start = clock();
        auto ent = entlib.loadEntityAsNode(
            R"(X:\RawData\20_scene\KOM2021\SceneKOM\SceneKOM\editor\SceneKOM.scene)");
        end = clock();
        std::cout << static_cast<float>(end - start) / CLOCKS_PER_SEC << std::endl;

        std::cout << "Travserse SceneKOM.scene with NodeLib" << std::endl;
        start = clock();
        auto nodeCount = countNodes(ent.get());
        end = clock();
        std::cout << static_cast<float>(end - start) / CLOCKS_PER_SEC << std::endl;
        std::cout << "Primitive count : " << nodeCount << std::endl;

        PrimitiveCounterVisitor visitor;
        std::cout << "Travserse SceneKOM.scene with LazyLib" << std::endl;
        start = clock();
        visitRecursive(expl, visitor);
        end = clock();
        std::cout << static_cast<float>(end - start) / CLOCKS_PER_SEC << std::endl;
        std::cout << "Primitive count : " << visitor.primitiveCount << std::endl;
    }
    bool testCompare = true;
    if (testCompare)
    {
        entlib.rawdataPath = "X:/RawData";
        std::cout << "Read SceneKOM.scene with LazyLib" << std::endl;
        clock_t start = clock();
        Property expl(
            &entlib,
            entlib.getSchema(entitySchemaName),
            R"(X:\RawData\20_scene\KOM2021\SceneKOM\SceneKOM\editor\SceneKOM.scene)");
        clock_t end = clock();
        std::cout << static_cast<float>(end - start) / CLOCKS_PER_SEC << std::endl;

        std::cout << "Read SceneKOM.scene with NodeLib" << std::endl;
        start = clock();
        auto ent = entlib.loadEntityAsNode(
            R"(X:\RawData\20_scene\KOM2021\SceneKOM\SceneKOM\editor\SceneKOM.scene)");
        end = clock();
        std::cout << static_cast<float>(end - start) / CLOCKS_PER_SEC << std::endl;

        std::cout << "Travserse SceneKOM.scene with NodeLib" << std::endl;
        start = clock();
        auto nodeCount = countNodes(ent.get());
        end = clock();
        std::cout << static_cast<float>(end - start) / CLOCKS_PER_SEC << std::endl;
        std::cout << "Primitive count : " << nodeCount << std::endl;

        std::cout << "Compare both" << std::endl;
        start = clock();
        CompareNode comparator(ent.get());
        visitRecursive(expl, comparator);
        end = clock();
        std::cout << static_cast<float>(end - start) / CLOCKS_PER_SEC << std::endl;
    }
}
