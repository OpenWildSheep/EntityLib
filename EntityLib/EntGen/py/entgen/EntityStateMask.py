
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class EntityStateMask(HelperObject):
    schema_name = "EntityStateMask"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateMask
        return EntityStateMask(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateMask.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateMask
        return EntityStateMask(entlib.make_node(EntityStateMask.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def MaskMeshPath(self):  # type: ()->String
        return String(self._node.at("MaskMeshPath"))
    @MaskMeshPath.setter
    def MaskMeshPath(self, val): self.MaskMeshPath.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




