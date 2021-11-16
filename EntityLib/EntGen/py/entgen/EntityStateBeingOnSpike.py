
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Float import *

from EntityLibPy import Node

class EntityStateBeingOnSpike(HelperObject):
    schema_name = "EntityStateBeingOnSpike"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateBeingOnSpike
        return EntityStateBeingOnSpike(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateBeingOnSpike.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateBeingOnSpike
        return EntityStateBeingOnSpike(entlib.make_node(EntityStateBeingOnSpike.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def SpikeCooldown(self):  # type: ()->Float
        return Float(self._node.at("SpikeCooldown"))
    @SpikeCooldown.setter
    def SpikeCooldown(self, val): self.SpikeCooldown.set(val)
    @property
    def SpikeDamage(self):  # type: ()->Float
        return Float(self._node.at("SpikeDamage"))
    @SpikeDamage.setter
    def SpikeDamage(self, val): self.SpikeDamage.set(val)
    @property
    def SpikeImpact(self):  # type: ()->Float
        return Float(self._node.at("SpikeImpact"))
    @SpikeImpact.setter
    def SpikeImpact(self, val): self.SpikeImpact.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




