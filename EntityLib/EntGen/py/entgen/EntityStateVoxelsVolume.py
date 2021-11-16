
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class EntityStateVoxelsVolume(HelperObject):
    schema_name = "EntityStateVoxelsVolume"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateVoxelsVolume
        return EntityStateVoxelsVolume(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateVoxelsVolume.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateVoxelsVolume
        return EntityStateVoxelsVolume(entlib.make_node(EntityStateVoxelsVolume.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def VoxelsState(self):  # type: ()->String
        return String(self._node.at("VoxelsState"))
    @VoxelsState.setter
    def VoxelsState(self, val): self.VoxelsState.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




