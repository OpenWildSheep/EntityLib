
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class UnifiedPhysicsDataGD(HelperObject):
    schema_name = "UnifiedPhysicsDataGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->UnifiedPhysicsDataGD
        return UnifiedPhysicsDataGD(entlib.load_node_file(sourcefile, entlib.get_schema(UnifiedPhysicsDataGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->UnifiedPhysicsDataGD
        return UnifiedPhysicsDataGD(entlib.make_node(UnifiedPhysicsDataGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




