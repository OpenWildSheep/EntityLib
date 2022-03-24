
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Bool import *
from entgen.Float import *

from EntityLibPy import Node

class ActionPlayAnim(HelperObject):
    schema_name = "ActionPlayAnim"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionPlayAnim
        return ActionPlayAnim(entlib.load_node_file(sourcefile, entlib.get_schema(ActionPlayAnim.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionPlayAnim
        return ActionPlayAnim(entlib.make_node(ActionPlayAnim.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def MaxTime(self):  # type: ()->Float
        return Float(self._node.at("MaxTime"))
    @MaxTime.setter
    def MaxTime(self, val): self.MaxTime.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def exitRequired(self):  # type: ()->Bool
        return Bool(self._node.at("exitRequired"))
    @exitRequired.setter
    def exitRequired(self, val): self.exitRequired.set(val)
    pass




