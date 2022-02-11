#include "TestCursor.h"
#include <EntityLib.h>
#include <../Tools.h>
#include <fstream>
#include <variant>
#include <iostream>
#include <stack>

#include <EntityLib/Visitor.h>
#include <EntityLib/CopyNode.h>
#include <EntityLib/Cursor.h>

using namespace Ent;

class PrintNode : public RecursiveVisitor
{
    size_t tab = 0;

    std::string getTab() const
    {
        return std::string(tab * 4, ' ');
    }

public:
    PrintNode()
    {
    }

    void inObject([[maybe_unused]] Layer& _expl) override
    {
        ++tab;
    }
    bool inObjectField([[maybe_unused]] Layer& _expl, char const* key) override
    {
        // std::cout << "dksflghjdfjg" << getTab() << '"' << key << "\": " << std::endl;
        std::cout << getTab() << '"' << key << "\": " << std::endl;
        ++tab;
        return true;
    }
    void outObjectField([[maybe_unused]] Layer& _expl, [[maybe_unused]] char const* _key) override
    {
        --tab;
    }
    void outObject([[maybe_unused]] Layer& _expl) override
    {
        --tab;
    }
    void inUnion([[maybe_unused]] Layer& _expl, char const* type) override
    {
        std::cout << getTab() << '"' << type << "\": " << std::endl;
        ++tab;
    }
    void outUnion([[maybe_unused]] Layer& _expl) override
    {
        --tab;
    }
    void inMap([[maybe_unused]] Layer& _expl) override
    {
        ++tab;
    }
    void outMap([[maybe_unused]] Layer& _expl) override
    {
        --tab;
    }
    void inMapElement([[maybe_unused]] Layer& _expl, char const* key) override
    {
        ++tab;
        std::cout << getTab() << '"' << key << "\": " << std::endl;
    }
    void inMapElement([[maybe_unused]] Layer& _expl, int64_t key) override
    {
        ++tab;
        std::cout << getTab() << key << ": " << std::endl;
    }
    void outMapElement([[maybe_unused]] Layer& _expl) override
    {
        --tab;
    }
    void inPrimSet([[maybe_unused]] Layer& _expl, Ent::DataType) override
    {
        ++tab;
    }
    void inArrayElement([[maybe_unused]] Layer& _expl, size_t) override
    {
    }
    void outArrayElement([[maybe_unused]] Layer& _expl) override
    {
    }
    void key([[maybe_unused]] Layer& _expl, char const* _key) override
    {
        std::cout << getTab() << '"' << _key << '"' << std::endl;
    }
    void key([[maybe_unused]] Layer& _expl, int64_t _key) override
    {
        std::cout << getTab() << _key << std::endl;
    }
    void outPrimSet([[maybe_unused]] Layer& _expl) override
    {
        --tab;
    }
    void inUnionSet([[maybe_unused]] Layer& _expl) override
    {
        ++tab;
    }
    void inUnionSetElement([[maybe_unused]] Layer& _expl, char const* key) override
    {
        std::cout << getTab() << '"' << key << '"' << std::endl;
        ++tab;
    }
    void outUnionSetElement([[maybe_unused]] Layer& _expl) override
    {
        --tab;
    }
    void outUnionSet([[maybe_unused]] Layer& _expl) override
    {
        --tab;
    }
    void inObjectSet([[maybe_unused]] Layer& _expl) override
    {
        ++tab;
    }
    void outObjectSet([[maybe_unused]] Layer& _expl) override
    {
        --tab;
    }
    void inObjectSetElement([[maybe_unused]] Layer& _expl, char const* key) override
    {
        std::cout << getTab() << '"' << key << '"' << std::endl;
    }
    void inObjectSetElement([[maybe_unused]] Layer& _expl, int64_t key) override
    {
        std::cout << getTab() << key << std::endl;
    }
    void outObjectSetElement([[maybe_unused]] Layer& _expl) override
    {
    }
    void inArray([[maybe_unused]] Layer& _expl) override
    {
        ++tab;
    }
    void outArray([[maybe_unused]] Layer& _expl) override
    {
        --tab;
    }
    void nullNode([[maybe_unused]] Layer& _expl) override
    {
        std::cout << getTab() << "null" << std ::endl;
    }
    void boolNode([[maybe_unused]] Layer& _expl) override
    {
        std::cout << getTab() << _expl.getBool() << std::endl;
    }
    void intNode([[maybe_unused]] Layer& _expl) override
    {
        std::cout << getTab() << _expl.getInt() << std::endl;
    }
    void floatNode([[maybe_unused]] Layer& _expl) override
    {
        std::cout << getTab() << _expl.getFloat() << std::endl;
    }
    void stringNode([[maybe_unused]] Layer& _expl) override
    {
        std::cout << getTab() << '"' << _expl.getString() << '"' << std::endl;
    }
    void entityRefNode([[maybe_unused]] Layer& _expl) override
    {
        std::cout << getTab() << '"' << _expl.getEntityRef().entityPath.c_str() << '"' << std::endl;
    }
};

class CompareNode : public RecursiveVisitor
{
    std::vector<Node*> nodes;

public:
    CompareNode(Node* n)
        : nodes({n})
    {
    }
    void inObject([[maybe_unused]] Layer& expl) override
    {
        // ENTLIB_ASSERT(nodes.back()->getFieldNames().size() == expl.get);
    }
    bool inObjectField([[maybe_unused]] Layer& expl, char const* key) override
    {
        nodes.push_back(nodes.back()->at(key));
        ENTLIB_ASSERT(nodes.back() != nullptr);
        return true;
    }
    void outObjectField([[maybe_unused]] Layer& expl, [[maybe_unused]] char const* _key) override
    {
        nodes.pop_back();
    }
    void outObject([[maybe_unused]] Layer& expl) override
    {
    }
    void inUnion([[maybe_unused]] Layer& expl, char const*) override
    {
        //ENTLIB_ASSERT(strcmp(expl.getUnionType(), nodes.back()->getUnionType()) == 0);
        //ENTLIB_ASSERT(strcmp(nodes.back()->getUnionType(), type) == 0);
        nodes.push_back(nodes.back()->getUnionData());
        // expl.enterUnionData();
        // std::cout << "expl : UnionData : " << expl.getSchema()->name << std::endl;
        // std::cout << "inUnion : UnionData : " << nodes.back()->getSchema()->name << std::endl;
        //if (expl.getSchema()->name != nodes.back()->getSchema()->name)
        //{
        //    expl.exit();
        //    expl.enterUnionData();
        //}
        //expl.exit();
        ENTLIB_ASSERT(nodes.back() != nullptr);
    }
    void outUnion([[maybe_unused]] Layer& expl) override
    {
        nodes.pop_back();
    }
    void inMap(Layer& expl) override
    {
        ENTLIB_ASSERT(nodes.back()->size() == expl.size());
        switch (expl.getMapKeyType())
        {
        case Ent::DataType::string:
            if (nodes.back()->getKeysString().size() != expl.getMapKeysString().size())
                std::cout << nodes.back()->getKeysString().size() << " "
                          << expl.getMapKeysString().size() << std::endl;
            ENTLIB_ASSERT(nodes.back()->getKeysString().size() == expl.getMapKeysString().size());
            break;
        case Ent::DataType::integer:
            ENTLIB_ASSERT(nodes.back()->getKeysInt().size() == expl.getMapKeysInt().size());

            break;
        default: ENTLIB_LOGIC_ERROR("Unexpected key type");
        }
    }
    void outMap([[maybe_unused]] Layer& expl) override
    {
    }
    void inMapElement([[maybe_unused]] Layer& expl, char const* key) override
    {
        nodes.push_back(nodes.back()->mapGet(key));
        ENTLIB_ASSERT(nodes.back() != nullptr);
    }
    void inMapElement([[maybe_unused]] Layer& expl, int64_t key) override
    {
        nodes.push_back(nodes.back()->mapGet(key));
        ENTLIB_ASSERT(nodes.back() != nullptr);
    }
    void outMapElement([[maybe_unused]] Layer& expl) override
    {
        nodes.pop_back();
    }
    void inPrimSet(Layer& expl, Ent::DataType) override
    {
        ENTLIB_ASSERT(nodes.back()->size() == expl.size());
        auto& itemType = expl.getSchema()->singularItems.get()->get();
        switch (itemType.type)
        {
        case Ent::DataType::string:
            ENTLIB_ASSERT(nodes.back()->getKeysString().size() == expl.getPrimSetKeysString().size());
            break;
        case Ent::DataType::integer:
            ENTLIB_ASSERT(nodes.back()->getKeysInt().size() == expl.getPrimSetKeysInt().size());
            break;
        default: ENTLIB_LOGIC_ERROR("Unexpected key type");
        }
    }
    void inArrayElement([[maybe_unused]] Layer& expl, size_t i) override
    {
        nodes.push_back(nodes.back()->at(i));
        ENTLIB_ASSERT(nodes.back() != nullptr);
    }
    void outArrayElement([[maybe_unused]] Layer& expl) override
    {
        nodes.pop_back();
    }
    void key([[maybe_unused]] Layer& expl, char const* key) override
    {
        ENTLIB_ASSERT(nodes.back()->mapGet(key) != nullptr);
    }
    void key([[maybe_unused]] Layer& expl, int64_t key) override
    {
        ENTLIB_ASSERT(nodes.back()->mapGet(key) != nullptr);
    }
    void outPrimSet([[maybe_unused]] Layer& expl) override
    {
    }
    void inUnionSet(Layer& expl) override
    {
        auto a = nodes.back()->getKeysString();
        auto b = expl.getUnionSetKeysString();
        ENTLIB_ASSERT(a.size() == b.size());
        ENTLIB_ASSERT(nodes.back()->size() == expl.size());
        ENTLIB_ASSERT(nodes.back()->getSchema() == expl.getSchema());
    }
    void inUnionSetElement([[maybe_unused]] Layer& expl, char const* type) override
    {
        auto union_ = nodes.back()->mapGet(type);
        ENTLIB_ASSERT(union_ != nullptr);
        nodes.push_back(union_->getUnionData());
        ENTLIB_ASSERT(nodes.back() != nullptr);
    }
    void outUnionSetElement([[maybe_unused]] Layer& expl) override
    {
        nodes.pop_back();
    }
    void outUnionSet([[maybe_unused]] Layer& expl) override
    {
    }
    void inObjectSet(Layer& expl) override
    {
        ENTLIB_ASSERT(nodes.back()->size() == expl.size());
        switch (nodes.back()->getKeyType())
        {
        case Ent::DataType::string:
            ENTLIB_ASSERT(
                nodes.back()->getKeysString().size() == expl.getObjectSetKeysString().size());
            break;
        case Ent::DataType::integer:
            ENTLIB_ASSERT(nodes.back()->getKeysInt().size() == expl.getObjectSetKeysInt().size());

            break;
        default: ENTLIB_LOGIC_ERROR("Unexpected key type");
        }
    }
    void outObjectSet([[maybe_unused]] Layer& expl) override
    {
    }
    void inObjectSetElement([[maybe_unused]] Layer& expl, char const* key) override
    {
        nodes.push_back(nodes.back()->mapGet(key));
        ENTLIB_ASSERT(nodes.back() != nullptr);
    }
    void inObjectSetElement([[maybe_unused]] Layer& expl, int64_t key) override
    {
        nodes.push_back(nodes.back()->mapGet(key));
        ENTLIB_ASSERT(nodes.back() != nullptr);
    }
    void outObjectSetElement([[maybe_unused]] Layer& expl) override
    {
        nodes.pop_back();
    }
    void inArray(Layer& expl) override
    {
        ENTLIB_ASSERT(nodes.back()->size() == expl.size());
        if (nodes.back()->size() != expl.size())
        {
            expl.size();
        }
        ENTLIB_ASSERT(nodes.back()->size() == expl.size());
    }
    void outArray([[maybe_unused]] Layer& expl) override
    {
    }
    void nullNode([[maybe_unused]] Layer& expl) override
    {
    }
    void boolNode(Layer& expl) override
    {
        // std::cout << elt.getBool() << " " << nodes.back()->getBool() << std::endl;
        ENTLIB_ASSERT(expl.getBool() == nodes.back()->getBool());
    }
    void intNode(Layer& expl) override
    {
        // std::cout << elt.getInt() << " " << nodes.back()->getInt() << std::endl;
        if (expl.getInt() != nodes.back()->getInt())
        {
            expl.getInt();
        }
        ENTLIB_ASSERT(expl.getInt() == nodes.back()->getInt());
    }
    void floatNode(Layer& expl) override
    {
        // std::cout << elt.getFloat() << " " << nodes.back()->getFloat() << std::endl;
        if (fabs(expl.getFloat() - nodes.back()->getFloat()) >= FLT_EPSILON)
        {
            expl.getFloat();
        }
        // ENTLIB_ASSERT(fabs(elt.getFloat() - nodes.back()->getFloat()) < FLT_EPSILON);
    }
    void stringNode(Layer& expl) override
    {
        if (strcmp(expl.getString(), nodes.back()->getString()) != 0)
        {
            std::cout << expl.getString() << " " << nodes.back()->getString() << std::endl;
            expl.getString();
        }
        ENTLIB_ASSERT(strcmp(expl.getString(), nodes.back()->getString()) == 0);
    }
    void entityRefNode(Layer& expl) override
    {
        //std::cout << elt.getEntityRef().entityPath.c_str() << " "
        //          << nodes.back()->getEntityRef().entityPath.c_str() << std::endl;
        ENTLIB_ASSERT(expl.getEntityRef() == nodes.back()->getEntityRef());
    }
};

class CompareCursor : public RecursiveVisitor
{
    std::vector<Layer> expl2;

public:
    CompareCursor(Layer _expl2)
        : expl2({std::move(_expl2)})
    {
    }
    void inObject([[maybe_unused]] Layer& expl) override
    {
        if (expl.getPrefab())
        {
            ENTLIB_ASSERT(expl2.back().getPrefab());
            ENTLIB_ASSERT(expl.getPrefab()->_getRawJson() == expl2.back().getPrefab()->_getRawJson());
        }
        auto a = expl.getInstanceOf();
        auto b = expl2.back().getInstanceOf();
        ENTLIB_ASSERT(
            (a == nullptr and b == nullptr)
            or (a != nullptr and b != nullptr and a == std::string_view(b)));
    }
    bool inObjectField([[maybe_unused]] Layer& expl, char const* key) override
    {
        expl2.push_back(expl2.back().enterObjectField(key));
        if (expl.getPrefab())
        {
            ENTLIB_ASSERT(expl2.back().getPrefab());
            ENTLIB_ASSERT(expl.getPrefab()->_getRawJson() == expl2.back().getPrefab()->_getRawJson());
        }
        return true;
    }
    void outObjectField([[maybe_unused]] Layer& expl, [[maybe_unused]] char const* _key) override
    {
        expl2.pop_back();
    }
    void inUnion([[maybe_unused]] Layer& expl, char const* _type) override
    {
        expl2.push_back(expl2.back().enterUnionData(_type));
    }
    void outUnion([[maybe_unused]] Layer& expl) override
    {
        expl2.pop_back();
    }
    void inMap([[maybe_unused]] Layer& expl) override
    {
        ENTLIB_ASSERT(expl2.back().size() == expl.size());
        switch (expl.getMapKeyType())
        {
        case Ent::DataType::string:
            ENTLIB_ASSERT(expl2.back().getMapKeysString().size() == expl.getMapKeysString().size());
            break;
        case Ent::DataType::integer:
            ENTLIB_ASSERT(expl2.back().getMapKeysInt().size() == expl.getMapKeysInt().size());
            break;
        default: ENTLIB_LOGIC_ERROR("Unexpected key type");
        }
    }
    void inMapElement([[maybe_unused]] Layer& expl, char const* _key) override
    {
        expl2.push_back(expl2.back().enterMapItem(_key));
    }
    void inMapElement([[maybe_unused]] Layer& expl, int64_t _key) override
    {
        expl2.push_back(expl2.back().enterMapItem(_key));
    }
    void outMapElement([[maybe_unused]] Layer& expl) override
    {
        expl2.pop_back();
    }
    void inPrimSet([[maybe_unused]] Layer& expl, Ent::DataType) override
    {
        ENTLIB_ASSERT(expl2.back().size() == expl.size());
        auto& itemType = expl.getSchema()->singularItems.get()->get();
        switch (itemType.type)
        {
        case Ent::DataType::string:
            ENTLIB_ASSERT(expl2.back().getPrimSetKeysString() == expl.getPrimSetKeysString());
            break;
        case Ent::DataType::integer:
            ENTLIB_ASSERT(expl2.back().getPrimSetKeysInt() == expl.getPrimSetKeysInt());
            break;
        default: ENTLIB_LOGIC_ERROR("Unexpected key type");
        }
    }
    void inArrayElement([[maybe_unused]] Layer& expl, size_t i) override
    {
        expl2.push_back(expl2.back().enterArrayItem(i));
    }
    void outArrayElement([[maybe_unused]] Layer& expl) override
    {
        expl2.pop_back();
    }
    void inUnionSet([[maybe_unused]] Layer& expl) override
    {
        if (expl.getPrefab())
        {
            ENTLIB_ASSERT(expl2.back().getPrefab());
            ENTLIB_ASSERT(expl.getPrefab()->_getRawJson() == expl2.back().getPrefab()->_getRawJson());
        }
        auto a = expl2.back().getUnionSetKeysString();
        auto b = expl.getUnionSetKeysString();
        ENTLIB_ASSERT(a.size() == b.size());
        ENTLIB_ASSERT(expl2.back().getSchema() == expl.getSchema());
        for (auto [name, type] : a)
        {
            ENTLIB_ASSERT(b.at(name) == type);
        }
    }
    void inUnionSetElement([[maybe_unused]] Layer& expl, char const* _type) override
    {
        expl2.push_back(expl2.back().enterUnionSetItem(_type));
    }
    void outUnionSetElement([[maybe_unused]] Layer& expl) override
    {
        expl2.pop_back();
    }
    void inObjectSet([[maybe_unused]] Layer& expl) override
    {
        if (expl.getPrefab())
        {
            ENTLIB_ASSERT(expl2.back().getPrefab());
            ENTLIB_ASSERT(expl.getPrefab()->_getRawJson() == expl2.back().getPrefab()->_getRawJson());
        }
        ENTLIB_ASSERT(expl2.back().size() == expl.size());
        switch (expl2.back().getObjectSetKeyType())
        {
        case Ent::DataType::string:
        {
            auto a = expl2.back().getObjectSetKeysString();
            auto b = expl.getObjectSetKeysString();
            ENTLIB_ASSERT(a.size() == b.size());
            ENTLIB_ASSERT(expl2.back().getSchema() == expl.getSchema());
            for (auto name : a)
            {
                ENTLIB_ASSERT(b.count(name));
            }
            break;
        }
        case Ent::DataType::integer:
            ENTLIB_ASSERT(expl2.back().getObjectSetKeysInt() == expl.getObjectSetKeysInt());
            break;
        default: ENTLIB_LOGIC_ERROR("Unexpected key type");
        }
    }
    void inObjectSetElement([[maybe_unused]] Layer& expl, char const* _key) override
    {
        expl2.push_back(expl2.back().enterObjectSetItem(_key));
        if (expl.getPrefab())
        {
            ENTLIB_ASSERT(expl2.back().getPrefab());
            auto a = expl.getPrefab()->_getRawJson();
            auto b = expl2.back().getPrefab()->_getRawJson();
            ENTLIB_ASSERT(a == b);
        }
    }
    void inObjectSetElement([[maybe_unused]] Layer& expl, int64_t _key) override
    {
        expl2.push_back(expl2.back().enterObjectSetItem(_key));
    }
    void outObjectSetElement([[maybe_unused]] Layer& expl) override
    {
        expl2.pop_back();
    }
    void inArray([[maybe_unused]] Layer& expl) override
    {
        ENTLIB_ASSERT(expl2.back().size() == expl.size());
    }
    void nullNode([[maybe_unused]] Layer& expl) override
    {
        ENTLIB_ASSERT(expl2.back().getDataType() == Ent::DataType::null);
    }
    void boolNode([[maybe_unused]] Layer& expl) override
    {
        ENTLIB_ASSERT(expl.isSet() == expl2.back().isSet());
        ENTLIB_ASSERT(expl.getBool() == expl2.back().getBool());
    }
    void intNode([[maybe_unused]] Layer& expl) override
    {
        ENTLIB_ASSERT(expl.isSet() == expl2.back().isSet());
        ENTLIB_ASSERT(expl.getInt() == expl2.back().getInt());
    }
    void floatNode([[maybe_unused]] Layer& expl) override
    {
        ENTLIB_ASSERT(expl.isSet() == expl2.back().isSet());
        if (expl.getFloat() != expl2.back().getFloat())
        {
            std::cout << expl.isSet() << " " << expl2.back().isSet() << std::endl;
            std::cout << expl.getFloat() << " " << expl2.back().getFloat() << std::endl;
            if (expl.getPrefab())
            {
                ENTLIB_ASSERT(expl2.back().getPrefab());
                ENTLIB_ASSERT(
                    expl.getPrefab()->_getRawJson() == expl2.back().getPrefab()->_getRawJson());
            }
        }
        ENTLIB_ASSERT(expl.getFloat() == expl2.back().getFloat());
    }
    void stringNode([[maybe_unused]] Layer& expl) override
    {
        ENTLIB_ASSERT(expl.isSet() == expl2.back().isSet());
        ENTLIB_ASSERT(expl.getString() == std::string_view(expl2.back().getString()));
    }
    void entityRefNode([[maybe_unused]] Layer& expl) override
    {
        ENTLIB_ASSERT(expl.isSet() == expl2.back().isSet());
        ENTLIB_ASSERT(expl.getEntityRef() == expl2.back().getEntityRef());
    }
};

class PrimitiveCounterVisitor : public RecursiveVisitor
{
public:
    size_t primitiveCount = 0;

    void key([[maybe_unused]] Layer& _expl, char const*) override
    {
        ++primitiveCount;
    }
    void key([[maybe_unused]] Layer& _expl, int64_t) override
    {
        ++primitiveCount;
    }
    void nullNode([[maybe_unused]] Layer& _expl) override
    {
        ++primitiveCount;
    }
    void boolNode([[maybe_unused]] Layer& _expl) override
    {
        ++primitiveCount;
    }
    void intNode([[maybe_unused]] Layer& _expl) override
    {
        ++primitiveCount;
    }
    void floatNode([[maybe_unused]] Layer& _expl) override
    {
        ++primitiveCount;
    }
    void stringNode([[maybe_unused]] Layer& _expl) override
    {
        ++primitiveCount;
    }
    void entityRefNode([[maybe_unused]] Layer& _expl) override
    {
        ++primitiveCount;
    }
};

size_t countNodes(Node* node)
{
    size_t nodeCount = 0;
    switch (node->getDataType())
    {
    case Ent::DataType::null: ++nodeCount; break;
    case Ent::DataType::string: ++nodeCount; break;
    case Ent::DataType::number: ++nodeCount; break;
    case Ent::DataType::integer: ++nodeCount; break;
    case Ent::DataType::object:
        for (auto&& [name, prop] : node->getSchema()->properties)
        {
            nodeCount += countNodes(node->at(name.c_str()));
        }
        break;
    case Ent::DataType::array:
    {
        auto meta = std::get<Ent::Subschema::ArrayMeta>(node->getSchema()->meta);
        switch (hash(meta.overridePolicy))
        {
        case "map"_hash:
            switch (node->getKeyType())
            {
            case Ent::DataType::string:
                for (auto&& key : node->getKeysString())
                {
                    nodeCount += countNodes(node->mapGet(key.c_str()));
                }
                break;
            case Ent::DataType::integer:
                for (int64_t key : node->getKeysInt())
                {
                    nodeCount += countNodes(node->mapGet(key));
                }
                break;
            default: ENTLIB_LOGIC_ERROR("Unexpected key type");
            }
            break;
        case "set"_hash:
        {
            auto& itemType = node->getSchema()->singularItems.get()->get();
            switch (itemType.type)
            {
            case Ent::DataType::integer:
                for (int64_t key : node->getKeysInt())
                {
                    nodeCount += countNodes(node->mapGet(key));
                }
                break;
            case Ent::DataType::string:
                for (auto&& key : node->getKeysString())
                {
                    nodeCount += countNodes(node->mapGet(key.c_str()));
                }
                break;
            case Ent::DataType::oneOf:
                for (auto&& type : node->getKeysString())
                {
                    nodeCount += countNodes(node->mapGet(type.c_str())->getUnionData());
                }
                break;
            case Ent::DataType::object:
                auto& keyFieldSchema = itemType.properties.at(*meta.keyField).get();
                switch (keyFieldSchema.type)
                {
                case Ent::DataType::string:
                    for (auto&& key : node->getKeysString())
                    {
                        nodeCount += countNodes(node->mapGet(key.c_str()));
                    }
                    break;
                case Ent::DataType::integer:
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
    case Ent::DataType::boolean: ++nodeCount; break;
    case Ent::DataType::entityRef: ++nodeCount; break;
    case Ent::DataType::oneOf: nodeCount += countNodes(node->getUnionData()); break;
    case Ent::DataType::COUNT:
    default: ENTLIB_LOGIC_ERROR("Unexpected datatype");
    }
    return nodeCount;
}

void testCursor(Ent::EntityLib& entlib)
{
    {
        auto storage = nlohmann::json::object();
        Layer entity(
            &entlib, nullptr, entlib.getEntitySchema(), nullptr, &storage);
        auto name = entity.enterObjectField("Name");
        name.setString("Debug Quick Creatures Switch");
    }
    {
        std::ifstream ifstr("test.SeedPatch.node");
        std::string filedata;
        std::getline(ifstr, filedata, char(0));
        auto& d = entlib.readJsonFile("test.SeedPatch.node");
        auto& schema = d["$schema"].get_ref<nlohmann::json::string_t const&>();
        auto typeName = getRefTypeName(schema.c_str());
        Layer simpleObject(&entlib, nullptr, entlib.getSchema(typeName), "test.SeedPatch.node", &d);
        ENTLIB_ASSERT(simpleObject.enterObjectField("NoiseSizeX").getFloat() == 1.f);
        ENTLIB_ASSERT(simpleObject.enterObjectField("NoiseSizeY").getFloat() == 2.f);
    }
    {
        std::ifstream ifstr("test.SeedPatch.node");
        std::string filedata;
        std::getline(ifstr, filedata, char(0));
        auto& d = entlib.readJsonFile("test.SeedPatch.node");
        Layer simpleObject(
            &entlib,
            nullptr,
            entlib.getSchema(getRefTypeName(d["$schema"].get_ref<std::string const&>().c_str())),
            "test.SeedPatch.node",
            &d);
        ENTLIB_ASSERT(simpleObject.enterObjectField("NoiseSizeX").getFloat() == 1.f);
        simpleObject.enterObjectField("NoiseSizeX").setFloat(2.);
        ENTLIB_ASSERT(simpleObject.enterObjectField("NoiseSizeX").getFloat() == 2.);
        ENTLIB_ASSERT(simpleObject.enterObjectField("NoiseSizeY").getFloat() == 2.f);
    }
    {
        Layer expl(&entlib, nullptr, entlib.getSchema(entitySchemaName), "prefab.entity");
        ENTLIB_ASSERT(expl.enterObjectField("Name").getString()
            == std::string("PlayerSpawner_"));
        {
            ENTLIB_ASSERT(
                expl.enterObjectField("Components")
                    .enterUnionSetItem("NetworkNode")
                    .enterObjectField("Type")
                    .getString()
                == std::string("Spawner"));
        }
        auto posX = expl.enterObjectField("Components")
                        .enterUnionSetItem("TransformGD")
                        .enterObjectField("Position")
                        .enterArrayItem(0llu);
        std::cout << posX.getFloat()
                  << std::endl;
        ENTLIB_ASSERT(posX.getFloat() == 105.2244);
        auto& entityRung = expl;
        auto floatA = entityRung.enterObjectField("Components")
                          .enterUnionSetItem("TransformGD")
                          .enterObjectField("Position")
                          .enterArrayItem(0llu)
                          .getFloat();
        auto floatB = entityRung.enterObjectField("Components")
                          .enterUnionSetItem("TransformGD")
                          .enterObjectField("Position")
                          .enterArrayItem(0llu)
                          .getFloat();
        ENTLIB_ASSERT(floatA == 105.2244);
        ENTLIB_ASSERT(floatB == 105.2244);

        ENTLIB_ASSERT(
            expl.enterObjectField("Components")
                .enterUnionSetItem("SubScene")
                .enterObjectField("Embedded")
                .enterObjectSetItem("EP1-Spout_LINK_001")
                .enterObjectField("Name")
                .getString()
            == std::string("EP1-Spout_LINK_001"));
    }
    {
        Layer expl(&entlib, nullptr, entlib.getSchema(entitySchemaName), "instance.entity");
        ENTLIB_ASSERT(expl.enterObjectField("Name").getString() == std::string("PlayerSpawner_"));
        auto type = expl.enterObjectField("Components").enterUnionSetItem("NetworkNode").enterObjectField("Type");
        std::cout << type.getString() << std::endl;
        ENTLIB_ASSERT(
            expl.enterObjectField("Components")
                .enterUnionSetItem("NetworkNode")
                .enterObjectField("Type")
                .getString()
            == std::string("Spawner"));
        std::cout << expl.enterObjectField("Components")
                         .enterUnionSetItem("TransformGD")
                         .enterObjectField("Matrix")
                         .enterArrayItem(3llu)
                         .getFloat()
                  << std::endl;
        auto pos2 = expl.enterObjectField("Components")
                        .enterUnionSetItem("TransformGD")
                        .enterObjectField("Position")
                        .enterArrayItem(2llu)
                        .getFloat();
        ENTLIB_ASSERT(fabs(pos2 - 29.6635) < FLT_EPSILON);
        ENTLIB_ASSERT(
            expl.enterObjectField("Components")
                .enterUnionSetItem("SubScene")
                .enterObjectField("Embedded")
                .enterObjectSetItem("EP1-Spout_LINK_001")
                .enterObjectField("Name")
                .getString()
            == std::string("EP1-Spout_LINK_001"));
        ENTLIB_ASSERT(
            expl.enterObjectField("ActorStates")
                .enterUnionSetItem("ActorStateHoldingItem")
                .enterObjectField("ItemEntityRef")
                .getString()
            == std::string("tutu"));
        auto components = expl.enterObjectField("Components");
        auto transformGD = components.enterUnionSetItem("TransformGD");
        auto orientation = transformGD.enterObjectField("Orientation");
        auto ori3 = orientation.enterArrayItem(3llu);
        ENTLIB_ASSERT(fabs(ori3.getFloat() - 0.9916236400604248) < FLT_EPSILON);
        ori3.setFloat(2.);
        ENTLIB_ASSERT(ori3.getFloat() == 2.);
        auto soundAreaGD = expl.enterObjectField("Components").enterUnionSetItem("SoundAreaGD");
        ENTLIB_ASSERT(soundAreaGD.isSet() == false);
        ENTLIB_ASSERT(soundAreaGD.isDefault() == true);
        auto keys = components.getUnionSetKeysString();
        keys = components.getUnionSetKeysString();
        auto staffVertebrasGD =
            expl.enterObjectField("Components").enterUnionSetItem("StaffVertebrasGD");
        ENTLIB_ASSERT(staffVertebrasGD.isSet() == false);
        ENTLIB_ASSERT(staffVertebrasGD.isDefault() == true);
        keys = components.getUnionSetKeysString();

        expl.save("instance.prout.entity");
        // Must not crash
        Layer prefab2(&entlib, nullptr, entlib.getSchema(entitySchemaName), "instance.prout.entity");
        auto comp2 = prefab2.enterObjectField("Components");
        auto characterControllerGD = comp2.enterUnionSetItem("CharacterControllerGD");
        auto clamberData = characterControllerGD.enterObjectField("ClamberData");
        auto vertOriRatio = clamberData.enterObjectField("VerticalOrientationRatio");
        auto in = vertOriRatio.enterObjectField("in");
        auto in0 = in.enterArrayItem(0);
        in0.setFloat(3.33);
    }
    {
        std::cout << "Read instance.entity with LazyLib" << std::endl;
        clock_t start = clock();
        Layer expl(&entlib, nullptr, entlib.getSchema(entitySchemaName), "instance.entity");
        clock_t end = clock();

        auto ent = entlib.loadEntityAsNode(R"(instance.entity)");

        std::cout << float(end - start) / CLOCKS_PER_SEC << std::endl;
        CompareNode compare(ent.get());
        std::cout << "Visit all" << std::endl;
        start = clock();
        Ent::visitRecursive(expl, compare);
        end = clock();
        std::cout << float(end - start) / CLOCKS_PER_SEC << std::endl;

        nlohmann::json newDoc = nlohmann::json::object();
        Layer destExpl(&entlib, nullptr, expl.getSchema(), "", &newDoc);
        CopyToEmptyNode copier(destExpl);
        Ent::visitRecursive(expl, copier);
        entlib.saveJsonFile(&newDoc, "instance.cursor.entity");
    }
    bool testLoading = true;
    if (testLoading)
    {
        entlib.rawdataPath = "X:/RawData";
        std::cout << "Read SceneKOM.scene with LazyLib" << std::endl;
        clock_t start = clock();
        Layer expl(
            &entlib,
            nullptr,
            entlib.getSchema(entitySchemaName),
            R"(X:\RawData\20_scene\KOM2021\SceneKOM\SceneKOM\editor\SceneKOM.scene)");
        clock_t end = clock();
        std::cout << float(end - start) / CLOCKS_PER_SEC << std::endl;

        bool testCopy = false;
        if (testCopy)
        {
            std::cout << "Copy SceneKOM.scene with LazyLib" << std::endl;
            nlohmann::json newDoc = nlohmann::json::object();
            Layer destExpl(&entlib, nullptr, expl.getSchema(), "", &newDoc);
            CopyToEmptyNode copier(destExpl);
            visitRecursive(expl, copier);

            std::cout << "CompareCursor SceneKOM.scene wth the clone" << std::endl;
            CompareCursor comparator(destExpl);
            Ent::visitRecursive(expl, comparator);

            std::cout << "Save SceneKOM.scene with LazyLib" << std::endl;
            entlib.saveJsonFile(&newDoc, "SceneKOM.scene");
        }
        /*
        std::cout << "Read SceneKOM.scene with NodeLib" << std::endl;
        start = clock();
        auto ent = entlib.loadEntityAsNode(
            R"(X:\RawData\20_scene\KOM2021\SceneKOM\SceneKOM\editor\SceneKOM.scene)");
        end = clock();
        std::cout << float(end - start) / CLOCKS_PER_SEC << std::endl;

        std::cout << "Travserse SceneKOM.scene with NodeLib" << std::endl;
        start = clock();
        auto nodeCount = countNodes(ent.get());
        end = clock();
        std::cout << float(end - start) / CLOCKS_PER_SEC << std::endl;
        std::cout << "Primitive count : " << nodeCount << std::endl;
        */

        PrimitiveCounterVisitor visitor;
        std::cout << "Travserse SceneKOM.scene with LazyLib" << std::endl;
        start = clock();
        Ent::visitRecursive(expl, visitor);
        //Ent::visitRecursive(expl, visitor);
        //Ent::visitRecursive(expl, visitor);
        //Ent::visitRecursive(expl, visitor);
        //Ent::visitRecursive(expl, visitor);
        end = clock();
        std::cout << float(end - start) / CLOCKS_PER_SEC << std::endl;
        std::cout << "Primitive count : " << visitor.primitiveCount << std::endl;
    }
    bool testCompare = false;
    if (testCompare)
    {
        entlib.rawdataPath = "X:/RawData";
        std::cout << "Read SceneKOM.scene with LazyLib" << std::endl;
        clock_t start = clock();
        Layer expl(
            &entlib,
            nullptr,
            entlib.getSchema(entitySchemaName),
            R"(X:\RawData\20_scene\KOM2021\SceneKOM\SceneKOM\editor\SceneKOM.scene)");
        clock_t end = clock();
        std::cout << float(end - start) / CLOCKS_PER_SEC << std::endl;

        std::cout << "Read SceneKOM.scene with NodeLib" << std::endl;
        start = clock();
        auto ent = entlib.loadEntityAsNode(
            R"(X:\RawData\20_scene\KOM2021\SceneKOM\SceneKOM\editor\SceneKOM.scene)");
        end = clock();
        std::cout << float(end - start) / CLOCKS_PER_SEC << std::endl;

        std::cout << "Travserse SceneKOM.scene with NodeLib" << std::endl;
        start = clock();
        auto nodeCount = countNodes(ent.get());
        end = clock();
        std::cout << float(end - start) / CLOCKS_PER_SEC << std::endl;
        std::cout << "Primitive count : " << nodeCount << std::endl;

        std::cout << "Compare both" << std::endl;
        start = clock();
        CompareNode comparator(ent.get());
        Ent::visitRecursive(expl, comparator);
        end = clock();
        std::cout << float(end - start) / CLOCKS_PER_SEC << std::endl;
    }
}
