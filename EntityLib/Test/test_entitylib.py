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

    entlib = Ent.EntityLib("X:/Tools")

    ####################################################################################################################
    ent = entlib.load_entity("prefab.entity")

    # TEST read inherited values in inherited component
    heightObj = ent.get_component("HeightObj")
    assert(heightObj is not None)
    assert(heightObj.root.at("Subdivision").get_int() == 0)
    assert(heightObj.root.at("Subdivision").is_set())
    assert(
        heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").get_int() == 51248)
    assert(heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").is_set())

    # Test read Thumbnail
    assert(ent.thumbnail is not None)
    assert(ent.thumbnail == "TestThumbnail")

    # Test read prefab
    sysCreat = ent.get_component("SystemicCreature")
    assert(sysCreat is not None)

    # TEST read setted values
    assert(sysCreat.root.at("Faction").get_string() == "Shamans") # set
    assert(sysCreat.root.at("Faction").is_set()) # is set
    assert(sysCreat.root.at("Inventory").get_string() == "KaiWOLgrey") # set
    assert(sysCreat.root.at("Inventory").is_set()) # is set

    # TEST read array
    assert(sysCreat.root.at("ScriptList").is_set())
    assert(sysCreat.root.at("ScriptList").size() == 3)

    # TEST default values
    assert(sysCreat.root.at("Burried").get_bool() == False) # default
    assert(not sysCreat.root.at("Burried").is_set()) # default
    assert(sysCreat.root.at("Name").get_string() == "") # default
    assert(not sysCreat.root.at("Name").is_set()) # default

    sysCreat.root.at("Name").set_string("Shamane_male")
    entlib.save_entity(ent, "prefab.copy.entity")
    ####################################################################################################################
    # Test write prefab
    ent = entlib.load_entity("prefab.copy.entity")

    # TEST read inherited values in inherited component
    heightObj = ent.get_component("HeightObj")
    assert(heightObj is not None)
    assert(heightObj.root.at("Subdivision").get_int() == 0)
    assert(heightObj.root.at("Subdivision").is_set())
    assert(
        heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").get_int() == 51248)
    assert(heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").is_set())

    sysCreat = ent.get_component("SystemicCreature")
    assert(sysCreat is not None)
    # TEST read setted values
    assert(sysCreat.root.at("Faction").get_string() == "Shamans") # set
    assert(sysCreat.root.at("Inventory").get_string() == "KaiWOLgrey") # set

    # TEST read array
    assert(sysCreat.root.at("ScriptList").is_set())
    assert(sysCreat.root.at("ScriptList").size() == 3)

    # TEST default values unchanged
    assert(sysCreat.root.at("Burried").get_bool() is False) # default
    assert(not sysCreat.root.at("Burried").is_set()) # default

    # TEST changed values
    assert(
        sysCreat.root.at("Name").get_string() == "Shamane_male") # set. changed.
    assert(sysCreat.root.at("Name").is_set()) # set. changed.
    ####################################################################################################################
    # Test read instance of
    ent = entlib.load_entity("instance.entity")
    sysCreat = ent.get_component("SystemicCreature")
    assert(sysCreat is not None)

    # TEST read overrided value
    assert(sysCreat.root.at("Faction").get_string() == "Plouf") # Overrided

    # TEST read inherited values
    assert(
        sysCreat.root.at("Inventory").get_string() == "KaiWOLgrey") # Inherited
    assert(sysCreat.root.at("Life").get_float() == 1000.) # Inherited

    # TEST read inherited values in inherited component
    heightObj = ent.get_component("HeightObj")
    assert(heightObj is not None)
    assert(heightObj.root.at("Subdivision").get_int() == 0)
    assert(not heightObj.root.at("Subdivision").is_set())
    assert(
        heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").get_int() == 51248)
    assert(
        not heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").is_set())

    # TEST read default value
    assert(sysCreat.root.at("Burried").get_bool() == False) # Inherited (from default)
    assert(not sysCreat.root.at("Burried").is_set()) # default

    # TEST read overrided in array
    assert(
        sysCreat.root.at("ScriptList").at(1).get_string() == "b2") # Overrided
    assert(sysCreat.root.at("ScriptList").at(1).is_set()) # Overrided
    # TEST read Not overrided in array
    assert(
        sysCreat.root.at("ScriptList").at(2).get_string() == "c1") # not overrided
    assert(not sysCreat.root.at("ScriptList").at(2).is_set()) # Not overrided

    # Programatically unset
    sysCreat.root.at("ScriptList").at(1).unset()
    # Programatically set
    sysCreat.root.at("ScriptList").at(2).set_string("c2")

    # TEST read array
    assert(sysCreat.root.at("ScriptList").is_set())
    assert(sysCreat.root.at("ScriptList").size() == 3)

    # TEST Extand array
    sysCreat.root.at("ScriptList").push().set_string("d2")
    assert(sysCreat.root.at("ScriptList").size() == 4)

    sysCreat.root.at("BehaviorState").set_string("Overrided")
    entlib.save_entity(ent, "instance.copy.entity")
    ####################################################################################################################
    # Test write instance of
    ent = entlib.load_entity("instance.copy.entity")
    sysCreat = ent.get_component("SystemicCreature")
    assert(sysCreat is not None)

    # TEST read inherited values in inherited component
    heightObj = ent.get_component("HeightObj")
    assert(heightObj is not None)
    assert(heightObj.root.at("Subdivision").get_int() == 0)
    assert(not heightObj.root.at("Subdivision").is_set())
    assert(
        heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").get_int() == 51248)
    assert(
        not heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").is_set())

    # TEST read overrided value
    assert(sysCreat.root.at("Faction").get_string() == "Plouf") # Overrided

    # TEST read inherited values
    assert(
        sysCreat.root.at("Inventory").get_string() == "KaiWOLgrey") # Inherited
    assert(sysCreat.root.at("Life").get_float() == 1000.) # Inherited

    # TEST read default value
    assert(sysCreat.root.at("Burried").get_bool() == False) # Inherited (from default)
    assert(not sysCreat.root.at("Burried").is_set()) # default

    # TEST read programatically overrided in array
    assert(
        sysCreat.root.at("ScriptList").at(1).get_string() == "b1") # No more overrided
    assert(not sysCreat.root.at("ScriptList").at(1).is_set()) # No more overrided
    # TEST read programatically unset in array
    assert(
        sysCreat.root.at("ScriptList").at(2).get_string() == "c2") # Overrided
    assert(sysCreat.root.at("ScriptList").at(2).is_set()) # Overrided

    # TEST read programatically extand array
    assert(
        sysCreat.root.at("ScriptList").at(3).get_string() == "d2") # Overrided
    assert(sysCreat.root.at("ScriptList").at(3).is_set()) # Overrided

    # TEST read extanded array
    assert(sysCreat.root.at("ScriptList").is_set())
    assert(sysCreat.root.at("ScriptList").size() == 4)

    # TEST override value from code
    assert(
        sysCreat.root.at("BehaviorState").get_string() == "Overrided") # set. changed.
    assert(sysCreat.root.at("BehaviorState").is_set()) # set. changed.

    entlib.save_entity(ent, "instance.copy.entity")
    ####################################################################################################################
    # Test create detached
    ent = entlib.load_entity("instance.entity")
    detached = ent.detach_entity_from_prefab()

    sysCreat = detached.get_component("SystemicCreature")

    # TEST read inherited values in inherited component
    heightObj = ent.get_component("HeightObj")
    assert(heightObj is not None)
    assert(heightObj.root.at("Subdivision").get_int() == 0)
    assert(not heightObj.root.at("Subdivision").is_set())
    assert(
        heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").get_int() == 51248)
    assert(
        not heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").is_set())

    # TEST default values
    assert(sysCreat.root.at("Burried").get_bool() == False) # default
    assert(not sysCreat.root.at("Burried").is_set()) # default
    assert(sysCreat.root.at("Name").get_string() == "") # default
    assert(not sysCreat.root.at("Name").is_set()) # default

    # TEST read setted values
    assert(sysCreat.root.at("Faction").get_string() == "Plouf") # set
    assert(sysCreat.root.at("Faction").is_set()) # is set
    assert(sysCreat.root.at("Inventory").get_string() == "KaiWOLgrey") # set
    assert(sysCreat.root.at("Inventory").is_set()) # is set

    entlib.save_entity(detached, "instance.detached.entity")
    ####################################################################################################################
    # Test read detached
    ent = entlib.load_entity("instance.detached.entity")

    sysCreat = ent.get_component("SystemicCreature")

    # TEST read inherited values in inherited component
    heightObj = ent.get_component("HeightObj")
    assert(heightObj is not None)
    assert(heightObj.root.at("Subdivision").get_int() == 0)
    assert(heightObj.root.at("Subdivision").is_set())
    assert(
        heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").get_int() == 51248)
    assert(heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").is_set())

    # TEST default values
    assert(sysCreat.root.at("Burried").get_bool() == False) # default
    assert(not sysCreat.root.at("Burried").is_set()) # default
    assert(sysCreat.root.at("Name").get_string() == "") # default
    assert(not sysCreat.root.at("Name").is_set()) # default

    # TEST read setted values
    assert(sysCreat.root.at("Faction").get_string() == "Plouf") # set
    assert(sysCreat.root.at("Faction").is_set()) # is set
    assert(sysCreat.root.at("Inventory").get_string() == "KaiWOLgrey") # set
    assert(sysCreat.root.at("Inventory").is_set()) # is set
    ####################################################################################################################
    # Test create instance of
    instanceOf = entlib.make_instance_of("test_makeInstanceOf", "prefab.entity")
    entlib.save_entity(instanceOf, "instance.create.entity")
    ####################################################################################################################
    # Test read instance of
    ent = entlib.load_entity("instance.create.entity")

    for f in ent.get_component("Transform").root.get_field_names():
        print(f)

    # TEST read inherited values in inherited component
    heightObj = ent.get_component("HeightObj")
    assert(heightObj is not None)
    assert(heightObj.root.at("Subdivision").get_int() == 0)
    assert(not heightObj.root.at("Subdivision").is_set())
    assert(
        heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").get_int() == 51248)
    assert(
        not heightObj.root.at("DisplaceNoiseList").at(0).at("MapChannel").is_set())

    # Test read prefab
    sysCreat = ent.get_component("SystemicCreature")
    assert(sysCreat is not None)

    # TEST read setted values
    assert(sysCreat.root.at("Faction").get_string() == "Shamans")
    assert(not sysCreat.root.at("Faction").is_set()) # Not overrided
    assert(sysCreat.root.at("Inventory").get_string() == "KaiWOLgrey")
    assert(not sysCreat.root.at("Inventory").is_set()) # Not overrided

    # TEST read array
    assert(sysCreat.root.at("ScriptList").is_set()) # Arrays are always set
    assert(sysCreat.root.at("ScriptList").size() == 3)

    # TEST default values
    assert(sysCreat.root.at("Burried").get_bool() == False) # default
    assert (sysCreat.root.at("Burried").datatype == Ent.DataType.boolean)  # default
    assert(not sysCreat.root.at("Burried").is_set()) # default
    assert(sysCreat.root.at("Name").get_string() == "") # default
    assert(not sysCreat.root.at("Name").is_set()) # default

    # ******************************** Test iteration of schema **********************************
    for name, sub in entlib.schema.components.items():
        displaySubSchema(name, sub, "")

    # ********************************** Test load/save scene ************************************
    print("load_scene")
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

    scene.entities[0].add_component("BeamGenerator").root.get_field_names()
    assert(
        len(scene.entities[0].add_component("ExplosionEffect").root.get_field_names()) == 22)

    ep1 = [ent for ent in scene.entities if ent.name == "EP1_"]
    assert (len(ep1) != 0)
    assert (ep1[0].get_subscene_component() is not None)

    print("save_scene")
    entlib.save_scene(scene, "X:/RawData/22_World/SceneMainWorld/SceneMainWorld.test.scene")

    print("Done")

except subprocess.CalledProcessError as err:
    print(traceback.format_exc())
    print(err.output)
