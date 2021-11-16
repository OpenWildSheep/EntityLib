
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Bool import *

from EntityLibPy import Node

class ActionChangeMount(HelperObject):
    schema_name = "ActionChangeMount"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionChangeMount
        return ActionChangeMount(entlib.load_node_file(sourcefile, entlib.get_schema(ActionChangeMount.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionChangeMount
        return ActionChangeMount(entlib.make_node(ActionChangeMount.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def UseSlowMotion(self):  # type: ()->Bool
        return Bool(self._node.at("UseSlowMotion"))
    @UseSlowMotion.setter
    def UseSlowMotion(self, val): self.UseSlowMotion.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




