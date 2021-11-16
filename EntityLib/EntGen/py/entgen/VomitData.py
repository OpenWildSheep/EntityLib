
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.Vector2 import *

from EntityLibPy import Node

class VomitData(HelperObject):
    schema_name = "VomitData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->VomitData
        return VomitData(entlib.load_node_file(sourcefile, entlib.get_schema(VomitData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->VomitData
        return VomitData(entlib.make_node(VomitData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AngleRangeHysteresis(self):  # type: ()->Vector2
        return Vector2(self._node.at("AngleRangeHysteresis"))
    @AngleRangeHysteresis.setter
    def AngleRangeHysteresis(self, val): self.AngleRangeHysteresis.set(val)
    @property
    def AngleRangeMax(self):  # type: ()->Vector2
        return Vector2(self._node.at("AngleRangeMax"))
    @AngleRangeMax.setter
    def AngleRangeMax(self, val): self.AngleRangeMax.set(val)
    @property
    def CanVomit(self):  # type: ()->Bool
        return Bool(self._node.at("CanVomit"))
    @CanVomit.setter
    def CanVomit(self, val): self.CanVomit.set(val)
    @property
    def ProjectileName(self):  # type: ()->String
        return String(self._node.at("ProjectileName"))
    @ProjectileName.setter
    def ProjectileName(self, val): self.ProjectileName.set(val)
    @property
    def VomitCost(self):  # type: ()->Float
        return Float(self._node.at("VomitCost"))
    @VomitCost.setter
    def VomitCost(self, val): self.VomitCost.set(val)
    @property
    def VomitMinTimer(self):  # type: ()->Float
        return Float(self._node.at("VomitMinTimer"))
    @VomitMinTimer.setter
    def VomitMinTimer(self, val): self.VomitMinTimer.set(val)
    @property
    def VomitRate(self):  # type: ()->Float
        return Float(self._node.at("VomitRate"))
    @VomitRate.setter
    def VomitRate(self, val): self.VomitRate.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




