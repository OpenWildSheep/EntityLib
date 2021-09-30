
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Position import *


class EntityStateBoidsHomePos(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EntityStateBoidsHomePos"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateBoidsHomePos.schema_name))
    @property
    def HomePosition(self): return Position(self._node.at("HomePosition"))
    @property
    def Super(self): return ActorState(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




