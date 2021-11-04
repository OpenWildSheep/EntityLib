
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *

from EntityLibPy import Node

class HealPumpGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/HealPumpGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->HealPumpGD
        return HealPumpGD(entlib.load_node_file(sourcefile, entlib.get_schema(HealPumpGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->HealPumpGD
        return HealPumpGD(entlib.make_node(HealPumpGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AlliesLifeAgentPerSecond(self):  # type: ()->Float
        return Float(self._node.at("AlliesLifeAgentPerSecond"))
    @AlliesLifeAgentPerSecond.setter
    def AlliesLifeAgentPerSecond(self, val): self.AlliesLifeAgentPerSecond.set(val)
    @property
    def EnemiesLifeAgentPerSecond(self):  # type: ()->Float
        return Float(self._node.at("EnemiesLifeAgentPerSecond"))
    @EnemiesLifeAgentPerSecond.setter
    def EnemiesLifeAgentPerSecond(self, val): self.EnemiesLifeAgentPerSecond.set(val)
    @property
    def LifeAmountRatio(self):  # type: ()->Float
        return Float(self._node.at("LifeAmountRatio"))
    @LifeAmountRatio.setter
    def LifeAmountRatio(self, val): self.LifeAmountRatio.set(val)
    @property
    def Range(self):  # type: ()->Float
        return Float(self._node.at("Range"))
    @Range.setter
    def Range(self, val): self.Range.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




