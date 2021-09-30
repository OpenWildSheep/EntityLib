
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *


class EntityStateMask(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EntityStateMask"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateMask.schema_name))
    @property
    def MaskMeshPath(self): return String(self._node.at("MaskMeshPath"))
    @MaskMeshPath.setter
    def MaskMeshPath(self, val): self.MaskMeshPath.set(val)
    @property
    def Super(self): return ActorState(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




