
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class Sensor(HelperObject):
    schema_name = "Sensor"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Sensor
        return Sensor(entlib.load_node_file(sourcefile, entlib.get_schema(Sensor.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Sensor
        return Sensor(entlib.make_node(Sensor.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




