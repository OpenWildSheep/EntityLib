
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *


class HealPumpGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/HealPumpGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(HealPumpGD.schema_name))
    @property
    def AlliesLifeAgentPerSecond(self): return Float(self._node.at("AlliesLifeAgentPerSecond"))
    @AlliesLifeAgentPerSecond.setter
    def AlliesLifeAgentPerSecond(self, val): self.AlliesLifeAgentPerSecond.set(val)
    @property
    def EnemiesLifeAgentPerSecond(self): return Float(self._node.at("EnemiesLifeAgentPerSecond"))
    @EnemiesLifeAgentPerSecond.setter
    def EnemiesLifeAgentPerSecond(self, val): self.EnemiesLifeAgentPerSecond.set(val)
    @property
    def LifeAmountRatio(self): return Float(self._node.at("LifeAmountRatio"))
    @LifeAmountRatio.setter
    def LifeAmountRatio(self, val): self.LifeAmountRatio.set(val)
    @property
    def Range(self): return Float(self._node.at("Range"))
    @Range.setter
    def Range(self, val): self.Range.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




