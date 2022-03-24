
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class sJointMotorDesc(HelperObject):
    schema_name = "sJointMotorDesc"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sJointMotorDesc
        return sJointMotorDesc(entlib.load_node_file(sourcefile, entlib.get_schema(sJointMotorDesc.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sJointMotorDesc
        return sJointMotorDesc(entlib.make_node(sJointMotorDesc.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




