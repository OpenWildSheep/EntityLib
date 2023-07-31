#include "TestCursor.h"

#include <catch.hpp>
#include <EntityLib/EntityLib.h>
#include <../Tools.h>
#include <fstream>
#include <iostream>

#include <EntityLib/Visitor.h>
#include <EntityLib/CopyProperty.h>
#include <EntityLib/Property.h>

#include "EntityLib/SearchProperty.h"

using namespace Ent;

class PrintNode : public RecursiveVisitor
{
    size_t tab = 0;

    [[nodiscard]] std::string getTab() const
    {
        return std::string(tab * 4, ' ');
    }

public:
    void inObject([[maybe_unused]] Property const& _prop) override
    {
        ++tab;
    }
    bool inObjectField([[maybe_unused]] Property const& _prop, char const* key) override
    {
        std::cout << getTab() << '"' << key << "\": " << std::endl;
        ++tab;
        return true;
    }
    void outObjectField([[maybe_unused]] Property const& _prop, [[maybe_unused]] char const* _key) override
    {
        --tab;
    }
    void outObject([[maybe_unused]] Property const& _prop) override
    {
        --tab;
    }
    void inUnion([[maybe_unused]] Property const& _prop, char const* type) override
    {
        std::cout << getTab() << '"' << type << "\": " << std::endl;
        ++tab;
    }
    void outUnion([[maybe_unused]] Property const& _prop) override
    {
        --tab;
    }
    void inMap([[maybe_unused]] Property const& _prop) override
    {
        ++tab;
    }
    void outMap([[maybe_unused]] Property const& _prop) override
    {
        --tab;
    }
    void inMapElement([[maybe_unused]] Property const& _prop, char const* key) override
    {
        ++tab;
        std::cout << getTab() << '"' << key << "\": " << std::endl;
    }
    void inMapElement([[maybe_unused]] Property const& _prop, int64_t key) override
    {
        ++tab;
        std::cout << getTab() << key << ": " << std::endl;
    }
    void outMapElement([[maybe_unused]] Property const& _prop) override
    {
        --tab;
    }
    void inPrimSet([[maybe_unused]] Property const& _prop, [[maybe_unused]] DataKind _dataKind) override
    {
        ++tab;
    }
    void inArrayElement([[maybe_unused]] Property const& _prop, [[maybe_unused]] size_t _index) override
    {
    }
    void outArrayElement([[maybe_unused]] Property const& _prop) override
    {
    }
    void key([[maybe_unused]] Property const& _prop, char const* _key) override
    {
        std::cout << getTab() << '"' << _key << '"' << std::endl;
    }
    void key([[maybe_unused]] Property const& _prop, int64_t _key) override
    {
        std::cout << getTab() << _key << std::endl;
    }
    void outPrimSet([[maybe_unused]] Property const& _prop) override
    {
        --tab;
    }
    void inUnionSet([[maybe_unused]] Property const& _prop) override
    {
        ++tab;
    }
    void inUnionSetElement([[maybe_unused]] Property const& _prop, char const* key) override
    {
        std::cout << getTab() << '"' << key << '"' << std::endl;
        ++tab;
    }
    void outUnionSetElement([[maybe_unused]] Property const& _prop) override
    {
        --tab;
    }
    void outUnionSet([[maybe_unused]] Property const& _prop) override
    {
        --tab;
    }
    void inObjectSet([[maybe_unused]] Property const& _prop) override
    {
        ++tab;
    }
    void outObjectSet([[maybe_unused]] Property const& _prop) override
    {
        --tab;
    }
    void inObjectSetElement([[maybe_unused]] Property const& _prop, char const* key) override
    {
        std::cout << getTab() << '"' << key << '"' << std::endl;
    }
    void inObjectSetElement([[maybe_unused]] Property const& _prop, int64_t key) override
    {
        std::cout << getTab() << key << std::endl;
    }
    void outObjectSetElement([[maybe_unused]] Property const& _prop) override
    {
    }
    void inArray([[maybe_unused]] Property const& _prop) override
    {
        ++tab;
    }
    void outArray([[maybe_unused]] Property const& _prop) override
    {
        --tab;
    }
    void boolProperty(Property const& _prop) override
    {
        std::cout << getTab() << _prop.getBool() << std::endl;
    }
    void intProperty(Property const& _prop) override
    {
        std::cout << getTab() << _prop.getInt() << std::endl;
    }
    void floatProperty(Property const& _prop) override
    {
        std::cout << getTab() << _prop.getFloat() << std::endl;
    }
    void stringProperty(Property const& _prop) override
    {
        std::cout << getTab() << '"' << _prop.getString() << '"' << std::endl;
    }
    void entityRefProperty(Property const& _prop) override
    {
        std::cout << getTab() << '"' << _prop.getEntityRef().entityPath.c_str() << '"' << std::endl;
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
        expl2 = *expl2.getParent();
    }

public:
    explicit CompareCursor(Property _expl2)
        : expl2(std::move(_expl2))
    {
    }
    void inObject(Property const& _prop) override
    {
        ENTLIB_ASSERT(expl2.isSet() == _prop.isSet());
        if (_prop.hasPrefab())
        {
            ENTLIB_ASSERT(expl2.hasPrefab());
            ENTLIB_ASSERT(_prop.getPrefab()->getRawJson() == expl2.getPrefab()->getRawJson());
        }
        auto const* const a = _prop.getInstanceOf();
        auto const* const b = expl2.getInstanceOf();
        ENTLIB_ASSERT(
            (a == nullptr and b == nullptr)
            or (a != nullptr and b != nullptr and a == std::string_view(b)));
    }
    bool inObjectField(Property const& _prop, char const* key) override
    {
        expl2 = expl2.getObjectField(key);
        ENTLIB_ASSERT(expl2.getSchema() == _prop.getSchema());
        bool expl2_isSet = expl2.isSet();
        bool _prop_isSet = _prop.isSet();
        ENTLIB_ASSERT(expl2_isSet == _prop_isSet);
        if (_prop.hasPrefab())
        {
            ENTLIB_ASSERT(expl2.hasPrefab());
            ENTLIB_ASSERT(_prop.getPrefab()->getRawJson() == expl2.getPrefab()->getRawJson());
        }
        return true;
    }
    void outObjectField([[maybe_unused]] Property const& _prop, [[maybe_unused]] char const* _key) override
    {
        pop();
    }
    void inUnion([[maybe_unused]] Property const& _prop, char const* _type) override
    {
        expl2 = *expl2.getUnionData(_type);
        ENTLIB_ASSERT(expl2.isSet() == _prop.isSet());
    }
    void outUnion([[maybe_unused]] Property const& _prop) override
    {
        pop();
    }
    void inMap(Property const& _prop) override
    {
        ENTLIB_ASSERT(expl2.isSet() == _prop.isSet());
        ENTLIB_ASSERT(expl2.size() == _prop.size());
        switch (_prop.getMapKeyKind())
        {
        case DataKind::entityRef: [[fallthrough]];
        case DataKind::string:
            ENTLIB_ASSERT(expl2.getMapKeysString().size() == _prop.getMapKeysString().size());
            break;
        case DataKind::integer:
            ENTLIB_ASSERT(expl2.getMapKeysInt().size() == _prop.getMapKeysInt().size());
            break;
        default: ENTLIB_LOGIC_ERROR("Unexpected key type");
        }
    }
    void inMapElement([[maybe_unused]] Property const& _prop, char const* _key) override
    {
        expl2 = *expl2.getMapItem(_key);
        ENTLIB_ASSERT(expl2.isSet() == _prop.isSet());
    }
    void inMapElement([[maybe_unused]] Property const& _prop, int64_t _key) override
    {
        expl2 = *expl2.getMapItem(_key);
        ENTLIB_ASSERT(expl2.isSet() == _prop.isSet());
    }
    void outMapElement([[maybe_unused]] Property const& _prop) override
    {
        pop();
    }
    void inPrimSet(Property const& _prop, [[maybe_unused]] DataKind _dataKind) override
    {
        ENTLIB_ASSERT(expl2.isSet() == _prop.isSet());
        ENTLIB_ASSERT(expl2.size() == _prop.size());
        auto const& itemType = _prop.getSchema()->singularItems->get();
        switch (itemType.getDataKind())
        {
        case DataKind::entityRef: [[fallthrough]];
        case DataKind::string:
            ENTLIB_ASSERT(expl2.getPrimSetKeysString() == _prop.getPrimSetKeysString());
            break;
        case DataKind::integer:
            ENTLIB_ASSERT(expl2.getPrimSetKeysInt() == _prop.getPrimSetKeysInt());
            break;
        default: ENTLIB_LOGIC_ERROR("Unexpected key type");
        }
    }
    void inArrayElement([[maybe_unused]] Property const& _prop, size_t i) override
    {
        expl2 = expl2.getArrayItem(i);
        ENTLIB_ASSERT(expl2.isSet() == _prop.isSet());
    }
    void outArrayElement([[maybe_unused]] Property const& _prop) override
    {
        pop();
    }
    void inUnionSet(Property const& _prop) override
    {
        ENTLIB_ASSERT(expl2.isSet() == _prop.isSet());
        if (_prop.hasPrefab())
        {
            ENTLIB_ASSERT(expl2.hasPrefab());
            ENTLIB_ASSERT(_prop.getPrefab()->getRawJson() == expl2.getPrefab()->getRawJson());
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
    void inUnionSetElement([[maybe_unused]] Property const& _prop, char const* _type) override
    {
        expl2 = *expl2.getUnionSetItem(_type);
        auto expl2_isSet = expl2.isSet();
        auto _prop_isSet = _prop.isSet();
        ENTLIB_ASSERT(expl2_isSet == _prop_isSet);
    }
    void outUnionSetElement([[maybe_unused]] Property const& _prop) override
    {
        pop();
    }
    void inObjectSet(Property const& _prop) override
    {
        if (_prop.hasPrefab())
        {
            ENTLIB_ASSERT(expl2.hasPrefab());
            ENTLIB_ASSERT(_prop.getPrefab()->getRawJson() == expl2.getPrefab()->getRawJson());
        }
        ENTLIB_ASSERT(expl2.size() == _prop.size());
        ENTLIB_ASSERT(expl2.isSet() == _prop.isSet());
        switch (expl2.getObjectSetKeyKind())
        {
        case DataKind::entityRef: [[fallthrough]];
        case DataKind::string:
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
        case DataKind::integer:
            ENTLIB_ASSERT(expl2.getObjectSetKeysInt() == _prop.getObjectSetKeysInt());
            break;
        default: ENTLIB_LOGIC_ERROR("Unexpected key type");
        }
    }
    void inObjectSetElement(Property const& _prop, char const* _key) override
    {
        expl2 = *expl2.getObjectSetItem(_key);
        ENTLIB_ASSERT(expl2.isSet() == _prop.isSet());
        if (_prop.hasPrefab())
        {
            ENTLIB_ASSERT(expl2.hasPrefab());
            auto const* const a = _prop.getPrefab()->getRawJson();
            auto const* const b = expl2.getPrefab()->getRawJson();
            ENTLIB_ASSERT(a == b);
        }
    }
    void inObjectSetElement([[maybe_unused]] Property const& _prop, int64_t _key) override
    {
        expl2 = *expl2.getObjectSetItem(_key);
        ENTLIB_ASSERT(expl2.isSet() == _prop.isSet());
    }
    void outObjectSetElement([[maybe_unused]] Property const& _prop) override
    {
        pop();
    }
    void inArray(Property const& _prop) override
    {
        ENTLIB_ASSERT(expl2.size() == _prop.size());
        ENTLIB_ASSERT(expl2.isSet() == _prop.isSet());
    }
    void boolProperty([[maybe_unused]] Property const& _prop) override
    {
        ENTLIB_ASSERT(_prop.isSet() == expl2.isSet());
        ENTLIB_ASSERT(_prop.getBool() == expl2.getBool());
    }
    void intProperty([[maybe_unused]] Property const& _prop) override
    {
        ENTLIB_ASSERT(_prop.isSet() == expl2.isSet());
        ENTLIB_ASSERT(_prop.getInt() == expl2.getInt());
    }
    void floatProperty(Property const& _prop) override
    {
        ENTLIB_ASSERT(_prop.isSet() == expl2.isSet());
        if (_prop.getFloat() != expl2.getFloat())
        {
            std::cout << _prop.isSet() << " " << expl2.isSet() << std::endl;
            std::cout << _prop.getFloat() << " " << expl2.getFloat() << std::endl;
            if (_prop.hasPrefab())
            {
                ENTLIB_ASSERT(expl2.hasPrefab());
                ENTLIB_ASSERT(_prop.getPrefab()->getRawJson() == expl2.getPrefab()->getRawJson());
            }
        }
        ENTLIB_ASSERT(_prop.getFloat() == expl2.getFloat());
    }
    void stringProperty([[maybe_unused]] Property const& _prop) override
    {
        ENTLIB_ASSERT(_prop.isSet() == expl2.isSet());
        ENTLIB_ASSERT(_prop.getString() == std::string_view(expl2.getString()));
    }
    void entityRefProperty([[maybe_unused]] Property const& _prop) override
    {
        ENTLIB_ASSERT(_prop.isSet() == expl2.isSet());
        ENTLIB_ASSERT(_prop.getEntityRef() == expl2.getEntityRef());
    }
};

class PrimitiveCounterVisitor : public RecursiveVisitor
{
public:
    size_t primitiveCount = 0;

    void key([[maybe_unused]] Property const& _prop, [[maybe_unused]] char const* _key) override
    {
        ++primitiveCount;
    }
    void key([[maybe_unused]] Property const& _prop, [[maybe_unused]] int64_t _key) override
    {
        ++primitiveCount;
    }
    void boolProperty([[maybe_unused]] Property const& _prop) override
    {
        ++primitiveCount;
    }
    void intProperty([[maybe_unused]] Property const& _prop) override
    {
        ++primitiveCount;
    }
    void floatProperty([[maybe_unused]] Property const& _prop) override
    {
        ++primitiveCount;
    }
    void stringProperty([[maybe_unused]] Property const& _prop) override
    {
        ++primitiveCount;
    }
    void entityRefProperty([[maybe_unused]] Property const& _prop) override
    {
        ++primitiveCount;
    }
};

TEST_CASE("Test Properties2", "[all2]")
{
    std::filesystem::path rawdataPath = ".";
    std::filesystem::path schemaPath = "../build/Schemas";

    EntityLib entlib(rawdataPath, schemaPath);

    SECTION("Create Property from empty json")
    {
        auto storage = nlohmann::json::object();
        Property entity(&entlib, entlib.getEntitySchema(), nullptr, &storage, nullptr);
        auto name = entity.getObjectField("Name");
        name.setString("Debug Quick Creatures Switch");
    }
    SECTION("Create Property from json")
    {
        auto d = loadJsonFile(std::filesystem::current_path(), "test.SeedPatch.node");
        auto const& schema = d["$schema"].get_ref<nlohmann::json::string_t const&>();
        auto typeName = std::string(getRefTypeName(schema.c_str()));
        Property simpleObject(
            &entlib, entlib.getSchema(typeName.c_str()), "test.SeedPatch.node", &d, nullptr);
        ENTLIB_ASSERT(simpleObject.getObjectField("NoiseSizeX").getFloat() == 1.f);
        ENTLIB_ASSERT(simpleObject.getObjectField("NoiseSizeY").getFloat() == 2.f);
        simpleObject.getObjectField("NoiseSizeX").setFloat(2.);
        ENTLIB_ASSERT(simpleObject.getObjectField("NoiseSizeX").getFloat() == 2.);
    }
    SECTION("Chained get")
    {
        Property expl = entlib.loadPropertyCopy("Entity", "prefab.entity");
        ENTLIB_ASSERT(expl.getObjectField("Name").getString() == std::string("PlayerSpawner_"));
        {
            ENTLIB_ASSERT(
                expl.getObjectField("Components")
                    .getUnionSetItem("NetworkNode")
                    ->getObjectField("Type")
                    .getString()
                == std::string("Spawner"));
        }
        auto posX = expl.getObjectField("Components")
                        .getUnionSetItem("TransformGD")
                        ->getObjectField("Position")
                        .getArrayItem(0llu);
        ENTLIB_ASSERT(posX.getFloat() == 105.2244);
        auto& entityRung = expl;
        auto floatA = entityRung.getObjectField("Components")
                          .getUnionSetItem("TransformGD")
                          ->getObjectField("Position")
                          .getArrayItem(0llu)
                          .getFloat();
        auto floatB = entityRung.getObjectField("Components")
                          .getUnionSetItem("TransformGD")
                          ->getObjectField("Position")
                          .getArrayItem(0llu)
                          .getFloat();
        ENTLIB_ASSERT(floatA == 105.2244);
        ENTLIB_ASSERT(floatB == 105.2244);

        ENTLIB_ASSERT(
            expl.getObjectField("Components")
                .getUnionSetItem("SubScene")
                ->getObjectField("Embedded")
                .getObjectSetItem("EP1-Spout_LINK_001")
                ->getObjectField("Name")
                .getString()
            == std::string("EP1-Spout_LINK_001"));
    }
    SECTION("More chained get")
    {
        Property expl = entlib.loadPropertyCopy("Entity", "instance.entity");
        ENTLIB_ASSERT(expl.getObjectField("Name").getString() == std::string("PlayerSpawner_"));
        auto type =
            expl.getObjectField("Components").getUnionSetItem("NetworkNode")->getObjectField("Type");
        ENTLIB_ASSERT(
            expl.getObjectField("Components").getUnionSetItem("NetworkNode")->getObjectField("Type").getString()
            == std::string("Spawner"));
        auto pos2 = expl.getObjectField("Components")
                        .getUnionSetItem("TransformGD")
                        ->getObjectField("Position")
                        .getArrayItem(2llu)
                        .getFloat();
        ENTLIB_ASSERT(fabs(pos2 - 29.6635) < std::numeric_limits<float>::epsilon());
        ENTLIB_ASSERT(
            expl.getObjectField("Components")
                .getUnionSetItem("SubScene")
                ->getObjectField("Embedded")
                .getObjectSetItem("EP1-Spout_LINK_001")
                ->getObjectField("Name")
                .getString()
            == std::string("EP1-Spout_LINK_001"));
        ENTLIB_ASSERT(
            expl.getObjectField("ActorStates")
                .getUnionSetItem("ActorStateHoldingItem")
                ->getObjectField("ItemEntityRef")
                .getEntityRef()
                .entityPath
            == std::string("tutu"));
        auto components = expl.getObjectField("Components");
        auto ori3 =
            components.getUnionSetItem("TransformGD")->getObjectField("Orientation").getArrayItem(3llu);
        ENTLIB_ASSERT(
            fabs(ori3.getFloat() - 0.9916236400604248) < std::numeric_limits<float>::epsilon());
        ori3.setFloat(2.);
        ENTLIB_ASSERT(ori3.getFloat() == 2.);
        auto soundAreaGD =
            expl.getObjectField("Components").forceGetUnionSetItem("SoundAreaGD").first;
        ENTLIB_ASSERT(soundAreaGD.isSet() == false);
        ENTLIB_ASSERT(soundAreaGD.isDefault() == true);
        auto keys = components.getUnionSetKeysString();
        keys = components.getUnionSetKeysString();

        expl.save("instance.prout.entity");
        // Must not crash
        Property prefab2(&entlib, entlib.getSchema(entitySchemaName), "instance.prout.entity");
        auto comp2 = prefab2.getObjectField("Components");
        auto characterControllerGD = *comp2.getUnionSetItem("CharacterControllerGD");
        auto clamberData = characterControllerGD.getObjectField("ClamberData");
        auto vertOriRatio = clamberData.getObjectField("VerticalOrientationRatio");
        auto in = vertOriRatio.getObjectField("in");
        auto in0 = in.getArrayItem(0);
        in0.setFloat(3.33);
    }
    SECTION("CopyProperty")
    {
        Property expl(&entlib, entlib.getSchema(entitySchemaName), "instance.entity");

        nlohmann::json newDoc = nlohmann::json::object();
        Property destExpl(&entlib, expl.getSchema(), "", &newDoc, nullptr);
        CopyProperty copier(
            destExpl, OverrideValueSource::OverrideOrPrefab, CopyMode::CopyOverride, true);
        visitRecursive(expl, copier);
        entlib.saveJsonFile(&newDoc, "instance.cursor.entity", "Entity");

        // test SearchProperty
        auto pattern = "eMbeDdEd";
        SearchProperty searcher(pattern);
        visitRecursive(expl, searcher);
        auto matching = searcher.getMatchingProperties();
        ENTLIB_ASSERT(matching.size() == 1);
    }
}
