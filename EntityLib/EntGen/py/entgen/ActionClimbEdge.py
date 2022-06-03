
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.LedgePositionInfo import *

from EntityLibPy import Node

class ActionClimbEdge(HelperObject):
    schema_name = "ActionClimbEdge"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionClimbEdge
        return ActionClimbEdge(entlib.load_node_file(sourcefile, entlib.get_schema(ActionClimbEdge.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionClimbEdge
        return ActionClimbEdge(entlib.make_node(ActionClimbEdge.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def ledgePosInfo(self):  # type: ()->LedgePositionInfo
        return LedgePositionInfo(self._node.at("ledgePosInfo"))
    pass




