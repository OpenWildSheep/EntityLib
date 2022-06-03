
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActionShakeOffInputs import *
from entgen.ActorState import *

from EntityLibPy import Node

class ActionShakeOff(HelperObject):
    schema_name = "ActionShakeOff"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionShakeOff
        return ActionShakeOff(entlib.load_node_file(sourcefile, entlib.get_schema(ActionShakeOff.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionShakeOff
        return ActionShakeOff(entlib.make_node(ActionShakeOff.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Inputs(self):  # type: ()->ActionShakeOffInputs
        return ActionShakeOffInputs(self._node.at("Inputs"))
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




