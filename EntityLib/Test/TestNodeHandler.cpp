#include "TestNodeHandler.h"
#include <EntityLib.h>
#include <../Tools.h>
#include <fstream>
#include <variant>
#include <iostream>
#include <stack>

#include <EntityLib/Visitor.h>
#include <EntityLib/CopyNode.h>
#include "DumpNode.h"

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
    virtual void inArrayElement(size_t)
    {
    }
    virtual void outArrayElement()
    {
    }
    virtual void key(char const* _key)
    {
        std::cout << getTab() << '"' << _key << '"' << std::endl;
    }
    virtual void key(int64_t _key)
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
    virtual void inObject()
    {
        // ENTLIB_ASSERT(nodes.back()->getFieldNames().size() == expl.get);
    }
    virtual bool inObjectField(char const* key)
    {
        nodes.push_back(nodes.back()->at(key));
        ENTLIB_ASSERT(nodes.back() != nullptr);
        return true;
    }
    virtual void outObjectField([[maybe_unused]] char const* _key)
    {
        nodes.pop_back();
    }
    virtual void outObject()
    {
    }
    virtual void inUnion(char const*)
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
    virtual void outUnion()
    {
        nodes.pop_back();
    }
    virtual void inMap()
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
    virtual void outMap()
    {
    }
    virtual void inMapElement(char const* key)
    {
        nodes.push_back(nodes.back()->mapGet(key));
        ENTLIB_ASSERT(nodes.back() != nullptr);
    }
    virtual void inMapElement(int64_t key)
    {
        nodes.push_back(nodes.back()->mapGet(key));
        ENTLIB_ASSERT(nodes.back() != nullptr);
    }
    virtual void outMapElement()
    {
        nodes.pop_back();
    }
    virtual void inPrimSet(Ent::DataType)
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
    virtual void inArrayElement(size_t i)
    {
        nodes.push_back(nodes.back()->at(i));
        ENTLIB_ASSERT(nodes.back() != nullptr);
    }
    virtual void outArrayElement()
    {
        nodes.pop_back();
    }
    virtual void key(char const* key)
    {
        ENTLIB_ASSERT(nodes.back()->mapGet(key) != nullptr);
    }
    virtual void key(int64_t key)
    {
        ENTLIB_ASSERT(nodes.back()->mapGet(key) != nullptr);
    }
    virtual void outPrimSet()
    {
    }
    virtual void inUnionSet()
    {
        ENTLIB_ASSERT(nodes.back()->size() == expl.size());
        ENTLIB_ASSERT(nodes.back()->getSchema() == expl.getSchema());
        ENTLIB_ASSERT(nodes.back()->getKeysString().size() == expl.getUnionSetKeysString().size());
    }
    virtual void inUnionSetElement(char const* type)
    {
        auto union_ = nodes.back()->mapGet(type);
        ENTLIB_ASSERT(union_ != nullptr);
        nodes.push_back(union_->getUnionData());
        ENTLIB_ASSERT(nodes.back() != nullptr);
    }
    virtual void outUnionSetElement()
    {
        nodes.pop_back();
    }
    virtual void outUnionSet()
    {
    }
    virtual void inObjectSet()
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
    virtual void outObjectSet()
    {
    }
    virtual void inObjectSetElement(char const* key)
    {
        nodes.push_back(nodes.back()->mapGet(key));
        ENTLIB_ASSERT(nodes.back() != nullptr);
    }
    virtual void inObjectSetElement(int64_t key)
    {
        nodes.push_back(nodes.back()->mapGet(key));
        ENTLIB_ASSERT(nodes.back() != nullptr);
    }
    virtual void outObjectSetElement()
    {
        nodes.pop_back();
    }
    virtual void inArray()
    {
        ENTLIB_ASSERT(nodes.back()->size() == expl.size());
        if (nodes.back()->size() != expl.size())
            expl.size();
        ENTLIB_ASSERT(nodes.back()->size() == expl.size());
    }
    virtual void outArray()
    {
    }
    virtual void nullNode()
    {
    }
    virtual void boolNode()
    {
        // std::cout << elt.getBool() << " " << nodes.back()->getBool() << std::endl;
        ENTLIB_ASSERT(expl.getBool() == nodes.back()->getBool());
    }
    virtual void intNode()
    {
        // std::cout << elt.getInt() << " " << nodes.back()->getInt() << std::endl;
        if (expl.getInt() != nodes.back()->getInt())
            expl.getInt();
        ENTLIB_ASSERT(expl.getInt() == nodes.back()->getInt());
    }
    virtual void floatNode()
    {
        // std::cout << elt.getFloat() << " " << nodes.back()->getFloat() << std::endl;
        if (fabs(expl.getFloat() - nodes.back()->getFloat()) >= FLT_EPSILON)
            expl.getFloat();
        // ENTLIB_ASSERT(fabs(elt.getFloat() - nodes.back()->getFloat()) < FLT_EPSILON);
    }
    virtual void stringNode()
    {
        if (strcmp(expl.getString(), nodes.back()->getString()) != 0)
        {
            std::cout << expl.getString() << " " << nodes.back()->getString() << std::endl;
            expl.getString();
        }
        ENTLIB_ASSERT(strcmp(expl.getString(), nodes.back()->getString()) == 0);
    }
    virtual void entityRefNode()
    {
        //std::cout << elt.getEntityRef().entityPath.c_str() << " "
        //          << nodes.back()->getEntityRef().entityPath.c_str() << std::endl;
        ENTLIB_ASSERT(expl.getEntityRef() == nodes.back()->getEntityRef());
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

void testNodeHandler(Ent::EntityLib& entlib)
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
        DumpNode dumper(simpleObject);
        Ent::visitRecursive(simpleObject, dumper, true);
        std::cout << dumper.getResult().dump(4) << std::endl;
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
        ENTLIB_ASSERT(simpleObject.enterObjectField("NoiseSizeX").getFloat() == 2.);
        simpleObject.exit();
        ENTLIB_ASSERT(simpleObject.enterObjectField("NoiseSizeY").getFloat() == 2.f);
        // ENTLIB_ASSERT(simpleObject.at("NoiseOffsetX").getFloat() == 0.f);
    }
    {
        FileCursor expl(entlib.getSchema(entitySchemaName), "prefab.entity");
        expl.enterObjectField("Name");
        if (auto value = expl.back())
        {
            std::cout << value->get_ref<std::string const&>() << std::endl;
        }
        expl.exit();
        expl.enterObjectField("Components").enterUnionSetItem("NetworkNode").enterObjectField("Type");
        if (auto value = expl.back())
        {
            std::cout << value->get_ref<std::string const&>().c_str() << std::endl;
        }
        expl.exit().exit();
        expl.enterUnionSetItem("TransformGD").enterObjectField("Matrix").enterArrayItem(3);
        if (auto value = expl.back())
        {
            std::cout << value->get<double>() << std::endl;
        }
        expl.exit().exit().exit();
        expl.enterUnionSetItem("SubScene")
            .enterObjectField("Embedded")
            .enterObjectSetItem("EP1-Spout_LINK_001")
            .enterObjectField("Name");
        if (auto value = expl.back())
        {
            std::cout << value->get_ref<std::string const&>() << std::endl;
        }
        //NodeHandler entity(entlib.getSchema(entitySchemaName), &d);
        //ENTLIB_ASSERT(entity.at("Name").getString() != nullptr);
        //ENTLIB_ASSERT(entity.at("Name").getString() == std::string("PlayerSpawner_"));
    }
    {
        Cursor expl(&entlib, entlib.getSchema(entitySchemaName), "prefab.entity");
        ENTLIB_ASSERT(expl.enterObjectField("Name").getString() == std::string("PlayerSpawner_"));
        expl.exit();
        ENTLIB_ASSERT(
            expl.enterObjectField("Components")
                .enterUnionSetItem("NetworkNode")
                .enterObjectField("Type")
                .getString()
            == std::string("Spawner"));
        expl.exit().exit().exit();
        std::cout << expl.enterObjectField("Components")
                         .enterUnionSetItem("TransformGD")
                         .enterObjectField("Position")
                         .enterArrayItem(0llu)
                         .getFloat()
                  << std::endl;
        ENTLIB_ASSERT(expl.getFloat() == 105.2244);
        expl.exit().exit().exit();
        ENTLIB_ASSERT(
            expl.enterUnionSetItem("SubScene")
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

        // PrintNode printer;
        // visit(expl, 0, printer);

        //auto ent = entlib.loadEntityAsNode("instance.entity");
        //CompareNode compare(&ent);
        //visit(expl, 0, compare);
        DumpNode dumper(expl);
        Ent::visitRecursive(expl, dumper, true);
        std::cout << dumper.getResult().dump(4) << std::endl;
    }
    {
        // entlib.rawdataPath = "X:/RawData";
        std::cout << "Read instance.entity with LazyLib" << std::endl;
        clock_t start = clock();
        Cursor expl(&entlib, entlib.getSchema(entitySchemaName), "instance.entity");
        clock_t end = clock();

        auto ent = entlib.loadEntityAsNode(R"(instance.entity)");

        std::cout << float(end - start) / CLOCKS_PER_SEC << std::endl;
        CompareNode compare(expl, ent.get());
        std::cout << "Visit all" << std::endl;
        start = clock();
        Ent::visitRecursive(expl, compare, true);
        end = clock();
        std::cout << float(end - start) / CLOCKS_PER_SEC << std::endl;

        nlohmann::json newDoc = nlohmann::json::object();
        Cursor destExpl(&entlib, expl.getSchema(), "", &newDoc);
        CopyNode copier(expl, destExpl);
        Ent::visitRecursive(expl, copier, true);
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

        {
            std::cout << "Copy SceneKOM.scene with LazyLib" << std::endl;
            nlohmann::json newDoc = nlohmann::json::object();
            Cursor destExpl(&entlib, expl.getSchema(), "", &newDoc);
            CopyNode copier(expl, destExpl);
            visitRecursive(expl, copier, true);
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

        //CompareNode visitor(expl, &ent);
        //std::cout << "Compare Nodes" << std::endl;
        PrimitiveCounterVisitor visitor;
        std::cout << "Travserse SceneKOM.scene with LazyLib" << std::endl;
        start = clock();
        Ent::visitRecursive(expl, visitor, true);
        // visit(expl, 0, visitor);
        // visit(expl, 0, visitor);
        // visit(expl, 0, visitor);
        // visit(expl, 0, visitor);
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
        Ent::visitRecursive(expl, comparator, true);
        end = clock();
        std::cout << float(end - start) / CLOCKS_PER_SEC << std::endl;
    }
}
