import os
import subprocess
import traceback
import logging
import sys

entitylib_path = "../x64/Release"
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
    colorRef = "file://RuntimeComponents.json#/definitions/Color"
    assert colorRef in entlib.schema.schema.definitions

    # Check Ent::Subschema::getUnionTypesMap
    cinematicGDRef = "file://RuntimeComponents.json#/definitions/CinematicGD"
    cinematicGDSchema = entlib.schema.schema.definitions[cinematicGDRef]
    scriptEventUnionSchema = cinematicGDSchema.properties["ScriptEvents"].get().get_singular_items().get()
    nameToTypeMap = scriptEventUnionSchema.get_union_types_dict()
    assert len(nameToTypeMap) == 14
    assert "CineEventTest" in nameToTypeMap
    assert "CineEventTestBlackboardHasFact" in nameToTypeMap
    assert "CineEventTestEndCurrentSequence" in nameToTypeMap

    ####################################################################################################################
    ent = entlib.load_entity("prefab.entity")  # type: Ent.Entity

    # Test default value
    voxelSimulationGD = ent.get_component("VoxelSimulationGD")
    assert(voxelSimulationGD.root.at("TransmissionBySecond").value == 100.)
    assert(voxelSimulationGD.root.at("TransmissionBySecond").is_default())
    assert(voxelSimulationGD.root.get_type_name() == "file://RuntimeComponents.json#/definitions/VoxelSimulationGD")

    # TEST read inherited values in inherited component
    heightObj = ent.get_component("HeightObj")
    assert(heightObj is not None)
    assert(heightObj.root.at("Subdivision").value == 0)
    assert(heightObj.root.at("Subdivision").is_set())
    assert(
        heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").value == 51248)
    assert(heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").is_set())

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
    assert(cineEvent.get_type_name() == "file://RuntimeComponents.json#/definitions/CineEventTestBlackboardHasFact")

    nbEnt = cineEvent.at("FactName")  # type: Ent.Node
    assert(nbEnt is not None)
    assert(nbEnt.datatype == Ent.DataType.string)
    assert(nbEnt.value == "Toto")

    # Set Union type
    oneOfScripts2 = scriptEvents.at(1)  # type: Ent.Node
    assert(oneOfScripts2.datatype == Ent.DataType.union)
    assert(oneOfScripts2.get_union_type() == "CineEventTestBlackboardHasFact")
    oneOfScripts2.set_union_type("CineEventTestCurrentGameState")
    testCurrentState = oneOfScripts2.get_union_data()  # type: Ent.Node
    assert(oneOfScripts2.get_union_type() == "CineEventTestCurrentGameState")
    fieldNames2 = testCurrentState.get_field_names()
    assert(fieldNames2[0] == "GameStateName")
    assert(fieldNames2[1] == "Super")
    testCurrentState.at("GameStateName").set_string("Pouet!")
    
    # TEST sub - object with non - default values
    explosionEffect = ent.get_component("ExplosionEffect")  # type: Ent.Component
    shakeData = explosionEffect.root.at("ShakeData")  # type: Ent.Node
    assert(shakeData.at("shakeDuration").value == 0.)

    # TEST simple entity ref creation
    testEntityRef = ent.add_component("TestEntityRef")
    assert(testEntityRef is not None)
    assert(testEntityRef.root.at("TestRef").get_entityref().entity_path == "")  # value                             ????
    testEntityRef.root.at("TestRef").set_entityref(ent.make_entityref(ent))
    assert(testEntityRef.root.at("TestRef").get_entityref().entity_path == ".")
    testEntityRef.root.at("TestRef").value = ent.make_entityref(allSubEntities[0])

    sysCreat.root.at("Name").value = "Shamane_male"
    entlib.save_entity(ent, "prefab.copy.entity")
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
    // TEST entity refs
    // file: entity-references-a.entity
    // - A-entity [ref to B: "B"]
    //     - B [ref to A: ".."]
    //
    // file: entity-references.scene
    // - root-scene
    //     - InstanceOfA
    //     - C [ref to B in InstanceOfA: "../InstanceOfA/B"]
    //
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
    # Test create instance of
    instanceOf = entlib.make_instance_of("prefab.entity")
    entlib.save_entity(instanceOf, "instance.create.entity")

    ####################################################################################################################
    # Test read instance of
    ent = entlib.load_entity("instance.create.entity")

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

    # ******************************** Test iteration of schema **********************************
    for name, sub in entlib.schema.components.items():
        displaySubSchema(name, sub, "")

    # ********************************** Test load/save scene ************************************
    print("load_scene")
    entlib.rawdata_path = "X:/RawData"
    scene = entlib.load_scene("X:/RawData/22_World/SceneMainWorld/SceneMainWorld.scene")

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
        len(scene.entities[0].add_component("ExplosionEffect").root.get_field_names()) == 23)

    ep1 = [ent for ent in scene.entities if ent.name == "EP1_"]
    assert (len(ep1) != 0)
    assert (ep1[0].get_subscene_component() is not None)

    scene.entities.append(entlib.make_instance_of(os.getcwd() + "/prefab.entity"))

    print("save_scene")
    entlib.save_scene(scene, "X:/RawData/22_World/SceneMainWorld/SceneMainWorld.test.scene")

    print("Done")

except subprocess.CalledProcessError as err:
    print(traceback.format_exc())
    print(err.output)
