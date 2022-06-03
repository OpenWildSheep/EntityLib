
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Float import *

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
    def AirControlMultiplier(self):  # type: ()->Float
        return Float(self._node.at("AirControlMultiplier"))
    @AirControlMultiplier.setter
    def AirControlMultiplier(self, val): self.AirControlMultiplier.set(val)
    @property
    def FallHeightProtection(self):  # type: ()->Float
        return Float(self._node.at("FallHeightProtection"))
    @FallHeightProtection.setter
    def FallHeightProtection(self, val): self.FallHeightProtection.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




