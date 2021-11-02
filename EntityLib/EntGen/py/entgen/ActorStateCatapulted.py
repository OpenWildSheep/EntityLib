
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class ActorStateCatapulted(HelperObject):
    schema_name = "ActorStateCatapulted"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateCatapulted
        return ActorStateCatapulted(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateCatapulted.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateCatapulted
        return ActorStateCatapulted(entlib.make_node(ActorStateCatapulted.schema_name))
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




