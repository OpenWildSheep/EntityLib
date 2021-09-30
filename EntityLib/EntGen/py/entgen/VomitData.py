
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.Vector2 import *


class VomitData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/VomitData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(VomitData.schema_name))
    @property
    def AngleRangeHysteresis(self): return Vector2(self._node.at("AngleRangeHysteresis"))
    @AngleRangeHysteresis.setter
    def AngleRangeHysteresis(self, val): self.AngleRangeHysteresis.set(val)
    @property
    def AngleRangeMax(self): return Vector2(self._node.at("AngleRangeMax"))
    @AngleRangeMax.setter
    def AngleRangeMax(self, val): self.AngleRangeMax.set(val)
    @property
    def CanVomit(self): return Bool(self._node.at("CanVomit"))
    @CanVomit.setter
    def CanVomit(self, val): self.CanVomit.set(val)
    @property
    def ProjectileName(self): return String(self._node.at("ProjectileName"))
    @ProjectileName.setter
    def ProjectileName(self, val): self.ProjectileName.set(val)
    @property
    def VomitCost(self): return Float(self._node.at("VomitCost"))
    @VomitCost.setter
    def VomitCost(self, val): self.VomitCost.set(val)
    @property
    def VomitMinTimer(self): return Float(self._node.at("VomitMinTimer"))
    @VomitMinTimer.setter
    def VomitMinTimer(self, val): self.VomitMinTimer.set(val)
    @property
    def VomitRate(self): return Float(self._node.at("VomitRate"))
    @VomitRate.setter
    def VomitRate(self, val): self.VomitRate.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




