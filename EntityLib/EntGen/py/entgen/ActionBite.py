
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Float import *

from EntityLibPy import Node

class ActionBite(HelperObject):
    schema_name = "ActionBite"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionBite
        return ActionBite(entlib.load_node_file(sourcefile, entlib.get_schema(ActionBite.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionBite
        return ActionBite(entlib.make_node(ActionBite.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def RadiusMultiplier(self):  # type: ()->Float
        return Float(self._node.at("RadiusMultiplier"))
    @RadiusMultiplier.setter
    def RadiusMultiplier(self, val): self.RadiusMultiplier.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




