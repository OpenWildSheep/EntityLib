
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Bool import *
from entgen.Hit import *

from EntityLibPy import Node

class ActionHit(HelperObject):
    schema_name = "ActionHit"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionHit
        return ActionHit(entlib.load_node_file(sourcefile, entlib.get_schema(ActionHit.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionHit
        return ActionHit(entlib.make_node(ActionHit.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Hit(self):  # type: ()->Hit
        return Hit(self._node.at("Hit"))
    @property
    def NoAnimNeeded(self):  # type: ()->Bool
        return Bool(self._node.at("NoAnimNeeded"))
    @NoAnimNeeded.setter
    def NoAnimNeeded(self, val): self.NoAnimNeeded.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def TransferAllowed(self):  # type: ()->Bool
        return Bool(self._node.at("TransferAllowed"))
    @TransferAllowed.setter
    def TransferAllowed(self, val): self.TransferAllowed.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




