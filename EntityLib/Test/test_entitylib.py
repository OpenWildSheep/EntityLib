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
    # Test $ref links in entlib.schema.schema.allDefinitions
    colorRef = "./RuntimeComponents.json#/definitions/Color"
    assert colorRef in entlib.schema.schema.definitions

    # Check Ent.Subschema.getUnionTypesMap
    cinematicGDRef = "./RuntimeComponents.json#/definitions/CinematicGD"
    cinematicGDSchema = entlib.schema.schema.definitions[cinematicGDRef]
    scriptEventUnionSchema = cinematicGDSchema.properties["ScriptEvents"].get().get_singular_items().get()
    nameToTypeMap = scriptEventUnionSchema.get_union_types_dict()
    assert len(nameToTypeMap) == 12
    assert "CineEventTest" in nameToTypeMap
    assert "CineEventTriggerEventHandlerPost" in nameToTypeMap
    assert "CineEventTestEndCurrentSequence" in nameToTypeMap

    # Ensure that all components have a ref and is in entlib.schema.schema.allDefinitions
    for name, schema in entlib.schema.components.items():
        absRef = schema.name
        assert absRef.find("./") == 0
        assert absRef in entlib.schema.schema.definitions

    ####################################################################################################################
    def testPrefabEntity(ent: Ent.Entity):
        # ActorStates
        actorStates = ent.get_actorstates()
        assert(actorStates.datatype == Ent.DataType.array)
        assert(actorStates.size() == 2)
        actorState = actorStates.at(0)
        assert(actorState != None)
        assert actorState.get_schema().get_union_name_field() == "className"
        assert actorState.get_schema().get_union_data_field() == "classData"
        climbEdge = actorState.get_union_data()
        assert(climbEdge != None)
        exitRequired = climbEdge.at("locomotionMode")
        assert(exitRequired != None)
        assert(exitRequired.get_string() == "crouch")
        actorState2 = actorStates.at(1)
        assert(actorState2 != None)
        cinematic = actorState2.get_union_data()
        assert(cinematic != None)
        type = cinematic.at("Type")
        assert(type != None)
        assert(type.get_int() == -1)

        # Map and Set overridePolicy
        pathNodeGD = ent.get_component("PathNodeGD")
        tags = pathNodeGD.root.at("Tags").at("Tags")
        assert(tags.size() == 2)
        assert(tags.at(0).at(0).get_string() == "a")
        assert(tags.at(1).at(0).get_string() == "c")
        assert(tags.at(1).at(1).size() == 1)
        assert(tags.at(1).at(1).at(0).get_string() == "2")


        # Test default value
        voxelSimulationGD = ent.get_component("VoxelSimulationGD")
        assert(voxelSimulationGD.root.at("TransmissionBySecond").value == 100.)
        assert(voxelSimulationGD.root.at("TransmissionBySecond").is_default())
        assert(voxelSimulationGD.root.get_type_name() == "./RuntimeComponents.json#/definitions/VoxelSimulationGD")

        # TEST read inherited values in inherited component
        heightObj = ent.get_component("HeightObj")
        assert(heightObj is not None)
        assert(heightObj.root.at("Subdivision").value == 0)
        assert(heightObj.root.at("Subdivision").is_set())
        assert(
            heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").value == 51248)
        assert(heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").is_set())
        assert heightObj.root.at("Subdivision").get_schema().user_meta["testUserMetatdata"] is 42

        # Test read Thumbnail
        assert(ent.thumbnail is not None)
        assert(ent.thumbnail == "TestThumbnail")

        # Test read prefab
        sysCreat = ent.get_component("SystemicCreature")
        assert(sysCreat is not None)

        # TEST read setted values
        assert(sysCreat.root.at("Faction").value == "Shamans") # set
        assert(sysCreat.root.at("Faction").is_set()) # is set
        assert(sysCreat.root.at("Inventory").value == "KaiWOLgrey") # set
        assert(sysCreat.root.at("Inventory").is_set()) # is set

        # TEST comment
        assert sysCreat.root.at("BehaviorState").get_string() == "W/*at*/c//h"

        # TEST read array
        assert(sysCreat.root.at("ScriptList").is_set())
        assert(sysCreat.root.at("ScriptList").size() == 3)

        # TEST default values
        assert(sysCreat.root.at("Burried").value == False) # default
        assert(not sysCreat.root.at("Burried").is_set()) # default
        assert(sysCreat.root.at("Name").value == "") # default
        assert(not sysCreat.root.at("Name").is_set()) # default

        # TEST SubScene
        subScenecomp = ent.get_subscene_component()
        allSubEntities = subScenecomp.embedded.entities
        assert(len(allSubEntities) == 1)
        assert(allSubEntities[0].name == "EP1-Spout_LINK_001")
        assert(allSubEntities[0].color[0] == 255)

        # TEST union
        cinematicGD = ent.get_component("CinematicGD")  # type: Ent.Component
        scriptEvents = cinematicGD.root.at("ScriptEvents")  # type: Ent.Node
        assert(scriptEvents.datatype == Ent.DataType.array)

        # Read Union type
        oneOfScripts = scriptEvents.at(0)  # type: Ent.Node
        assert(oneOfScripts.datatype == Ent.DataType.union)
        cineEvent = oneOfScripts.get_union_data()  # type: Ent.Node
        assert(cineEvent.get_type_name() == "./RuntimeComponents.json#/definitions/CineEventTriggerEventHandlerPost")

        nbEnt = cineEvent.at("EventName")  # type: Ent.Node
        assert(nbEnt is not None)
        assert(nbEnt.datatype == Ent.DataType.string)
        assert(nbEnt.value == "Toto")

        # TEST sub - object with non - default values
        ldprimitive = ent.get_component("LDPrimitive")  # type: Ent.Component
        primitiveData = ldprimitive.root.at("PrimitiveData")  # type: Ent.Node
        assert(primitiveData.at("Height").value == 42.)

    ####################################################################################################################
    # Test the readOnly prefab.entity
    ent = entlib.load_entity_read_only("prefab.entity")  # type: Ent.Entity
    testPrefabEntity(ent)

    ####################################################################################################################
    ent = entlib.load_entity("prefab.entity")  # type: Ent.Entity

    testPrefabEntity(ent)

    # Set Union type
    cinematicGD = ent.get_component("CinematicGD")  # type: Ent.Component
    scriptEvents = cinematicGD.root.at("ScriptEvents")  # type: Ent.Node
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

    # Push in an array of Union Ent.Node
    oneOfScripts4 = scriptEvents.push()
    assert(oneOfScripts4.datatype == Ent.DataType.union)
    assert(oneOfScripts4.get_union_type() == "CineEvent")
    assert(scriptEvents.at(3) == oneOfScripts4)

    # TEST simple entity ref creation
    testEntityRef = ent.add_component("TestEntityRef")
    assert(testEntityRef is not None)
    assert(testEntityRef.root.at("TestRef").get_entityref().entity_path == "")  # value                             ????
    testEntityRef.root.at("TestRef").set_entityref(ent.make_entityref(ent))
    assert(testEntityRef.root.at("TestRef").get_entityref().entity_path == ".")
    subScenecomp = ent.get_subscene_component()
    allSubEntities = subScenecomp.embedded.entities
    testEntityRef.root.at("TestRef").value = ent.make_entityref(allSubEntities[0])

    # TEST MaxActivationLevel
    ent.max_activation_level = Ent.ActivationLevel.InWorld

    sysCreat = ent.get_component("SystemicCreature")
    sysCreat.root.at("Name").value = "Shamane_male"
    entlib.save_entity(ent, "prefab.copy.entity")

    # TEST SubScene detach
    original_sub_entities = ent.get_subscene_component().embedded.entities
    detached_sub_scene = ent.get_subscene_component().detach_embedded()
    assert(len(ent.get_subscene_component().embedded.entities) is 0)
    assert(all(a == b for a, b in zip(original_sub_entities, detached_sub_scene.entities)))
    
    ####################################################################################################################
    # Test write prefab
    ent = entlib.load_entity("prefab.copy.entity")

    # TEST read inherited values in inherited component
    heightObj = ent.get_component("HeightObj")
    assert(heightObj is not None)
    assert(heightObj.root.at("Subdivision").value == 0)
    assert(heightObj.root.at("Subdivision").is_set())
    assert(
        heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").value == 51248)
    assert(heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").is_set())

    sysCreat = ent.get_component("SystemicCreature")
    assert(sysCreat is not None)
    # TEST read setted values
    assert(sysCreat.root.at("Faction").value == "Shamans") # set
    assert(sysCreat.root.at("Inventory").value == "KaiWOLgrey") # set

    # TEST read array
    assert(sysCreat.root.at("ScriptList").is_set())
    assert(sysCreat.root.at("ScriptList").size() == 3)

    # TEST default values unchanged
    assert(sysCreat.root.at("Burried").value is False) # default
    assert(not sysCreat.root.at("Burried").is_set()) # default

    # TEST changed values
    assert(
        sysCreat.root.at("Name").value == "Shamane_male") # set. changed.
    assert(sysCreat.root.at("Name").is_set()) # set. changed.

    # TEST simple entity refs resolution
    testEntityRef = ent.get_component("TestEntityRef")
    assert(testEntityRef is not None)
    assert(testEntityRef.root.at("TestRef").is_set())
    entityRef = testEntityRef.root.at("TestRef").get_entityref()
    resolvedEntity = ent.resolve_entityref(entityRef)
    assert(resolvedEntity is not None)

    subScenecomp = ent.get_subscene_component()
    allSubEntities = subScenecomp.embedded.entities
    assert(len(allSubEntities) == 1)
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
    scene = entlib.load_scene("entity-references.scene")
    assert(len(scene.entities) == 2)
    instanceOfA = scene.entities[0]
    assert(instanceOfA.name == "InstanceOfA")
    subSceneComp = instanceOfA.get_subscene_component()  # type: Ent.SubSceneComponent
    assert(subSceneComp is not None)
    assert(subSceneComp.is_embedded)
    assert(len(subSceneComp.embedded.entities) == 1)
    B = subSceneComp.embedded.entities[0]
    assert(B.name == "B")
    C = scene.entities[1]
    assert(C.name == "C")

    # TEST entity ref creation
    BToInstanceOfAref = B.make_entityref(instanceOfA)
    assert(BToInstanceOfAref.entity_path == "..")
    InstanceOfAToBref = instanceOfA.make_entityref(B)
    assert(InstanceOfAToBref.entity_path == "B")
    CToBref = C.make_entityref(B)
    assert(CToBref.entity_path == "../InstanceOfA/B")
    BToCref = B.make_entityref(C)
    assert(BToCref.entity_path == "../../C")

    # TEST entity ref resolution
    resolvedEmptyRef = instanceOfA.resolve_entityref(Ent.EntityRef())
    assert(resolvedEmptyRef is None)
    resolvedInstanceOfA = B.resolve_entityref(Ent.EntityRef(".."))
    assert(resolvedInstanceOfA is instanceOfA)
    resolvedB = instanceOfA.resolve_entityref(Ent.EntityRef("B"))
    assert(resolvedB is B)
    resolvedBbis = C.resolve_entityref(Ent.EntityRef("../InstanceOfA/B"))
    assert(resolvedBbis is B)
    resolvedC = B.resolve_entityref(Ent.EntityRef("../../C"))
    assert(resolvedC is C)

    # TEST entity ref resolution from scenes
    assert(scene.resolve_entityref(Ent.EntityRef("..")) is None)
    assert(scene.resolve_entityref(Ent.EntityRef("InstanceOfA")) is instanceOfA)
    assert(scene.resolve_entityref(Ent.EntityRef("InstanceOfA/B")) is B)
    assert(scene.resolve_entityref(Ent.EntityRef("C")) is C)
    assert(scene.resolve_entityref(Ent.EntityRef("InstanceOfA/B/../../C")) is C)

    ####################################################################################################################
    def testInstanceOf(ent: Ent.Entity):
        # ActorStates
        actorStates = ent.get_actorstates()
        assert(actorStates.datatype == Ent.DataType.array)
        assert(actorStates.size() == 3)
        actorState = actorStates.at(0)
        assert(actorState is not None)
        climbEdge = actorState.get_union_data()
        assert(climbEdge is not None)
        exitRequired = climbEdge.at("locomotionMode")
        assert(exitRequired is not None)
        assert(exitRequired.get_string() == "crouch")
        actorState2 = actorStates.at(1)
        assert(actorState2 is not None)
        cinematic = actorState2.get_union_data()
        assert(cinematic is not None)
        type = cinematic.at("Type")
        assert(type is not None)
        assert(type.get_int() == 13)
        actorState3 = actorStates.at(2)
        assert(actorState3 is not None)
        chosen = actorState3.get_union_data()
        assert(chosen is not None)
        exitRequ = chosen.at("ExitRequired")
        assert(exitRequ is not None)
        assert(exitRequ.get_bool() == True)

        # Map and Set overridePolicy
        pathNodeGD = ent.get_component("PathNodeGD")
        tags = pathNodeGD.root.at("Tags").at("Tags")
        assert(tags.size() == 3)
        assert(tags.at(0).at(0).get_string() == "a")
        assert(tags.at(1).at(0).get_string() == "b")
        assert(tags.at(2).at(0).get_string() == "c")
        assert(tags.at(2).at(1).size() == 3)
        assert(tags.at(2).at(1).at(0).get_string() == "1")
        assert(tags.at(2).at(1).at(1).get_string() == "2")
        assert(tags.at(2).at(1).at(2).get_string() == "3")

        # TEST SubScene (without override)
        subScene = ent.get_subscene_component()  # type: Ent.SubSceneComponent
        assert(subScene is not None)
        assert(subScene.is_embedded)
        subObj = subScene.embedded.entities[0]  # type: Ent.Entity
        assert(subObj.name == "EP1-Spout_LINK_001")
        assert(not subObj.has_override())
        netLink = subObj.get_component("NetworkLink")
        assert(netLink is not None)
        assert(netLink.root.at("Source").value == ".EP1-Spout_")
        assert(not netLink.root.at("Source").is_set())
        assert(netLink.root.at("Target").value == ".EP1-crook_")
        assert(not netLink.root.at("Target").is_set())
        trans = subObj.get_component("TransformGD")
        assert(trans.root.at("Position").at(0).value == 0.0)
        
        # Test instanciation of a template Node
        stickToTerrain = ent.get_component("StickToTerrain")
        assert(fabs(stickToTerrain.root.at("NormalRatio").get_float() - 0.6) < 0.0001)
        assert(stickToTerrain.root.at("ZOffset").is_set() is False)
        assert(stickToTerrain.root.at("ZOffset").is_default() is False)
        assert(fabs(stickToTerrain.root.at("ZOffset").get_float() - 10.) < 0.0001)

    # Test read instance of
    ent = entlib.load_entity("instance.entity")
    sysCreat = ent.get_component("SystemicCreature")
    assert(sysCreat is not None)

    # TEST read overrided value
    assert(sysCreat.root.at("Faction").value == "Plouf")  # Overrided

    # TEST read inherited values
    assert(
        sysCreat.root.at("Inventory").value == "KaiWOLgrey")  # Inherited
    assert(sysCreat.root.at("Life").value == 1000.)  # Inherited

    # TEST read inherited values in inherited component
    heightObj = ent.get_component("HeightObj")
    assert(heightObj is not None)
    assert(heightObj.root.at("Subdivision").value == 0)
    assert(not heightObj.root.at("Subdivision").is_set())
    assert(
        heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").value == 51248)
    assert(
        not heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").is_set())

    # TEST read default value
    assert(sysCreat.root.at("Burried").value is False)  # Inherited (from default)
    assert(not sysCreat.root.at("Burried").is_set())  # default

    # TEST read overrided in array
    assert(
        sysCreat.root.at("ScriptList").at(1).value == "b2")  # Overrided
    assert(sysCreat.root.at("ScriptList").at(1).is_set())  # Overrided
    # TEST read Not overrided in array
    assert(
        sysCreat.root.at("ScriptList").at(2).value == "c1")  # not overrided
    assert(not sysCreat.root.at("ScriptList").at(2).is_set())  # Not overrided

    # Programatically unset
    sysCreat.root.at("ScriptList").at(1).unset()
    # Programatically set
    sysCreat.root.at("ScriptList").at(2).value = "c2"

    # TEST read array
    assert(sysCreat.root.at("ScriptList").is_set())
    assert(sysCreat.root.at("ScriptList").size() == 3)

    # TEST Extand array
    sysCreat.root.at("ScriptList").push().value = "d2"
    assert(sysCreat.root.at("ScriptList").size() == 4)

    # TEST SubScene(without override)
    testInstanceOf(ent)

    sysCreat.root.at("BehaviorState").value = "Overrided"
    entlib.save_entity(ent, "instance.copy.entity")

    ####################################################################################################################
    
    def testInstanceOverrideSubscene(ent: Ent.Entity):
        # TEST SubScene (with override)
        subScene = ent.get_subscene_component()
        assert(subScene is not None)
        assert(subScene.is_embedded)
        subObj = subScene.embedded.entities[0]
        assert(subObj.name == "EP1-Spout_LINK_001")

        # Test an overrided Component
        netLink = subObj.get_component("NetworkLink")
        assert(netLink is not None)
        assert(netLink.root.at("Source").value == ".EP1-Spout_")
        assert(not netLink.root.at("Source").is_set())
        assert(netLink.root.at("Target").value == ".EP1-crook_2")
        assert(netLink.root.at("Target").is_set())

        # Test a not overrided Component
        trans = subObj.get_component("TransformGD")
        assert(trans is not None)
        assert(trans.root.at("Position").at(0).value == 0.0)

    ####################################################################################################################
    ent = entlib.load_entity("instance_override_subscene.entity")
    testInstanceOverrideSubscene(ent)
    entlib.save_entity(ent, "instance_override_subscene.copy.entity")

    ####################################################################################################################
    ent = entlib.load_entity("instance_override_subscene.copy.entity")
    testInstanceOverrideSubscene(ent)

    # Test write instance of
    ent = entlib.load_entity("instance.copy.entity")
    sysCreat = ent.get_component("SystemicCreature")
    assert(sysCreat is not None)

    # TEST read inherited values in inherited component
    heightObj = ent.get_component("HeightObj")
    assert(heightObj is not None)
    assert(heightObj.root.at("Subdivision").value == 0)
    assert(not heightObj.root.at("Subdivision").is_set())
    assert(
        heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").value == 51248)
    assert(
        not heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").is_set())

    # TEST read overrided value
    assert(sysCreat.root.at("Faction").value == "Plouf")  # Overrided

    # TEST read inherited values
    assert(
        sysCreat.root.at("Inventory").value == "KaiWOLgrey")  # Inherited
    assert(sysCreat.root.at("Life").value == 1000.)  # Inherited

    # TEST read default value
    assert(sysCreat.root.at("Burried").value == False)  # Inherited (from default)
    assert(not sysCreat.root.at("Burried").is_set())  # default

    # TEST read programatically overrided in array
    assert(
        sysCreat.root.at("ScriptList").at(1).value == "b1")  # No more overrided
    assert(not sysCreat.root.at("ScriptList").at(1).is_set())  # No more overrided
    # TEST read programatically unset in array
    assert(
        sysCreat.root.at("ScriptList").at(2).value == "c2")  # Overrided
    assert(sysCreat.root.at("ScriptList").at(2).is_set())  # Overrided

    # TEST read programatically extand array
    assert(
        sysCreat.root.at("ScriptList").at(3).value == "d2")  # Overrided
    assert(sysCreat.root.at("ScriptList").at(3).is_set())  # Overrided

    # TEST read extanded array
    assert(sysCreat.root.at("ScriptList").is_set())
    assert(sysCreat.root.at("ScriptList").size() == 4)

    # TEST override value from code
    assert(
        sysCreat.root.at("BehaviorState").value == "Overrided")  # set. changed.
    assert(sysCreat.root.at("BehaviorState").is_set())  # set. changed.

    testInstanceOf(ent)

    entlib.save_entity(ent, "instance.copy.entity")

    ####################################################################################################################
    # Test create detached
    ent = entlib.load_entity("instance.entity")
    detached = ent.detach_entity_from_prefab()

    sysCreat = detached.get_component("SystemicCreature")
    assert(sysCreat is not None)

    # TEST read inherited values in inherited component
    heightObj = ent.get_component("HeightObj")
    assert(heightObj is not None)
    assert(heightObj.root.at("Subdivision").value == 0)
    assert(not heightObj.root.at("Subdivision").is_set())
    assert(
        heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").value == 51248)
    assert(
        not heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").is_set())

    # TEST default values
    assert(sysCreat.root.at("Burried").value is False)  # default
    assert(not sysCreat.root.at("Burried").is_set())  # default
    assert(sysCreat.root.at("Name").value == "")  # default
    assert(not sysCreat.root.at("Name").is_set())  # default

    # TEST read setted values
    assert(sysCreat.root.at("Faction").value == "Plouf")  # set
    assert(sysCreat.root.at("Faction").is_set())  # is set
    assert(sysCreat.root.at("Inventory").value == "KaiWOLgrey")  # set
    assert(sysCreat.root.at("Inventory").is_set())  # is set

    entlib.save_entity(detached, "instance.detached.entity")

    ####################################################################################################################
    # Test read detached
    ent = entlib.load_entity("instance.detached.entity")

    sysCreat = ent.get_component("SystemicCreature")

    # TEST read inherited values in inherited component
    heightObj = ent.get_component("HeightObj")
    assert(heightObj is not None)
    assert(heightObj.root.at("Subdivision").value == 0)
    assert(heightObj.root.at("Subdivision").is_set())
    assert(
        heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").value == 51248)
    assert(heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").is_set())

    # TEST default values
    assert(sysCreat.root.at("Burried").value is False)  # default
    assert(not sysCreat.root.at("Burried").is_set())  # default
    assert(sysCreat.root.at("Name").value == "")  # default
    assert(not sysCreat.root.at("Name").is_set())  # default

    # TEST read setted values
    assert(sysCreat.root.at("Faction").value == "Plouf")  # set
    assert(sysCreat.root.at("Faction").is_set())  # is set
    assert(sysCreat.root.at("Inventory").value == "KaiWOLgrey")  # set
    assert(sysCreat.root.at("Inventory").is_set())  # is set

    ####################################################################################################################
    # Test make_instance_of
    instanceOf = entlib.make_instance_of("prefab.entity")

    # Test instanciation of a template Node
    stickToTerrain = instanceOf.add_component("StickToTerrain")
    stickToTerrain.root.set_instance_of("test.StickToTerrain.node", )
    assert(stickToTerrain.root.get_instance_of() is not None)
    stickToTerrain.root.at("NormalRatio").set_float(0.6)

    assert(fabs(stickToTerrain.root.at("NormalRatio").get_float() - 0.6) < 0.0001)
    assert(stickToTerrain.root.at("ZOffset").is_set() is False)
    assert(stickToTerrain.root.at("ZOffset").is_default() is False)
    assert(fabs(stickToTerrain.root.at("ZOffset").get_float() - 10.) < 0.0001)

    assert(instanceOf.get_component("NetworkNode") is not None)
    instanceOf.get_component("TransformGD").root.get_field_names()
    entlib.save_entity(instanceOf, "instance.create.entity")

    ####################################################################################################################
    def testCreateInstanceOf(_instancePath):
        # Test read instance of
        ent = entlib.load_entity(_instancePath)

        ent.get_component("TransformGD").root.get_field_names()

        # Test instanciation of a template Node
        stickToTerrain = ent.get_component("StickToTerrain")
        assert(stickToTerrain.root.get_instance_of() is not None)
        assert(fabs(stickToTerrain.root.at("NormalRatio").get_float() - 0.6) < 0.0001)
        assert(stickToTerrain.root.at("ZOffset").is_set() is False)
        assert(stickToTerrain.root.at("ZOffset").is_default() is False)
        assert(fabs(stickToTerrain.root.at("ZOffset").get_float() - 10.) < 0.0001)

        # TEST read inherited values in inherited component
        heightObj = ent.get_component("HeightObj")
        assert(heightObj is not None)
        assert(heightObj.root.at("Subdivision").value == 0)
        assert(not heightObj.root.at("Subdivision").is_set())
        assert(
            heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").value == 51248)
        assert(
            not heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").is_set())

        # Test read prefab
        sysCreat = ent.get_component("SystemicCreature")
        assert(sysCreat is not None)

        # TEST read setted values
        assert(sysCreat.root.at("Faction").value == "Shamans")
        assert(not sysCreat.root.at("Faction").is_set())  # Not overrided
        assert(sysCreat.root.at("Inventory").value == "KaiWOLgrey")
        assert(not sysCreat.root.at("Inventory").is_set())  # Not overrided

        # TEST read array
        assert(sysCreat.root.at("ScriptList").is_set()) # Arrays are always set
        assert(sysCreat.root.at("ScriptList").size() == 3)

        # TEST default values
        assert(sysCreat.root.at("Burried").value is False)  # default
        assert (sysCreat.root.at("Burried").datatype == Ent.DataType.boolean)  # default
        assert(not sysCreat.root.at("Burried").is_set())  # default
        assert(sysCreat.root.at("Name").value == "")  # default
        assert(not sysCreat.root.at("Name").is_set())  # default

    testCreateInstanceOf("instance.create.entity")

    # ****************************** Test set_node_instance_of ******************************************
    instanceOf = Ent.Entity(entlib)
    instanceOf.set_instance_of("prefab.entity")
    assert(instanceOf.get_component("NetworkNode") is not None)
    instanceOf.get_component("TransformGD").root.get_field_names()

    # Test instanciation of a template Node
    stickToTerrain = instanceOf.add_component("StickToTerrain")
    stickToTerrain.root.set_instance_of("test.StickToTerrain.node")
    stickToTerrain.root.at("NormalRatio").set_float(0.6)

    entlib.save_entity(instanceOf, "setInstanceOf.entity")

    testCreateInstanceOf("setInstanceOf.entity")

    # ******************************** Test iteration of schema **********************************
    for name, sub in entlib.schema.components.items():
        displaySubSchema(name, sub, "")

    # ********************************** Test load/save scene ************************************
    print("load_legacy_scene")
    entlib.rawdata_path = "X:/RawData"
    entlib.clear_cache()
    scene = entlib.load_scene_read_only(
        "X:/RawData/22_World/SceneMainWorld/SceneMainWorld_entitylib_unit_test.scene")
    assert(len(entlib.get_entity_cache()) > 0)
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
    print("Entity count : {}\n".format(len(scene.entities)))

    for ent in scene.entities:
        print("  Name \"{}\"".format(ent.name))

        for type in ent.get_component_types():
            print("    Type \"{}\"".format(type))
            root = ent.get_component(type).root
            # printNode("", root, "      ")

    heightObj = scene.entities[0].add_component("HeightObj")
    heightObj.root.at("DisplaceNoiseList").push()

    scene.entities[0].add_component("BeamGeneratorGD").root.get_field_names()
    assert(
        len(scene.entities[0].add_component("HeightObj").root.get_field_names()) == 5)

    ep1 = [ent for ent in scene.entities if ent.name == "EP1_"]
    assert (len(ep1) != 0)
    assert (ep1[0].get_subscene_component() is not None)

    scene.add_entity(entlib.make_instance_of(os.path.normpath(os.getcwd() + "/prefab.entity")))

    print("save_scene")
    entlib.save_scene(scene, os.getcwd() + "/SceneMainWorld.test.scene")

    added_entity = scene.entities[-1]
    cinematic_comp = added_entity.get_component("CinematicGD")
    assert (cinematic_comp is not None)

    print("dump_to_json(Override)")
    print(cinematic_comp.root.dumps())
    print("dump_to_json(OverrideOrPrefab)")
    print(cinematic_comp.root.dumps(Ent.OverrideValueSource.OverrideOrPrefab))
    print("dump_to_json(Any)")
    print(cinematic_comp.root.dumps(Ent.OverrideValueSource.Any))
    
    print("Done")

except subprocess.CalledProcessError as err:
    print(traceback.format_exc())
    print(err.output)
