
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Position import *

from EntityLibPy import Node

class EntityStateBoidsHomePos(HelperObject):
    schema_name = "EntityStateBoidsHomePos"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateBoidsHomePos
        return EntityStateBoidsHomePos(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateBoidsHomePos.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateBoidsHomePos
        return EntityStateBoidsHomePos(entlib.make_node(EntityStateBoidsHomePos.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def HomePosition(self):  # type: ()->Position
        return Position(self._node.at("HomePosition"))
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




