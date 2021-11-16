
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Bool import *

from EntityLibPy import Node

class ActorStateDucking(HelperObject):
    schema_name = "ActorStateDucking"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateDucking
        return ActorStateDucking(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateDucking.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateDucking
        return ActorStateDucking(entlib.make_node(ActorStateDucking.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ExitRequired(self):  # type: ()->Bool
        return Bool(self._node.at("ExitRequired"))
    @ExitRequired.setter
    def ExitRequired(self, val): self.ExitRequired.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




