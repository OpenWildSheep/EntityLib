
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class sJointBallDesc(HelperObject):
    schema_name = "sJointBallDesc"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sJointBallDesc
        return sJointBallDesc(entlib.load_node_file(sourcefile, entlib.get_schema(sJointBallDesc.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sJointBallDesc
        return sJointBallDesc(entlib.make_node(sJointBallDesc.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




