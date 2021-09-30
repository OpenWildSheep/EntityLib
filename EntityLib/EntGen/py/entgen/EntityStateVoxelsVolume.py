
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *


class EntityStateVoxelsVolume(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EntityStateVoxelsVolume"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateVoxelsVolume.schema_name))
    @property
    def Super(self): return ActorState(self._node.at("Super"))
    @property
    def VoxelsState(self): return String(self._node.at("VoxelsState"))
    @VoxelsState.setter
    def VoxelsState(self, val): self.VoxelsState.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




