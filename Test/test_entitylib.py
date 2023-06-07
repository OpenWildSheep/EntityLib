import os
import subprocess
import traceback
import logging
import sys
from math import fabs

entitylib_path = "../x64/Release-3.7"
if "PYTHONPATH" in os.environ:
    os.environ["PYTHONPATH"] += "" + entitylib_path
else:
    os.environ["PYTHONPATH"] = entitylib_path

sys.path.append(entitylib_path)

import EntityLibPy as Ent
from entgen.inline import *


def displaySubSchema(name: str, subschema: Ent.Subschema, indent: str):
    if len(indent) > 80:
        return
    sys.stdout.write("{}{} : ".format(indent, name))
    type = subschema.type
    defval = "def:" + str(subschema.default_value) if subschema.default_value else ""
    constval = "const:" + str(subschema.const_value) if subschema.const_value else ""
    if type == Ent.DataType.array:
        sys.stdout.write("array\n")
        if subschema.min_items != 0:
            sys.stdout.write("{}  minItems: {}\n".format(indent, subschema.min_items))
        if subschema.max_items != 18446744073709551615:
            sys.stdout.write("{}  maxItems: {}\n".format(indent, subschema.max_items))
        if subschema.has_singular_items():
            displaySubSchema("items", subschema.get_singular_items().get(), indent + "  ")
        if subschema.has_linear_items():
            for item in subschema.get_linear_items():
                displaySubSchema("items", item.get(), indent + "  ")
    if type == Ent.DataType.boolean:
        sys.stdout.write("boolean {} {}\n".format(defval, constval))
    if type == Ent.DataType.integer:
        sys.stdout.write("integer {} {}\n".format(defval, constval))
    if type == Ent.DataType.null:
        sys.stdout.write("null {} {}\n".format(defval, constval))
    if type == Ent.DataType.number:
        sys.stdout.write("number {} {}\n".format(defval, constval))
    if type == Ent.DataType.object:
        sys.stdout.write("object\n")
        for name, sub in subschema.properties.items():
            displaySubSchema(name, sub.get(), indent + "  ")
    if type == Ent.DataType.string:
        sys.stdout.write("string {} {}\n".format(defval, constval))


logfile = logging.getLogger()
try:
    logfile.setLevel(logging.DEBUG)
    streamHandler = logging.StreamHandler(sys.stdout)
    logfile.addHandler(streamHandler)

    print(Ent.__doc__)
    help(Ent)

    entlib = Ent.EntityLib("X:/")

    entlib.rawdata_path = os.getcwd()

    entlib.validation_enabled = True

    ####################################################################################################################
    # Test Property
    expl = Ent.Property(entlib, entlib.get_schema(Entity.schema_name), "instance.entity")
    assert(expl.get_object_field("Name").value == "PlayerSpawner_")
    assert(expl
           .get_object_field("Components")
           .get_unionset_item("NetworkNode")
           .get_object_field("Type")
           .value == "Spawner")
    posX = expl\
        .get_object_field("Components")\
        .get_unionset_item("TransformGD")\
        .get_object_field("Position")\
        .get_array_item(0)
    print(posX.value)
    assert(posX.value == 105.2244)
    floatA = expl\
        .get_object_field("Components")\
        .get_unionset_item("TransformGD")\
        .get_object_field("Position")\
        .get_array_item(0)\
        .get_float()
    floatB = expl\
        .get_object_field("Components")\
        .get_unionset_item("TransformGD")\
        .get_object_field("Position")\
        .get_array_item(0)\
        .get_float()
    assert(floatA == 105.2244);
    assert(floatB == 105.2244);

    assert(expl
           .get_object_field("Components")
           .get_unionset_item("SubScene")
           .get_object_field("Embedded")
           .get_objectset_item("EP1-Spout_LINK_001")
           .get_object_field("Name")
           .value
           == "EP1-Spout_LINK_001")

    ####################################################################################################################
    # Test $ref links in entlib.schema.schema.allDefinitions
    colorRef = "Color"
    assert colorRef in entlib.schema.schema.definitions

    # Check Ent.Subschema.getUnionTypesMap
    cinematicGDRef = "CinematicGD"
    cinematicGDSchema = entlib.schema.schema.definitions[cinematicGDRef]
    scriptEventUnionSchema = cinematicGDSchema.properties["ScriptEvents"].get().get_singular_items().get()
    nameToTypeMap = scriptEventUnionSchema.get_union_types_dict()
    assert len(nameToTypeMap) == 9
    assert "CineEventTestCurrentGameState" in nameToTypeMap
    assert "CineEventTriggerEventHandlerPost" in nameToTypeMap
    assert "CineEventTestEndCurrentSequence" in nameToTypeMap

    # Ensure that all components have a ref and is in entlib.schema.schema.allDefinitions
    for name, schema in entlib.schema.components.items():
        absRef = schema.name
        assert absRef.find("./") == -1
        assert absRef.find("#") == -1
        assert absRef in entlib.schema.schema.definitions

    ####################################################################################################################
    PrefabSubEntityCount = 5

    def testPrefabEntity(ent: Ent.Node):
        # ActorStates
        actorStates = ent.at("ActorStates")
        assert(actorStates.datatype == Ent.DataType.array)
        assert(actorStates.size() == 2)
        actorState = actorStates.at(0)
        assert(actorState != None)
        assert actorState.get_schema().get_union_name_field() == "className"
        assert actorState.get_schema().get_union_data_field() == "classData"
        climbEdge = actorState.get_union_data()
        assert(climbEdge != None)
        actorState2 = actorStates.at(1)
        assert(actorState2 != None)
        cinematic = actorState2.get_union_data()
        assert(cinematic != None)

        # Map and Set overridePolicy
        pathNodeGD = ent.at("Components").map_get("TestTagsList").get_union_data()
        tags = pathNodeGD.at("Tags").at("Tags")
        assert(tags.size() == 3)
        assert(tags.at(0).at(0).get_string() == "a")
        assert(tags.at(1).at(0).get_string() == "c")
        assert(tags.at(1).at(1).size() == 1)
        assert(tags.at(1).at(1).at(0).get_string() == "2")

        # Test mapGet on map and set
        assert(tags.map_get("a").map_get("1").value == "1")

        assert(tags.get_key_type() == Ent.DataType.string)
        keys = tags.get_keys()
        assert(len(keys) == 3)
        for k in keys:
            assert tags.map_get(k) is not None

        # Test default value
        voxelSimulationGD = ent.at("Components").map_get("VoxelSimulationGD").get_union_data()
        assert(voxelSimulationGD.at("TransmissionBySecond").value == 3.402823466385289e+38)
        assert(voxelSimulationGD.at("TransmissionBySecond").is_default())
        assert(voxelSimulationGD.get_type_name() == "VoxelSimulationGD")

        # TEST read inherited values in inherited component
        heightObj = ent.at("Components").map_get("HeightObj").get_union_data()
        assert(heightObj is not None)
        assert(heightObj.at("Subdivision").value == 0)
        assert(heightObj.at("Subdivision").is_set())
        assert(
            heightObj.at("DisplaceNoiseList").at(0).at("MapChannel").value == 51248)
        assert(heightObj.at("DisplaceNoiseList").at(0).at("MapChannel").is_set())
        assert heightObj.at("Subdivision").get_schema().user_meta["testUserMetatdata"] is 42

        # Test read Thumbnail
        assert(ent.at("Thumbnail").value is not None)
        assert(ent.at("Thumbnail").value == "TestThumbnail")

        # Test read prefab
        sysCreat = ent.at("Components").map_get("SystemicCreature").get_union_data()
        assert(sysCreat is not None)

        # TEST read setted values
        assert(sysCreat.at("Faction").value == "Shamans") # set
        assert(sysCreat.at("Faction").is_set()) # is set
        assert(sysCreat.at("Inventory").value == "KaiWOLgrey") # set
        assert(sysCreat.at("Inventory").is_set()) # is set

        # TEST comment
        assert sysCreat.at("BehaviorState").get_string() == "W/*at*/c//h"

        # TEST read array
        assert(sysCreat.at("ScriptList").is_set())
        assert(sysCreat.at("ScriptList").size() == 3)

        # TEST default values
        assert(sysCreat.at("Burried").value == False) # default
        assert(not sysCreat.at("Burried").is_set()) # default
        assert(sysCreat.at("Name").value == "") # default
        assert(not sysCreat.at("Name").is_set()) # default

        # TEST SubScene
        subScenecomp = ent.at("Components").map_get("SubScene").get_union_data()
        allSubEntities = subScenecomp.at("Embedded")
        assert(len(allSubEntities) == PrefabSubEntityCount)
        assert(allSubEntities[0].at("Name").value == "EP1-Spout_LINK_001")
        assert(allSubEntities[0].at("Color")[0].value == 255)

        # TEST union
        cinematicGD = ent.at("Components").map_get("CinematicGD").get_union_data()  # type: Ent.Component
        scriptEvents = cinematicGD.at("ScriptEvents")  # type: Ent.Node
        assert(scriptEvents.datatype == Ent.DataType.array)

        # Read Union type
        oneOfScripts = scriptEvents.at(0)  # type: Ent.Node
        assert(oneOfScripts.datatype == Ent.DataType.union)
        cineEvent = oneOfScripts.get_union_data()  # type: Ent.Node
        assert(cineEvent.get_type_name() == "CineEventTriggerEventHandlerPost")

        nbEnt = cineEvent.at("EventName")  # type: Ent.Node
        assert(nbEnt is not None)
        assert(nbEnt.datatype == Ent.DataType.string)
        assert(nbEnt.value == "Toto")

        # TEST sub - object with non - default values
        ldprimitive = ent.at("Components").map_get("LDPrimitive").get_union_data()  # type: Ent.Component
        primitiveData = ldprimitive.at("PrimitiveData")  # type: Ent.Node
        assert(primitiveData.at("Height").value == 42.)

    ####################################################################################################################
    # Test the readOnly prefab.entity
    ent = entlib.load_node_entity_read_only("prefab.entity")  # type: Ent.Node
    testPrefabEntity(ent)

    ####################################################################################################################
    node_cache_size = len(entlib.get_node_cache())
    ent = entlib.load_node_entity("prefab.copy.entity")
    assert len(entlib.get_node_cache()) == node_cache_size + 1
    # TEST simple entity refs resolution
    testEntityRef = ent.at("Components").map_get("TestEntityRef").get_union_data()
    assert testEntityRef is not None
    assert testEntityRef.at("TestRef").is_set()
    entityRef = testEntityRef.at("TestRef").get_entityref()
    resolvedEntity = entlib.resolve_entityref(ent, entityRef)
    assert resolvedEntity is not None

    subScenecomp = ent.at("Components").map_get("SubScene").get_union_data()
    allSubEntities = subScenecomp.at("Embedded")
    assert not allSubEntities.empty()
    originalEnt = allSubEntities.at(0)
    assert resolvedEntity == originalEnt

    ####################################################################################################################
    ent = entlib.load_node_entity("prefab.entity")  # type: Ent.Node

    testPrefabEntity(ent)

    # Set Union type
    cinematicGD = ent.at("Components").map_get("CinematicGD").get_union_data()  # type: Ent.Component
    scriptEvents = cinematicGD.at("ScriptEvents")  # type: Ent.Node
    oneOfScripts2 = scriptEvents.at(1)  # type: Ent.Node
    assert(oneOfScripts2.datatype == Ent.DataType.union)
    assert(oneOfScripts2.get_union_type() == "CineEventTriggerEventHandlerPost")
    oneOfScripts2.set_union_type("CineEventTestCurrentGameState")
    testCurrentState = oneOfScripts2.get_union_data()  # type: Ent.Node
    assert(oneOfScripts2.get_union_type() == "CineEventTestCurrentGameState")
    fieldNames2 = testCurrentState.get_field_names()
    assert(fieldNames2[0] == "GameStateName")
    assert(fieldNames2[1] == "Super")
    testCurrentState.at("GameStateName").set_string("Pouet!")

    # Set Union type without override
    oneOfScripts3 = scriptEvents.at(2)
    assert(oneOfScripts3.datatype == Ent.DataType.union)
    assert(oneOfScripts3.get_union_type() == "CineEventTriggerEventHandlerPost")
    oneOfScripts3.set_union_type("CineEventTestCurrentGameState")

    # Push in an array of Union
    oneOfScripts4 = scriptEvents.push()
    assert(oneOfScripts4.datatype == Ent.DataType.union)
    assert(oneOfScripts4.get_union_type() == "CineEventTestCurrentGameState")
    assert(scriptEvents.at(3) == oneOfScripts4)

    # TEST simple entity ref creation
    testEntityRef = ent.at("Components").map_insert("TestEntityRef").get_union_data()
    assert(testEntityRef is not None)
    assert(testEntityRef.at("TestRef").get_entityref().entity_path == "")  # value                             ????
    testEntityRef.at("TestRef").set_entityref(entlib.make_entityref(ent, ent))
    assert(testEntityRef.at("TestRef").get_entityref().entity_path == ".")
    subScenecomp = ent.at("Components").map_get("SubScene").get_union_data()
    allSubEntities = subScenecomp.at("Embedded")
    subent = allSubEntities[0]
    ref = entlib.make_entityref(ent, subent)
    testEntityRef.at("TestRef").value = ref

    # TEST MaxActivationLevel
    ent.at("MaxActivationLevel").value = "InWorld"

    sysCreat = ent.at("Components").map_get("SystemicCreature").get_union_data()
    sysCreat.at("Name").value = "Shamane_male"
    ent.save_node("prefab.copy.entity")

    ####################################################################################################################
    # Test write prefab
    ent = entlib.load_node_entity("prefab.copy.entity")

    # TEST read inherited values in inherited component
    heightObj = ent.at("Components").map_get("HeightObj").get_union_data()
    assert(heightObj is not None)
    assert(heightObj.at("Subdivision").value == 0)
    assert(heightObj.at("Subdivision").is_set())
    assert(
        heightObj.at("DisplaceNoiseList").at(0).at("MapChannel").value == 51248)
    assert(heightObj.at("DisplaceNoiseList").at(0).at("MapChannel").is_set())

    sysCreat = ent.at("Components").map_get("SystemicCreature").get_union_data()
    assert(sysCreat is not None)
    # TEST read setted values
    assert(sysCreat.at("Faction").value == "Shamans") # set
    assert(sysCreat.at("Inventory").value == "KaiWOLgrey") # set

    # TEST read array
    assert(sysCreat.at("ScriptList").is_set())
    assert(sysCreat.at("ScriptList").size() == 3)

    # TEST default values unchanged
    assert(sysCreat.at("Burried").value is False) # default
    assert(not sysCreat.at("Burried").is_set()) # default

    # TEST changed values
    assert(
        sysCreat.at("Name").value == "Shamane_male") # set. changed.
    assert(sysCreat.at("Name").is_set()) # set. changed.

    # TEST simple entity refs resolution
    testEntityRef = ent.at("Components").map_get("TestEntityRef").get_union_data()
    assert(testEntityRef is not None)
    assert(testEntityRef.at("TestRef").is_set())
    entityRef = testEntityRef.at("TestRef").get_entityref()
    val = testEntityRef.at("TestRef").value
    assert entityRef.entity_path == val.entity_path
    resolvedEntity = entlib.resolve_entityref(ent, entityRef)
    assert(resolvedEntity is not None)

    subScenecomp = ent.at("Components").map_get("SubScene").get_union_data()
    allSubEntities = subScenecomp.at("Embedded")
    assert(len(allSubEntities) == PrefabSubEntityCount)
    originalEnt = allSubEntities[0]
    assert(resolvedEntity is originalEnt)

    ####################################################################################################################
    
    """
    # TEST entity refs
    # file: entity-references-a.entity
    # - A-entity [ref to B: "B"]
    #     - B [ref to A: ".."]
    #
    # file: entity-references.scene
    # - root-scene
    #     - InstanceOfA
    #     - C [ref to B in InstanceOfA: "../InstanceOfA/B"]
    #
    """
    scene = entlib.load_node_scene("entity-references.scene")
    assert(len(scene) == 2)
    instanceOfA = scene.map_get("InstanceOfA")
    assert(instanceOfA.at("Name").value == "InstanceOfA")
    subSceneComp = instanceOfA.at("Components").map_get("SubScene").get_union_data()  # type: Ent.SubSceneComponent
    assert(subSceneComp is not None)
    assert(len(subSceneComp.at("Embedded")) == 1)
    B = subSceneComp.at("Embedded").at(0)
    assert(B.at("Name").value == "B")
    C = scene.map_get("C")
    assert(C.at("Name").value == "C")

    # TEST entity ref creation
    BToInstanceOfAref = entlib.make_entityref(B, instanceOfA)
    assert(BToInstanceOfAref.entity_path == "..")
    InstanceOfAToBref = entlib.make_entityref(instanceOfA, B)
    assert(InstanceOfAToBref.entity_path == "B")
    CToBref = entlib.make_entityref(C, B)
    assert(CToBref.entity_path == "../InstanceOfA/B")
    BToCref = entlib.make_entityref(B, C)
    assert(BToCref.entity_path == "../../C")

    # TEST entity ref resolution
    resolvedEmptyRef = entlib.resolve_entityref(instanceOfA, Ent.EntityRef())
    assert(resolvedEmptyRef is None)
    resolvedInstanceOfA = entlib.resolve_entityref(B, Ent.EntityRef(".."))
    assert(resolvedInstanceOfA is instanceOfA)
    resolvedB = entlib.resolve_entityref(instanceOfA, Ent.EntityRef("B"))
    assert(resolvedB is B)
    resolvedBbis = entlib.resolve_entityref(C, Ent.EntityRef("../InstanceOfA/B"))
    assert(resolvedBbis is B)
    resolvedC = entlib.resolve_entityref(B, Ent.EntityRef("../../C"))
    assert(resolvedC is C)

    # TEST entity ref resolution from scenes
    assert(entlib.resolve_entityref(scene, Ent.EntityRef("..")) is None)
    assert(entlib.resolve_entityref(scene, Ent.EntityRef("InstanceOfA")) is instanceOfA)
    assert(entlib.resolve_entityref(scene, Ent.EntityRef("InstanceOfA/B")) is B)
    assert(entlib.resolve_entityref(scene, Ent.EntityRef("C")) is C)
    assert(entlib.resolve_entityref(scene, Ent.EntityRef("InstanceOfA/B/../../C")) is C)

    ####################################################################################################################
    def testInstanceOf(ent: Ent.Node):
        # ActorStates
        actorStates = ent.at("ActorStates")
        assert(actorStates.datatype == Ent.DataType.array)
        assert(actorStates.size() == 3)
        actorState = actorStates.at(0)
        assert(actorState is not None)
        climbEdge = actorState.get_union_data()
        assert(climbEdge is not None)
        actorState2 = actorStates.at(1)
        assert(actorState2 is not None)
        cinematic = actorState2.get_union_data()
        assert(cinematic is not None)
        actorState3 = actorStates.at(2)
        assert(actorState3 is not None)
        chosen = actorState3.get_union_data()
        assert(chosen is not None)

        # Map and Set overridePolicy
        pathNodeGD = ent.at("Components").map_get("TestTagsList").get_union_data()
        tags = pathNodeGD.at("Tags").at("Tags")
        assert(tags.size() == 3)
        assert(tags.at(0).at(0).get_string() == "a")
        assert(tags.at(1).at(0).get_string() == "b")
        assert(tags.at(2).at(0).get_string() == "c")
        assert(tags.at(2).at(1).size() == 3)
        assert(tags.at(2).at(1).at(0).get_string() == "1")
        assert(tags.at(2).at(1).at(1).get_string() == "2")
        assert(tags.at(2).at(1).at(2).get_string() == "3")

        # TEST SubScene (without override)
        subScene = ent.at("Components").map_get("SubScene").get_union_data()  # type: Ent.SubSceneComponent
        assert(subScene is not None)
        subObj = subScene.at("Embedded").at(0)  # type: Ent.Node
        assert(subObj.at("Name").value == "EP1-Spout_LINK_001")
        assert(not subObj.has_override())
        netLink = subObj.at("Components").map_get("NetworkLink").get_union_data()
        assert(netLink is not None)
        assert(netLink.at("Source").value == ".EP1-Spout_")
        assert(not netLink.at("Source").is_set())
        assert(netLink.at("Target").value == ".EP1-crook_")
        assert(not netLink.at("Target").is_set())
        trans = subObj.at("Components").map_get("TransformGD").get_union_data()
        assert(trans.at("Position").at(0).value == 0.0)
        
        # Test instanciation of a template Node
        stickToTerrain = ent.at("Components").map_get("StickToTerrain").get_union_data()
        assert(fabs(stickToTerrain.at("NormalRatio").get_float() - 0.6) < 0.0001)
        assert(stickToTerrain.at("ZOffset").is_set() is False)
        assert(stickToTerrain.at("ZOffset").is_default() is False)
        assert(fabs(stickToTerrain.at("ZOffset").get_float() - 10.) < 0.0001)

    # Test read instance of
    ent = entlib.load_node_entity("instance.entity")
    sysCreat = ent.at("Components").map_get("SystemicCreature").get_union_data()
    assert(sysCreat is not None)

    # TEST read overrided value
    assert(sysCreat.at("Faction").value == "Plouf")  # Overrided

    # TEST read inherited values
    assert(
        sysCreat.at("Inventory").value == "KaiWOLgrey")  # Inherited
    assert(sysCreat.at("Life").value == 1000.)  # Inherited

    # TEST read inherited values in inherited component
    heightObj = ent.at("Components").map_get("HeightObj").get_union_data()
    assert(heightObj is not None)
    assert(heightObj.at("Subdivision").value == 0)
    assert(not heightObj.at("Subdivision").is_set())
    assert(
        heightObj.at("DisplaceNoiseList").at(0).at("MapChannel").value == 51248)
    assert(
        not heightObj.at("DisplaceNoiseList").at(0).at("MapChannel").is_set())

    # TEST read default value
    assert(sysCreat.at("Burried").value is False)  # Inherited (from default)
    assert(not sysCreat.at("Burried").is_set())  # default

    # TEST read overrided in array
    assert(
        sysCreat.at("ScriptList").at(1).value == "b2")  # Overrided
    assert(sysCreat.at("ScriptList").at(1).is_set())  # Overrided
    # TEST read Not overrided in array
    assert(
        sysCreat.at("ScriptList").at(2).value == "c1")  # not overrided
    assert(not sysCreat.at("ScriptList").at(2).is_set())  # Not overrided

    # Programatically unset
    sysCreat.at("ScriptList").at(1).unset()
    # Programatically set
    sysCreat.at("ScriptList").at(2).value = "c2"

    # TEST read array
    assert(sysCreat.at("ScriptList").is_set())
    assert(sysCreat.at("ScriptList").size() == 3)

    # TEST Extand array
    sysCreat.at("ScriptList").push().value = "d2"
    assert(sysCreat.at("ScriptList").size() == 4)

    # TEST SubScene(without override)
    testInstanceOf(ent)

    sysCreat.at("BehaviorState").value = "Overrided"
    ent.save_node("instance.copy.entity")

    ####################################################################################################################
    
    def testInstanceOverrideSubscene(ent: Ent.Node):
        # TEST SubScene (with override)
        subScene = ent.at("Components").map_get("SubScene").get_union_data()
        assert(subScene is not None)
        subObj = subScene.at("Embedded")[0]
        assert(subObj.at("Name").value == "EP1-Spout_LINK_001")

        parent = subObj.parent_node.parent_node.parent_node.parent_node.parent_node.parent_node
        subObj2 = parent.at("Components").map_get("SubScene").get_union_data().at("Embedded").at(0)
        assert subObj2 is subObj
        subObj3 = entlib.get_parent_entity(subObj)
        assert subObj3 is not None
        assert subObj3 is parent

        # Test an overrided Component
        netLink = subObj.at("Components").map_get("NetworkLink").get_union_data()
        assert(netLink is not None)
        assert(netLink.at("Source").value == ".EP1-Spout_")
        assert(not netLink.at("Source").is_set())
        assert(netLink.at("Target").value == ".EP1-crook_2")
        assert(netLink.at("Target").is_set())

        # Test a not overrided Component
        trans = subObj.at("Components").map_get("TransformGD").get_union_data()
        assert(trans is not None)
        assert(trans.at("Position").at(0).value == 0.0)

    ####################################################################################################################
    ent = entlib.load_node_entity("instance_override_subscene.entity")
    testInstanceOverrideSubscene(ent)
    ent.save_node("instance_override_subscene.copy.entity")

    ####################################################################################################################
    ent = entlib.load_node_entity("instance_override_subscene.copy.entity")
    testInstanceOverrideSubscene(ent)

    # Test write instance of
    ent = entlib.load_node_entity("instance.copy.entity")
    sysCreat = ent.at("Components").map_get("SystemicCreature").get_union_data()
    assert(sysCreat is not None)

    # TEST read inherited values in inherited component
    heightObj = ent.at("Components").map_get("HeightObj").get_union_data()
    assert(heightObj is not None)
    assert(heightObj.at("Subdivision").value == 0)
    assert(not heightObj.at("Subdivision").is_set())
    assert(
        heightObj.at("DisplaceNoiseList").at(0).at("MapChannel").value == 51248)
    assert(
        not heightObj.at("DisplaceNoiseList").at(0).at("MapChannel").is_set())

    # TEST read overrided value
    assert(sysCreat.at("Faction").value == "Plouf")  # Overrided

    # TEST read inherited values
    assert(
        sysCreat.at("Inventory").value == "KaiWOLgrey")  # Inherited
    assert(sysCreat.at("Life").value == 1000.)  # Inherited

    # TEST read default value
    assert(sysCreat.at("Burried").value == False)  # Inherited (from default)
    assert(not sysCreat.at("Burried").is_set())  # default

    # TEST read programatically overrided in array
    assert(
        sysCreat.at("ScriptList").at(1).value == "b1")  # No more overrided
    assert(not sysCreat.at("ScriptList").at(1).is_set())  # No more overrided
    # TEST read programatically unset in array
    assert(
        sysCreat.at("ScriptList").at(2).value == "c2")  # Overrided
    assert(sysCreat.at("ScriptList").at(2).is_set())  # Overrided

    # TEST read programatically extand array
    assert(
        sysCreat.at("ScriptList").at(3).value == "d2")  # Overrided
    assert(sysCreat.at("ScriptList").at(3).is_set())  # Overrided

    # TEST read extanded array
    assert(sysCreat.at("ScriptList").is_set())
    assert(sysCreat.at("ScriptList").size() == 4)

    # TEST override value from code
    assert(
        sysCreat.at("BehaviorState").value == "Overrided")  # set. changed.
    assert(sysCreat.at("BehaviorState").is_set())  # set. changed.

    testInstanceOf(ent)

    ent.save_node("instance.copy.entity")

    ####################################################################################################################
    # Test create detached
    ent = entlib.load_node_entity("instance.entity")
    detached = ent.detach()

    sysCreat = detached.at("Components").map_get("SystemicCreature").get_union_data()
    assert(sysCreat is not None)

    # TEST read inherited values in inherited component
    heightObj = ent.at("Components").map_get("HeightObj").get_union_data()
    assert(heightObj is not None)
    assert(heightObj.at("Subdivision").value == 0)
    assert(not heightObj.at("Subdivision").is_set())
    assert(
        heightObj.at("DisplaceNoiseList").at(0).at("MapChannel").value == 51248)
    assert(
        not heightObj.at("DisplaceNoiseList").at(0).at("MapChannel").is_set())

    # TEST default values
    assert(sysCreat.at("Burried").value is False)  # default
    assert(not sysCreat.at("Burried").is_set())  # default
    assert(sysCreat.at("Name").value == "")  # default
    assert(not sysCreat.at("Name").is_set())  # default

    # TEST read setted values
    assert(sysCreat.at("Faction").value == "Plouf")  # set
    assert(sysCreat.at("Faction").is_set())  # is set
    assert(sysCreat.at("Inventory").value == "KaiWOLgrey")  # set
    assert(sysCreat.at("Inventory").is_set())  # is set

    detached.save_node("instance.detached.entity")

    ####################################################################################################################
    # Test read detached
    ent = entlib.load_node_entity("instance.detached.entity")

    sysCreat = ent.at("Components").map_get("SystemicCreature").get_union_data()

    # TEST read inherited values in inherited component
    heightObj = ent.at("Components").map_get("HeightObj").get_union_data()
    assert(heightObj is not None)
    assert(heightObj.at("Subdivision").value == 0)
    assert(heightObj.at("Subdivision").is_set())
    assert(
        heightObj.at("DisplaceNoiseList").at(0).at("MapChannel").value == 51248)
    assert(heightObj.at("DisplaceNoiseList").at(0).at("MapChannel").is_set())

    # TEST default values
    assert(sysCreat.at("Burried").value is False)  # default
    assert(not sysCreat.at("Burried").is_set())  # default
    assert(sysCreat.at("Name").value == "")  # default
    assert(not sysCreat.at("Name").is_set())  # default

    # TEST read setted values
    assert(sysCreat.at("Faction").value == "Plouf")  # set
    assert(sysCreat.at("Faction").is_set())  # is set
    assert(sysCreat.at("Inventory").value == "KaiWOLgrey")  # set
    assert(sysCreat.at("Inventory").is_set())  # is set

    ####################################################################################################################
    # Test make_instance_of
    instanceOf = entlib.make_entity_node_instanceof("prefab.entity")
    assert instanceOf.get_instance_of() == "prefab.entity"

    # Test instanciation of a template Node
    stickToTerrain = instanceOf.at("Components").map_insert("StickToTerrain").get_union_data()
    stickToTerrain.set_instance_of("test.StickToTerrain.node", )
    assert(stickToTerrain.get_instance_of() is not None)
    stickToTerrain.at("NormalRatio").set_float(0.6)

    assert(fabs(stickToTerrain.at("NormalRatio").get_float() - 0.6) < 0.0001)
    assert(stickToTerrain.at("ZOffset").is_set() is False)
    assert(stickToTerrain.at("ZOffset").is_default() is False)
    assert(fabs(stickToTerrain.at("ZOffset").get_float() - 10.) < 0.0001)

    assert(instanceOf.at("Components").map_get("NetworkNode").get_union_data() is not None)
    instanceOf.at("Components").map_get("TransformGD").get_union_data().get_field_names()
    instanceOf.save_node("instance.create.entity")

    ####################################################################################################################
    def testCreateInstanceOf(_instancePath):
        # Test read instance of
        ent = entlib.load_node_entity(_instancePath)

        ent.at("Components").map_get("TransformGD").get_union_data().get_field_names()

        # Test instanciation of a template Node
        stickToTerrain = ent.at("Components").map_get("StickToTerrain").get_union_data()
        assert(stickToTerrain.get_instance_of() is not None)
        assert(fabs(stickToTerrain.at("NormalRatio").get_float() - 0.6) < 0.0001)
        assert(stickToTerrain.at("ZOffset").is_set() is False)
        assert(stickToTerrain.at("ZOffset").is_default() is False)
        assert(fabs(stickToTerrain.at("ZOffset").get_float() - 10.) < 0.0001)

        # TEST read inherited values in inherited component
        heightObj = ent.at("Components").map_get("HeightObj").get_union_data()
        assert(heightObj is not None)
        assert(heightObj.at("Subdivision").value == 0)
        assert(not heightObj.at("Subdivision").is_set())
        assert(
            heightObj.at("DisplaceNoiseList").at(0).at("MapChannel").value == 51248)
        assert(
            not heightObj.at("DisplaceNoiseList").at(0).at("MapChannel").is_set())

        # Test read prefab
        sysCreat = ent.at("Components").map_get("SystemicCreature").get_union_data()
        assert(sysCreat is not None)

        # TEST read setted values
        assert(sysCreat.at("Faction").value == "Shamans")
        assert(not sysCreat.at("Faction").is_set())  # Not overrided
        assert(sysCreat.at("Inventory").value == "KaiWOLgrey")
        assert(not sysCreat.at("Inventory").is_set())  # Not overrided

        # TEST read array
        assert(sysCreat.at("ScriptList").is_set()) # Arrays are always set
        assert(sysCreat.at("ScriptList").size() == 3)

        # TEST default values
        assert(sysCreat.at("Burried").value is False)  # default
        assert (sysCreat.at("Burried").datatype == Ent.DataType.boolean)  # default
        assert(not sysCreat.at("Burried").is_set())  # default
        assert(sysCreat.at("Name").value == "")  # default
        assert(not sysCreat.at("Name").is_set())  # default

    testCreateInstanceOf("instance.create.entity")

    # ****************************** Test set_node_instance_of ******************************************
    instanceOf = entlib.make_entity_node()
    instanceOf.set_instance_of("prefab.entity")
    assert(instanceOf.at("Components").map_get("NetworkNode").get_union_data() is not None)
    instanceOf.at("Components").map_get("TransformGD").get_union_data().get_field_names()

    # Test instanciation of a template Node
    stickToTerrain = instanceOf.at("Components").map_insert("StickToTerrain").get_union_data()
    stickToTerrain.set_instance_of("test.StickToTerrain.node")
    stickToTerrain.at("NormalRatio").set_float(0.6)

    instanceOf.save_node("setInstanceOf.entity")

    testCreateInstanceOf("setInstanceOf.entity")

    # ******************************** Test iteration of schema **********************************
    for name, sub in entlib.schema.components.items():
        displaySubSchema(name, sub, "")

    # ********************************** Test load/save scene ************************************
    print("load_legacy_scene")
    entlib.rawdata_path = "X:/RawData"
    entlib.clear_cache()
    entlib.validation_enabled = False
    scene_ent = entlib.load_node_entity_read_only("X:/RawData/20_scene/personal/simont/vfxGym/ScenevfxGym.scene")

    scene = scene_ent.at("Components").map_get("SubScene").get_union_data().at("Embedded")
    assert(len(entlib.get_node_cache()) > 0)

    # assert (len(entlib.get_scene_cache()) > 0)
    # scene_cache = entlib.get_scene_cache()
    # found = False
    # for k, v in scene_cache.items():
    #     if k == r"22_World\SceneMainWorld\SceneMainWorld_entitylib_unit_test.scene":
    #         print(len(v.data.entities))
    #         found = True
    #         break
    # assert(found)

    print("Scene Loaded\n")
    print("Entity count : {}\n".format(len(scene)))

    for ent in scene.get_items():
        assert ent is not None
        print("  Name \"{}\"".format(ent.at("Name").value))

        for type in ent.at("Components").get_keys():
            print("    Type \"{}\"".format(type))
            root = ent.at("Components").map_get(type).get_union_data()
            # printNode("", root, "      ")

    heightObj = scene.at(0).at("Components").map_insert("HeightObj").get_union_data()
    heightObj.at("DisplaceNoiseList").push()

    scene.at(0).at("Components").map_insert("BeamGeneratorGD").get_union_data().get_field_names()
    assert(
        len(scene.at(0).at("Components").map_insert("HeightObj").get_union_data().get_field_names()) == 9)

    entlib.rawdata_path = os.getcwd()
    # scene.add_entity(entlib.make_instance_of(os.path.normpath(os.getcwd() + "/prefab.entity")))
    scene.map_insert_instanceof(os.path.normpath(os.getcwd() + "/prefab.entity"))

    print("save_scene")
    entlib.save_node_as_scene(scene_ent, os.getcwd() + "/SceneWild.test.scene")

    added_entity = scene.map_get("PlayerSpawner_")
    cinematic_comp = added_entity.at("Components").map_get("CinematicGD").get_union_data()
    assert (cinematic_comp is not None)

    print("dump_to_json(Override)")
    print(cinematic_comp.dumps())
    print("dump_to_json(OverrideOrPrefab)")
    print(cinematic_comp.dumps(Ent.OverrideValueSource.OverrideOrPrefab))
    print("dump_to_json(Any)")
    print(cinematic_comp.dumps(Ent.OverrideValueSource.Any))
    
    print("Done")

except subprocess.CalledProcessError as err:
    print(traceback.format_exc())
    print(err.output)
