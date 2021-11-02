
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class sJointFixedDesc(HelperObject):
    schema_name = "sJointFixedDesc"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sJointFixedDesc
        return sJointFixedDesc(entlib.load_node_file(sourcefile, entlib.get_schema(sJointFixedDesc.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sJointFixedDesc
        return sJointFixedDesc(entlib.make_node(sJointFixedDesc.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




