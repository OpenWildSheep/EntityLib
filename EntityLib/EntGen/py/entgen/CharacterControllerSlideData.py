
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class CharacterControllerSlideData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CharacterControllerSlideData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CharacterControllerSlideData
        return CharacterControllerSlideData(entlib.load_node_file(sourcefile, entlib.get_schema(CharacterControllerSlideData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CharacterControllerSlideData
        return CharacterControllerSlideData(entlib.make_node(CharacterControllerSlideData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def adherenceRecoverSpeedDependingOnTheSlope(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("adherenceRecoverSpeedDependingOnTheSlope"))
    @property
    def adherenceThresholdHysteresis(self):  # type: ()->Float
        return Float(self._node.at("adherenceThresholdHysteresis"))
    @adherenceThresholdHysteresis.setter
    def adherenceThresholdHysteresis(self, val): self.adherenceThresholdHysteresis.set(val)
    @property
    def adherenceThresholdRequiredToKeepControl(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("adherenceThresholdRequiredToKeepControl"))
    @property
    def adherenceUsingDownwardSlopeDirection(self):  # type: ()->Float
        return Float(self._node.at("adherenceUsingDownwardSlopeDirection"))
    @adherenceUsingDownwardSlopeDirection.setter
    def adherenceUsingDownwardSlopeDirection(self, val): self.adherenceUsingDownwardSlopeDirection.set(val)
    @property
    def adherenceUsingSideSlopeDirection(self):  # type: ()->Float
        return Float(self._node.at("adherenceUsingSideSlopeDirection"))
    @adherenceUsingSideSlopeDirection.setter
    def adherenceUsingSideSlopeDirection(self, val): self.adherenceUsingSideSlopeDirection.set(val)
    @property
    def adherenceUsingUpwardSlopeDirection(self):  # type: ()->Float
        return Float(self._node.at("adherenceUsingUpwardSlopeDirection"))
    @adherenceUsingUpwardSlopeDirection.setter
    def adherenceUsingUpwardSlopeDirection(self, val): self.adherenceUsingUpwardSlopeDirection.set(val)
    @property
    def animblendInTime(self):  # type: ()->Float
        return Float(self._node.at("animblendInTime"))
    @animblendInTime.setter
    def animblendInTime(self, val): self.animblendInTime.set(val)
    @property
    def friction(self):  # type: ()->Float
        return Float(self._node.at("friction"))
    @friction.setter
    def friction(self, val): self.friction.set(val)
    @property
    def maxSlopeAngle(self):  # type: ()->Float
        return Float(self._node.at("maxSlopeAngle"))
    @maxSlopeAngle.setter
    def maxSlopeAngle(self, val): self.maxSlopeAngle.set(val)
    @property
    def speedMediumCoeffHysteresis(self):  # type: ()->Float
        return Float(self._node.at("speedMediumCoeffHysteresis"))
    @speedMediumCoeffHysteresis.setter
    def speedMediumCoeffHysteresis(self, val): self.speedMediumCoeffHysteresis.set(val)
    @property
    def speedMediumCoeffIn(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("speedMediumCoeffIn"))
    @property
    def speedMediumCoeffMin(self):  # type: ()->Float
        return Float(self._node.at("speedMediumCoeffMin"))
    @speedMediumCoeffMin.setter
    def speedMediumCoeffMin(self, val): self.speedMediumCoeffMin.set(val)
    pass




