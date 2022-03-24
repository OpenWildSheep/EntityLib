
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class RespawnPlaceGD(HelperObject):
    schema_name = "RespawnPlaceGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RespawnPlaceGD
        return RespawnPlaceGD(entlib.load_node_file(sourcefile, entlib.get_schema(RespawnPlaceGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RespawnPlaceGD
        return RespawnPlaceGD(entlib.make_node(RespawnPlaceGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AlwaysAvailable(self):  # type: ()->Bool
        return Bool(self._node.at("AlwaysAvailable"))
    @AlwaysAvailable.setter
    def AlwaysAvailable(self, val): self.AlwaysAvailable.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




