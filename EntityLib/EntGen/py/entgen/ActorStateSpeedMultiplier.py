
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Float import *

from EntityLibPy import Node

class ActorStateSpeedMultiplier(HelperObject):
    schema_name = "ActorStateSpeedMultiplier"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateSpeedMultiplier
        return ActorStateSpeedMultiplier(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateSpeedMultiplier.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateSpeedMultiplier
        return ActorStateSpeedMultiplier(entlib.make_node(ActorStateSpeedMultiplier.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def SpeedMultiplier(self):  # type: ()->Float
        return Float(self._node.at("SpeedMultiplier"))
    @SpeedMultiplier.setter
    def SpeedMultiplier(self, val): self.SpeedMultiplier.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




