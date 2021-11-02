
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Manager import *
from entgen.Float import *

from EntityLibPy import Node

class PerceptionManager(HelperObject):
    schema_name = "PerceptionManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PerceptionManager
        return PerceptionManager(entlib.load_node_file(sourcefile, entlib.get_schema(PerceptionManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PerceptionManager
        return PerceptionManager(entlib.make_node(PerceptionManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DistanceMultipliers(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("DistanceMultipliers"))
    @DistanceMultipliers.setter
    def DistanceMultipliers(self, val): self.DistanceMultipliers.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




