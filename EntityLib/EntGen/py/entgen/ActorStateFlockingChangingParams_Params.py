
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Bool import *
from entgen.Float import *

from EntityLibPy import Node

class ActorStateFlockingChangingParams_Params(HelperObject):
    schema_name = "ActorStateFlockingChangingParams::Params"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateFlockingChangingParams_Params
        return ActorStateFlockingChangingParams_Params(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateFlockingChangingParams_Params.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateFlockingChangingParams_Params
        return ActorStateFlockingChangingParams_Params(entlib.make_node(ActorStateFlockingChangingParams_Params.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ApplyAfterCurrent(self):  # type: ()->Bool
        return Bool(self._node.at("ApplyAfterCurrent"))
    @ApplyAfterCurrent.setter
    def ApplyAfterCurrent(self, val): self.ApplyAfterCurrent.set(val)
    @property
    def ApplyOnBud(self):  # type: ()->Bool
        return Bool(self._node.at("ApplyOnBud"))
    @ApplyOnBud.setter
    def ApplyOnBud(self, val): self.ApplyOnBud.set(val)
    @property
    def DelayRandom(self):  # type: ()->Float
        return Float(self._node.at("DelayRandom"))
    @DelayRandom.setter
    def DelayRandom(self, val): self.DelayRandom.set(val)
    @property
    def DelayStatic(self):  # type: ()->Float
        return Float(self._node.at("DelayStatic"))
    @DelayStatic.setter
    def DelayStatic(self, val): self.DelayStatic.set(val)
    @property
    def Hash(self):  # type: ()->String
        return String(self._node.at("Hash"))
    @Hash.setter
    def Hash(self, val): self.Hash.set(val)
    @property
    def Layer(self):  # type: ()->Int
        return Int(self._node.at("Layer"))
    @Layer.setter
    def Layer(self, val): self.Layer.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




