
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.ActorState import *

from EntityLibPy import Node

class ActionChangeRidingSpot(HelperObject):
    schema_name = "ActionChangeRidingSpot"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionChangeRidingSpot
        return ActionChangeRidingSpot(entlib.load_node_file(sourcefile, entlib.get_schema(ActionChangeRidingSpot.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionChangeRidingSpot
        return ActionChangeRidingSpot(entlib.make_node(ActionChangeRidingSpot.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def TargetHotspotDestID(self):  # type: ()->Int
        return Int(self._node.at("TargetHotspotDestID"))
    @TargetHotspotDestID.setter
    def TargetHotspotDestID(self, val): self.TargetHotspotDestID.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




