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
#include <EntityLib/CursorRestore.h>

using namespace Ent;

class PrintNode : public RecursiveVisitor
{
    Cursor& expl;
    size_t tab = 0;

    std::string getTab() const
    {
        return std::string(tab * 4, ' ');
    }

public:
    PrintNode(Cursor& _expl)
        : expl(_expl)
    {
    }

    void inObject() override
    {
        ++tab;
    }
    bool inObjectField(char const* key) override
    {
        // std::cout << "dksflghjdfjg" << getTab() << '"' << key << "\": " << std::endl;
        std::cout << getTab() << '"' << key << "\": " << std::endl;
        ++tab;
        return true;
    }
    void outObjectField([[maybe_unused]] char const* _key) override
    {
        --tab;
    }
    void outObject() override
    {
        --tab;
    }
    void inUnion(char const* type) override
    {
        std::cout << getTab() << '"' << type << "\": " << std::endl;
        ++tab;
    }
    void outUnion() override
    {
        --tab;
    }
    void inMap() override
    {
        ++tab;
    }
    void outMap() override
    {
        --tab;
    }
    void inMapElement(char const* key) override
    {
        ++tab;
        std::cout << getTab() << '"' << key << "\": " << std::endl;
    }
    void inMapElement(int64_t key) override
    {
        ++tab;
        std::cout << getTab() << key << ": " << std::endl;
    }
    void outMapElement() override
    {
        --tab;
    }
    void inPrimSet(Ent::DataType) override
    {
        ++tab;
    }
    void inArrayElement(size_t) override
    {
    }
    void outArrayElement() override
    {
    }
    void key(char const* _key) override
    {
        std::cout << getTab() << '"' << _key << '"' << std::endl;
    }
    void key(int64_t _key) override
    {
        std::cout << getTab() << _key << std::endl;
    }
    void outPrimSet() override
    {
        --tab;
    }
    void inUnionSet() override
    {
        ++tab;
    }
    void inUnionSetElement(char const* key) override
    {
        std::cout << getTab() << '"' << key << '"' << std::endl;
        ++tab;
    }
    void outUnionSetElement() override
    {
        --tab;
    }
    void outUnionSet() override
    {
        --tab;
    }
    void inObjectSet() override
    {
        ++tab;
    }
    void outObjectSet() override
    {
        --tab;
    }
    void inObjectSetElement(char const* key) override
    {
        std::cout << getTab() << '"' << key << '"' << std::endl;
    }
    void inObjectSetElement(int64_t key) override
    {
        std::cout << getTab() << key << std::endl;
    }
    void outObjectSetElement() override
    {
    }
    void inArray() override
    {
        ++tab;
    }
    void outArray() override
    {
        --tab;
    }
    void nullNode() override
    {
        std::cout << getTab() << "null" << std ::endl;
    }
    void boolNode() override
    {
        std::cout << getTab() << expl.getBool() << std::endl;
    }
    void intNode() override
    {
        std::cout << getTab() << expl.getInt() << std::endl;
    }
    void floatNode() override
    {
        std::cout << getTab() << expl.getFloat() << std::endl;
    }
    void stringNode() override
    {
        std::cout << getTab() << '"' << expl.getString() << '"' << std::endl;
    }
    void entityRefNode() override
    {
        std::cout << getTab() << '"' << expl.getEntityRef().entityPath.c_str() << '"' << std::endl;
    }
};

class CompareNode : public RecursiveVisitor
{
    Cursor& expl;
    std::vector<Node*> nodes;

public:
    CompareNode(Cursor& _expl, Node* n)
        : expl(_expl)
        , nodes({n})
    {
    }
    void inObject() override
    {
        // ENTLIB_ASSERT(nodes.back()->getFieldNames().size() == expl.get);
    }
    bool inObjectField(char const* key) override
    {
        nodes.push_back(nodes.back()->at(key));
        ENTLIB_ASSERT(nodes.back() != nullptr);
        return true;
    }
    void outObjectField([[maybe_unused]] char const* _key) override
    {
        nodes.pop_back();
    }
    void outObject() override
    {
    }
    void inUnion(char const*) override
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
    void outUnion() override
    {
        nodes.pop_back();
    }
    void inMap() override
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
    void outMap() override
    {
    }
    void inMapElement(char const* key) override
    {
        nodes.push_back(nodes.back()->mapGet(key));
        ENTLIB_ASSERT(nodes.back() != nullptr);
    }
    void inMapElement(int64_t key) override
    {
        nodes.push_back(nodes.back()->mapGet(key));
        ENTLIB_ASSERT(nodes.back() != nullptr);
    }
    void outMapElement() override
    {
        nodes.pop_back();
    }
    void inPrimSet(Ent::DataType) override
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
    void inArrayElement(size_t i) override
    {
        nodes.push_back(nodes.back()->at(i));
        ENTLIB_ASSERT(nodes.back() != nullptr);
    }
    void outArrayElement() override
    {
        nodes.pop_back();
    }
    void key(char const* key) override
    {
        ENTLIB_ASSERT(nodes.back()->mapGet(key) != nullptr);
    }
    void key(int64_t key) override
    {
        ENTLIB_ASSERT(nodes.back()->mapGet(key) != nullptr);
    }
    void outPrimSet() override
    {
    }
    void inUnionSet() override
    {
        auto a = nodes.back()->getKeysString();
        auto b = expl.getUnionSetKeysString();
        ENTLIB_ASSERT(a.size() == b.size());
        ENTLIB_ASSERT(nodes.back()->size() == expl.size());
        ENTLIB_ASSERT(nodes.back()->getSchema() == expl.getSchema());
    }
    void inUnionSetElement(char const* type) override
    {
        auto union_ = nodes.back()->mapGet(type);
        ENTLIB_ASSERT(union_ != nullptr);
        nodes.push_back(union_->getUnionData());
        ENTLIB_ASSERT(nodes.back() != nullptr);
    }
    void outUnionSetElement() override
    {
        nodes.pop_back();
    }
    void outUnionSet() override
    {
    }
    void inObjectSet() override
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
    void outObjectSet() override
    {
    }
    void inObjectSetElement(char const* key) override
    {
        nodes.push_back(nodes.back()->mapGet(key));
        ENTLIB_ASSERT(nodes.back() != nullptr);
    }
    void inObjectSetElement(int64_t key) override
    {
        nodes.push_back(nodes.back()->mapGet(key));
        ENTLIB_ASSERT(nodes.back() != nullptr);
    }
    void outObjectSetElement() override
    {
        nodes.pop_back();
    }
    void inArray() override
    {
        ENTLIB_ASSERT(nodes.back()->size() == expl.size());
        if (nodes.back()->size() != expl.size())
            expl.size();
        ENTLIB_ASSERT(nodes.back()->size() == expl.size());
    }
    void outArray() override
    {
    }
    void nullNode() override
    {
    }
    void boolNode() override
    {
        // std::cout << elt.getBool() << " " << nodes.back()->getBool() << std::endl;
        ENTLIB_ASSERT(expl.getBool() == nodes.back()->getBool());
    }
    void intNode() override
    {
        // std::cout << elt.getInt() << " " << nodes.back()->getInt() << std::endl;
        if (expl.getInt() != nodes.back()->getInt())
            expl.getInt();
        ENTLIB_ASSERT(expl.getInt() == nodes.back()->getInt());
    }
    void floatNode() override
    {
        // std::cout << elt.getFloat() << " " << nodes.back()->getFloat() << std::endl;
        if (fabs(expl.getFloat() - nodes.back()->getFloat()) >= FLT_EPSILON)
            expl.getFloat();
        // ENTLIB_ASSERT(fabs(elt.getFloat() - nodes.back()->getFloat()) < FLT_EPSILON);
    }
    void stringNode() override
    {
        if (strcmp(expl.getString(), nodes.back()->getString()) != 0)
        {
            std::cout << expl.getString() << " " << nodes.back()->getString() << std::endl;
            expl.getString();
        }
        ENTLIB_ASSERT(strcmp(expl.getString(), nodes.back()->getString()) == 0);
    }
    void entityRefNode() override
    {
        //std::cout << elt.getEntityRef().entityPath.c_str() << " "
        //          << nodes.back()->getEntityRef().entityPath.c_str() << std::endl;
        ENTLIB_ASSERT(expl.getEntityRef() == nodes.back()->getEntityRef());
    }
};

class CompareCursor : public RecursiveVisitor
{
    Cursor& expl;
    Cursor& expl2;

public:
    CompareCursor(Cursor& _expl, Cursor& _expl2)
        : expl(_expl)
        , expl2(_expl2)
    {
    }
    void inObject() override
    {
        if (expl.getPrefab())
        {
            ENTLIB_ASSERT(expl2.getPrefab());
            ENTLIB_ASSERT(expl.getPrefab()->_getRawJson() == expl2.getPrefab()->_getRawJson());
        }
        auto a = expl.getInstanceOf();
        auto b = expl2.getInstanceOf();
        ENTLIB_ASSERT(
            (a == nullptr and b == nullptr)
            or (a != nullptr and b != nullptr and a == std::string_view(b)));
    }
    bool inObjectField(char const* key) override
    {
        expl2.enterObjectField(key);
        if (expl.getPrefab())
        {
            ENTLIB_ASSERT(expl2.getPrefab());
            ENTLIB_ASSERT(expl.getPrefab()->_getRawJson() == expl2.getPrefab()->_getRawJson());
        }
        return true;
    }
    void outObjectField([[maybe_unused]] char const* _key) override
    {
        expl2.exit();
    }
    void inUnion(char const* _type) override
    {
        expl2.enterUnionData(_type);
    }
    void outUnion() override
    {
        expl2.exit();
    }
    void inMap() override
    {
        ENTLIB_ASSERT(expl2.size() == expl.size());
        switch (expl.getMapKeyType())
        {
        case Ent::DataType::string:
            ENTLIB_ASSERT(expl2.getMapKeysString().size() == expl.getMapKeysString().size());
            break;
        case Ent::DataType::integer:
            ENTLIB_ASSERT(expl2.getMapKeysInt().size() == expl.getMapKeysInt().size());
            break;
        default: ENTLIB_LOGIC_ERROR("Unexpected key type");
        }
    }
    void inMapElement(char const* _key) override
    {
        expl2.enterMapItem(_key);
    }
    void inMapElement(int64_t _key) override
    {
        expl2.enterMapItem(_key);
    }
    void outMapElement() override
    {
        expl2.exit();
    }
    void inPrimSet(Ent::DataType) override
    {
        ENTLIB_ASSERT(expl2.size() == expl.size());
        auto& itemType = expl.getSchema()->singularItems.get()->get();
        switch (itemType.type)
        {
        case Ent::DataType::string:
            ENTLIB_ASSERT(expl2.getPrimSetKeysString() == expl.getPrimSetKeysString());
            break;
        case Ent::DataType::integer:
            ENTLIB_ASSERT(expl2.getPrimSetKeysInt() == expl.getPrimSetKeysInt());
            break;
        default: ENTLIB_LOGIC_ERROR("Unexpected key type");
        }
    }
    void inArrayElement(size_t i) override
    {
        expl2.enterArrayItem(i);
    }
    void outArrayElement() override
    {
        expl2.exit();
    }
    void inUnionSet() override
    {
        if (expl.getPrefab())
        {
            ENTLIB_ASSERT(expl2.getPrefab());
            ENTLIB_ASSERT(expl.getPrefab()->_getRawJson() == expl2.getPrefab()->_getRawJson());
        }
        auto a = expl2.getUnionSetKeysString();
        auto b = expl.getUnionSetKeysString();
        ENTLIB_ASSERT(a.size() == b.size());
        ENTLIB_ASSERT(expl2.getSchema() == expl.getSchema());
        for (auto [name, type] : a)
        {
            ENTLIB_ASSERT(b.at(name) == type);
        }
    }
    void inUnionSetElement(char const* _type) override
    {
        expl2.enterUnionSetItem(_type);
    }
    void outUnionSetElement() override
    {
        expl2.exit();
    }
    void inObjectSet() override
    {
        if (expl.getPrefab())
        {
            ENTLIB_ASSERT(expl2.getPrefab());
            ENTLIB_ASSERT(expl.getPrefab()->_getRawJson() == expl2.getPrefab()->_getRawJson());
        }
        ENTLIB_ASSERT(expl2.size() == expl.size());
        switch (expl2.getObjectSetKeyType())
        {
        case Ent::DataType::string:
        {
            auto a = expl2.getObjectSetKeysString();
            auto b = expl.getObjectSetKeysString();
            ENTLIB_ASSERT(a.size() == b.size());
            ENTLIB_ASSERT(expl2.getSchema() == expl.getSchema());
            for (auto name : a)
            {
                ENTLIB_ASSERT(b.count(name));
            }
            break;
        }
        case Ent::DataType::integer:
            ENTLIB_ASSERT(expl2.getObjectSetKeysInt() == expl.getObjectSetKeysInt());
            break;
        default: ENTLIB_LOGIC_ERROR("Unexpected key type");
        }
    }
    void inObjectSetElement(char const* _key) override
    {
        expl2.enterObjectSetItem(_key);
        if (expl.getPrefab())
        {
            ENTLIB_ASSERT(expl2.getPrefab());
            auto a = expl.getPrefab()->_getRawJson();
            auto b = expl2.getPrefab()->_getRawJson();
            ENTLIB_ASSERT(a == b);
        }
    }
    void inObjectSetElement(int64_t _key) override
    {
        expl2.enterObjectSetItem(_key);
    }
    void outObjectSetElement() override
    {
        expl2.exit();
    }
    void inArray() override
    {
        ENTLIB_ASSERT(expl2.size() == expl.size());
    }
    void nullNode() override
    {
        ENTLIB_ASSERT(expl2.getDataType() == Ent::DataType::null);
    }
    void boolNode() override
    {
        ENTLIB_ASSERT(expl.isSet() == expl2.isSet());
        ENTLIB_ASSERT(expl.getBool() == expl2.getBool());
    }
    void intNode() override
    {
        ENTLIB_ASSERT(expl.isSet() == expl2.isSet());
        ENTLIB_ASSERT(expl.getInt() == expl2.getInt());
    }
    void floatNode() override
    {
        ENTLIB_ASSERT(expl.isSet() == expl2.isSet());
        if (expl.getFloat() != expl2.getFloat())
        {
            std::cout << expl.isSet() << " " << expl2.isSet() << std::endl;
            std::cout << expl.getFloat() << " " << expl2.getFloat() << std::endl;
            if (expl.getPrefab())
            {
                ENTLIB_ASSERT(expl2.getPrefab());
                ENTLIB_ASSERT(expl.getPrefab()->_getRawJson() == expl2.getPrefab()->_getRawJson());
            }
        }
        ENTLIB_ASSERT(expl.getFloat() == expl2.getFloat());
    }
    void stringNode() override
    {
        ENTLIB_ASSERT(expl.isSet() == expl2.isSet());
        ENTLIB_ASSERT(expl.getString() == std::string_view(expl2.getString()));
    }
    void entityRefNode() override
    {
        ENTLIB_ASSERT(expl.isSet() == expl2.isSet());
        ENTLIB_ASSERT(expl.getEntityRef() == expl2.getEntityRef());
    }
};

class PrimitiveCounterVisitor : public RecursiveVisitor
{
public:
    size_t primitiveCount = 0;

    void key(char const*) override
    {
        ++primitiveCount;
    }
    void key(int64_t) override
    {
        ++primitiveCount;
    }
    void nullNode() override
    {
        ++primitiveCount;
    }
    void boolNode() override
    {
        ++primitiveCount;
    }
    void intNode() override
    {
        ++primitiveCount;
    }
    void floatNode() override
    {
        ++primitiveCount;
    }
    void stringNode() override
    {
        ++primitiveCount;
    }
    void entityRefNode() override
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
        Ent::Cursor quickCreatureSwitchEntity(&entlib, entlib.getEntitySchema(), nullptr, &storage);
        quickCreatureSwitchEntity.enterObjectField("Name");
        quickCreatureSwitchEntity.setString("Debug Quick Creatures Switch");
        quickCreatureSwitchEntity.exit();
    }
    {
        std::ifstream ifstr("test.SeedPatch.node");
        std::string filedata;
        std::getline(ifstr, filedata, char(0));
        auto& d = entlib.readJsonFile("test.SeedPatch.node");
        auto& schema = d["$schema"].get_ref<nlohmann::json::string_t const&>();
        auto typeName = getRefTypeName(schema.c_str());
        Cursor simpleObject(&entlib, entlib.getSchema(typeName), "test.SeedPatch.node", &d);
        ENTLIB_ASSERT(simpleObject.enterObjectField("NoiseSizeX").getFloat() == 1.f);
        simpleObject.exit();
        ENTLIB_ASSERT(simpleObject.enterObjectField("NoiseSizeY").getFloat() == 2.f);
        simpleObject.exit();
    }
    {
        std::ifstream ifstr("test.SeedPatch.node");
        std::string filedata;
        std::getline(ifstr, filedata, char(0));
        auto& d = entlib.readJsonFile("test.SeedPatch.node");
        Cursor simpleObject(
            &entlib,
            entlib.getSchema(getRefTypeName(d["$schema"].get_ref<std::string const&>().c_str())),
            "test.SeedPatch.node",
            &d);
        ENTLIB_ASSERT(simpleObject.enterObjectField("NoiseSizeX").getFloat() == 1.f);
        simpleObject.exit();
        simpleObject.enterObjectField("NoiseSizeX").setFloat(2.);
        simpleObject.exit();
        ENTLIB_ASSERT(CursorRestore(simpleObject)->enterObjectField("NoiseSizeX").getFloat() == 2.);
        ENTLIB_ASSERT(simpleObject.enterObjectField("NoiseSizeY").getFloat() == 2.f);
    }
    {
        Cursor expl(&entlib, entlib.getSchema(entitySchemaName), "prefab.entity");
        ENTLIB_ASSERT(
            CursorRestore(expl)->enterObjectField("Name").getString()
            == std::string("PlayerSpawner_"));
        {
            CursorRestore restoreEntity(expl);
            ENTLIB_ASSERT(
                expl.enterObjectField("Components")
                    .enterUnionSetItem("NetworkNode")
                    .enterObjectField("Type")
                    .getString()
                == std::string("Spawner"));
        }
        std::cout << expl.enterObjectField("Components")
                         .enterUnionSetItem("TransformGD")
                         .enterObjectField("Position")
                         .enterArrayItem(0llu)
                         .getFloat()
                  << std::endl;
        ENTLIB_ASSERT(expl.getFloat() == 105.2244);
        expl.exit().exit().exit().exit();
        auto& entityRung = expl.getLastRung();
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
        Cursor expl(&entlib, entlib.getSchema(entitySchemaName), "instance.entity");
        ENTLIB_ASSERT(expl.enterObjectField("Name").getString() == std::string("PlayerSpawner_"));
        expl.exit();
        expl.enterObjectField("Components").enterUnionSetItem("NetworkNode").enterObjectField("Type");
        std::cout << expl.getString() << std::endl;
        expl.exit().exit().exit();
        ENTLIB_ASSERT(
            expl.enterObjectField("Components")
                .enterUnionSetItem("NetworkNode")
                .enterObjectField("Type")
                .getString()
            == std::string("Spawner"));
        expl.exit().exit().exit();
        std::cout << expl.enterObjectField("Components")
                         .enterUnionSetItem("TransformGD")
                         .enterObjectField("Matrix")
                         .enterArrayItem(3llu)
                         .getFloat()
                  << std::endl;
        expl.exit().exit().exit().exit();
        auto pos2 = expl.enterObjectField("Components")
                        .enterUnionSetItem("TransformGD")
                        .enterObjectField("Position")
                        .enterArrayItem(2llu)
                        .getFloat();
        expl.exit().exit().exit().exit();
        ENTLIB_ASSERT(fabs(pos2 - 29.6635) < FLT_EPSILON);
        ENTLIB_ASSERT(
            expl.enterObjectField("Components")
                .enterUnionSetItem("SubScene")
                .enterObjectField("Embedded")
                .enterObjectSetItem("EP1-Spout_LINK_001")
                .enterObjectField("Name")
                .getString()
            == std::string("EP1-Spout_LINK_001"));
        expl.exit().exit().exit().exit().exit();
        ENTLIB_ASSERT(
            expl.enterObjectField("ActorStates")
                .enterUnionSetItem("ActorStateHoldingItem")
                .enterObjectField("ItemEntityRef")
                .getString()
            == std::string("tutu"));
        expl.exit().exit().exit();
        auto& ori3 = expl.enterObjectField("Components")
                         .enterUnionSetItem("TransformGD")
                         .enterObjectField("Orientation")
                         .enterArrayItem(3llu);

        ENTLIB_ASSERT(fabs(ori3.getFloat() - 0.9916236400604248) < FLT_EPSILON);
        ori3.setFloat(2.);
        ENTLIB_ASSERT(ori3.getFloat() == 2.);
        expl.exit().exit().exit().exit();
        expl.enterObjectField("Components").enterUnionSetItem("SoundAreaGD");
        ENTLIB_ASSERT(expl.isSet() == false);
        ENTLIB_ASSERT(expl.isDefault() == true);
        expl.exit().exit();
        expl.enterObjectField("Components");
        auto keys = expl.getUnionSetKeysString();
        keys = expl.getUnionSetKeysString();
        expl.exit();
        expl.enterObjectField("Components").enterUnionSetItem("StaffVertebrasGD");
        ENTLIB_ASSERT(expl.isSet() == false);
        ENTLIB_ASSERT(expl.isDefault() == true);
        expl.exit().exit();
        expl.enterObjectField("Components");
        keys = expl.getUnionSetKeysString();
        expl.exit();

        expl.save("instance.prout.entity");
    }
    {
        std::cout << "Read instance.entity with LazyLib" << std::endl;
        clock_t start = clock();
        Cursor expl(&entlib, entlib.getSchema(entitySchemaName), "instance.entity");
        clock_t end = clock();

        auto ent = entlib.loadEntityAsNode(R"(instance.entity)");

        std::cout << float(end - start) / CLOCKS_PER_SEC << std::endl;
        CompareNode compare(expl, ent.get());
        std::cout << "Visit all" << std::endl;
        start = clock();
        Ent::visitRecursive(expl, compare);
        end = clock();
        std::cout << float(end - start) / CLOCKS_PER_SEC << std::endl;

        nlohmann::json newDoc = nlohmann::json::object();
        Cursor destExpl(&entlib, expl.getSchema(), "", &newDoc);
        CopyToEmptyNode copier(expl, destExpl);
        Ent::visitRecursive(expl, copier);
        entlib.saveJsonFile(&newDoc, "instance.cursor.entity");
    }
    bool testLoading = true;
    if (testLoading)
    {
        entlib.rawdataPath = "X:/RawData";
        std::cout << "Read SceneKOM.scene with LazyLib" << std::endl;
        clock_t start = clock();
        Cursor expl(
            &entlib,
            entlib.getSchema(entitySchemaName),
            R"(X:\RawData\20_scene\KOM2021\SceneKOM\SceneKOM\editor\SceneKOM.scene)");
        clock_t end = clock();
        std::cout << float(end - start) / CLOCKS_PER_SEC << std::endl;

        bool testCopy = true;
        if (testCopy)
        {
            std::cout << "Copy SceneKOM.scene with LazyLib" << std::endl;
            nlohmann::json newDoc = nlohmann::json::object();
            Cursor destExpl(&entlib, expl.getSchema(), "", &newDoc);
            CopyToEmptyNode copier(expl, destExpl);
            visitRecursive(expl, copier);

            std::cout << "CompareCursor SceneKOM.scene wth the clone" << std::endl;
            CompareCursor comparator(expl, destExpl);
            Ent::visitRecursive(expl, comparator);

            std::cout << "Save SceneKOM.scene with LazyLib" << std::endl;
            entlib.saveJsonFile(&newDoc, "SceneKOM.scene");
        }

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
    bool testCompare = true;
    if (testCompare)
    {
        entlib.rawdataPath = "X:/RawData";
        std::cout << "Read SceneKOM.scene with LazyLib" << std::endl;
        clock_t start = clock();
        Cursor expl(
            &entlib,
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
        CompareNode comparator(expl, ent.get());
        Ent::visitRecursive(expl, comparator);
        end = clock();
        std::cout << float(end - start) / CLOCKS_PER_SEC << std::endl;
    }
}
