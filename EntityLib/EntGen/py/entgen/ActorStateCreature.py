
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Position import *
from entgen.Quat import *

from EntityLibPy import Node

class ActorStateCreature(HelperObject):
    schema_name = "ActorStateCreature"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateCreature
        return ActorStateCreature(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateCreature.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateCreature
        return ActorStateCreature(entlib.make_node(ActorStateCreature.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Position(self):  # type: ()->Position
        return Position(self._node.at("Position"))
    @property
    def Rotation(self):  # type: ()->Quat
        return Quat(self._node.at("Rotation"))
    @Rotation.setter
    def Rotation(self, val): self.Rotation.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




