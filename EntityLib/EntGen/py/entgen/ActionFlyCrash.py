
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class ActionFlyCrash(HelperObject):
    schema_name = "ActionFlyCrash"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionFlyCrash
        return ActionFlyCrash(entlib.load_node_file(sourcefile, entlib.get_schema(ActionFlyCrash.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionFlyCrash
        return ActionFlyCrash(entlib.make_node(ActionFlyCrash.schema_name))
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
    pass




