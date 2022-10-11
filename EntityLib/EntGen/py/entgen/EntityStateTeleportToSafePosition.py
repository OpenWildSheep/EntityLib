
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Float import *

from EntityLibPy import Node

class EntityStateTeleportToSafePosition(HelperObject):
    schema_name = "EntityStateTeleportToSafePosition"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateTeleportToSafePosition
        return EntityStateTeleportToSafePosition(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateTeleportToSafePosition.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateTeleportToSafePosition
        return EntityStateTeleportToSafePosition(entlib.make_node(EntityStateTeleportToSafePosition.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def FadeInDelay(self):  # type: ()->Float
        return Float(self._node.at("FadeInDelay"))
    @FadeInDelay.setter
    def FadeInDelay(self, val): self.FadeInDelay.set(val)
    @property
    def FadeInTime(self):  # type: ()->Float
        return Float(self._node.at("FadeInTime"))
    @FadeInTime.setter
    def FadeInTime(self, val): self.FadeInTime.set(val)
    @property
    def FadeOutDelay(self):  # type: ()->Float
        return Float(self._node.at("FadeOutDelay"))
    @FadeOutDelay.setter
    def FadeOutDelay(self, val): self.FadeOutDelay.set(val)
    @property
    def FadeOutTime(self):  # type: ()->Float
        return Float(self._node.at("FadeOutTime"))
    @FadeOutTime.setter
    def FadeOutTime(self, val): self.FadeOutTime.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




