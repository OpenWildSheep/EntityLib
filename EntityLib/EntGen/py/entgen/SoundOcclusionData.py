
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class SoundOcclusionData(HelperObject):
    schema_name = "SoundOcclusionData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SoundOcclusionData
        return SoundOcclusionData(entlib.load_node_file(sourcefile, entlib.get_schema(SoundOcclusionData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SoundOcclusionData
        return SoundOcclusionData(entlib.make_node(SoundOcclusionData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def OcclusionMaxRatioAdjustRate(self):  # type: ()->Float
        return Float(self._node.at("OcclusionMaxRatioAdjustRate"))
    @OcclusionMaxRatioAdjustRate.setter
    def OcclusionMaxRatioAdjustRate(self, val): self.OcclusionMaxRatioAdjustRate.set(val)
    @property
    def OcclusionMaxThickness(self):  # type: ()->Float
        return Float(self._node.at("OcclusionMaxThickness"))
    @OcclusionMaxThickness.setter
    def OcclusionMaxThickness(self, val): self.OcclusionMaxThickness.set(val)
    @property
    def OcclusionRatioAdjustRateFactor(self):  # type: ()->Float
        return Float(self._node.at("OcclusionRatioAdjustRateFactor"))
    @OcclusionRatioAdjustRateFactor.setter
    def OcclusionRatioAdjustRateFactor(self, val): self.OcclusionRatioAdjustRateFactor.set(val)
    @property
    def OcclusionSphereCastRadius(self):  # type: ()->Float
        return Float(self._node.at("OcclusionSphereCastRadius"))
    @OcclusionSphereCastRadius.setter
    def OcclusionSphereCastRadius(self, val): self.OcclusionSphereCastRadius.set(val)
    @property
    def OcclusionSphereCastVerticalOffset(self):  # type: ()->Float
        return Float(self._node.at("OcclusionSphereCastVerticalOffset"))
    @OcclusionSphereCastVerticalOffset.setter
    def OcclusionSphereCastVerticalOffset(self, val): self.OcclusionSphereCastVerticalOffset.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




