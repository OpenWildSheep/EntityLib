
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *


class RespawnPlaceGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/RespawnPlaceGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(RespawnPlaceGD.schema_name))
    @property
    def AlwaysAvailable(self): return Bool(self._node.at("AlwaysAvailable"))
    @AlwaysAvailable.setter
    def AlwaysAvailable(self, val): self.AlwaysAvailable.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




