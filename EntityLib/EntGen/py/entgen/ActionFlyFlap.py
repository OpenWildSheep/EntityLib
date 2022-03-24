
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class ActionFlyFlap(HelperObject):
    schema_name = "ActionFlyFlap"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionFlyFlap
        return ActionFlyFlap(entlib.load_node_file(sourcefile, entlib.get_schema(ActionFlyFlap.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionFlyFlap
        return ActionFlyFlap(entlib.make_node(ActionFlyFlap.schema_name))
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




