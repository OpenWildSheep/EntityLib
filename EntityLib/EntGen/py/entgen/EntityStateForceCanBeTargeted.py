
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Bool import *


class EntityStateForceCanBeTargeted(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EntityStateForceCanBeTargeted"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateForceCanBeTargeted.schema_name))
    @property
    def CanBeTargeted(self): return Bool(self._node.at("CanBeTargeted"))
    @CanBeTargeted.setter
    def CanBeTargeted(self, val): self.CanBeTargeted.set(val)
    @property
    def Super(self): return ActorState(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




