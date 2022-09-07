
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.ComponentGD import *
from entgen.Float import *

from EntityLibPy import Node

class WallRunGD(HelperObject):
    schema_name = "WallRunGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->WallRunGD
        return WallRunGD(entlib.load_node_file(sourcefile, entlib.get_schema(WallRunGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->WallRunGD
        return WallRunGD(entlib.make_node(WallRunGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def dropAirControlDelay(self):  # type: ()->Float
        return Float(self._node.at("dropAirControlDelay"))
    @dropAirControlDelay.setter
    def dropAirControlDelay(self, val): self.dropAirControlDelay.set(val)
    @property
    def dropCoyoteJumpMaxTime(self):  # type: ()->Float
        return Float(self._node.at("dropCoyoteJumpMaxTime"))
    @dropCoyoteJumpMaxTime.setter
    def dropCoyoteJumpMaxTime(self, val): self.dropCoyoteJumpMaxTime.set(val)
    @property
    def dropDelayAfterInvalidDirectionRequested(self):  # type: ()->Float
        return Float(self._node.at("dropDelayAfterInvalidDirectionRequested"))
    @dropDelayAfterInvalidDirectionRequested.setter
    def dropDelayAfterInvalidDirectionRequested(self, val): self.dropDelayAfterInvalidDirectionRequested.set(val)
    @property
    def dropTrajectoryRotationYaw(self):  # type: ()->Float
        return Float(self._node.at("dropTrajectoryRotationYaw"))
    @dropTrajectoryRotationYaw.setter
    def dropTrajectoryRotationYaw(self, val): self.dropTrajectoryRotationYaw.set(val)
    @property
    def dropVisualRotationYawRateFactor(self):  # type: ()->Float
        return Float(self._node.at("dropVisualRotationYawRateFactor"))
    @dropVisualRotationYawRateFactor.setter
    def dropVisualRotationYawRateFactor(self, val): self.dropVisualRotationYawRateFactor.set(val)
    @property
    def jumpRiseMinCoeffToEnter(self):  # type: ()->Float
        return Float(self._node.at("jumpRiseMinCoeffToEnter"))
    @jumpRiseMinCoeffToEnter.setter
    def jumpRiseMinCoeffToEnter(self, val): self.jumpRiseMinCoeffToEnter.set(val)
    @property
    def jumpTrajectoryRotationYaw(self):  # type: ()->Float
        return Float(self._node.at("jumpTrajectoryRotationYaw"))
    @jumpTrajectoryRotationYaw.setter
    def jumpTrajectoryRotationYaw(self, val): self.jumpTrajectoryRotationYaw.set(val)
    @property
    def jumpVisualRotationYawRateFactor(self):  # type: ()->Float
        return Float(self._node.at("jumpVisualRotationYawRateFactor"))
    @jumpVisualRotationYawRateFactor.setter
    def jumpVisualRotationYawRateFactor(self, val): self.jumpVisualRotationYawRateFactor.set(val)
    @property
    def probeLengthCoeff(self):  # type: ()->Float
        return Float(self._node.at("probeLengthCoeff"))
    @probeLengthCoeff.setter
    def probeLengthCoeff(self, val): self.probeLengthCoeff.set(val)
    @property
    def probeRadiusCoeff(self):  # type: ()->Float
        return Float(self._node.at("probeRadiusCoeff"))
    @probeRadiusCoeff.setter
    def probeRadiusCoeff(self, val): self.probeRadiusCoeff.set(val)
    @property
    def probeRayCastCount(self):  # type: ()->Int
        return Int(self._node.at("probeRayCastCount"))
    @probeRayCastCount.setter
    def probeRayCastCount(self, val): self.probeRayCastCount.set(val)
    @property
    def probeRotationAngle(self):  # type: ()->Float
        return Float(self._node.at("probeRotationAngle"))
    @probeRotationAngle.setter
    def probeRotationAngle(self, val): self.probeRotationAngle.set(val)
    @property
    def runDurationMax(self):  # type: ()->Float
        return Float(self._node.at("runDurationMax"))
    @runDurationMax.setter
    def runDurationMax(self, val): self.runDurationMax.set(val)
    @property
    def runDurationMin(self):  # type: ()->Float
        return Float(self._node.at("runDurationMin"))
    @runDurationMin.setter
    def runDurationMin(self, val): self.runDurationMin.set(val)
    @property
    def runForwardSpeedNormMinToEnter(self):  # type: ()->Float
        return Float(self._node.at("runForwardSpeedNormMinToEnter"))
    @runForwardSpeedNormMinToEnter.setter
    def runForwardSpeedNormMinToEnter(self, val): self.runForwardSpeedNormMinToEnter.set(val)
    @property
    def runOrientationRateFactor(self):  # type: ()->Float
        return Float(self._node.at("runOrientationRateFactor"))
    @runOrientationRateFactor.setter
    def runOrientationRateFactor(self, val): self.runOrientationRateFactor.set(val)
    @property
    def runRequiredDirectionDeltaAngleMax(self):  # type: ()->Float
        return Float(self._node.at("runRequiredDirectionDeltaAngleMax"))
    @runRequiredDirectionDeltaAngleMax.setter
    def runRequiredDirectionDeltaAngleMax(self, val): self.runRequiredDirectionDeltaAngleMax.set(val)
    @property
    def runRequiredDirectionDeltaAngleMin(self):  # type: ()->Float
        return Float(self._node.at("runRequiredDirectionDeltaAngleMin"))
    @runRequiredDirectionDeltaAngleMin.setter
    def runRequiredDirectionDeltaAngleMin(self, val): self.runRequiredDirectionDeltaAngleMin.set(val)
    @property
    def runRequiredSpeedNormMin(self):  # type: ()->Float
        return Float(self._node.at("runRequiredSpeedNormMin"))
    @runRequiredSpeedNormMin.setter
    def runRequiredSpeedNormMin(self, val): self.runRequiredSpeedNormMin.set(val)
    @property
    def runSightDeltaAngleMaxtoEnter(self):  # type: ()->Float
        return Float(self._node.at("runSightDeltaAngleMaxtoEnter"))
    @runSightDeltaAngleMaxtoEnter.setter
    def runSightDeltaAngleMaxtoEnter(self, val): self.runSightDeltaAngleMaxtoEnter.set(val)
    @property
    def runSlopeAngleHysteresis(self):  # type: ()->Float
        return Float(self._node.at("runSlopeAngleHysteresis"))
    @runSlopeAngleHysteresis.setter
    def runSlopeAngleHysteresis(self, val): self.runSlopeAngleHysteresis.set(val)
    @property
    def runSlopeAngleMax(self):  # type: ()->Float
        return Float(self._node.at("runSlopeAngleMax"))
    @runSlopeAngleMax.setter
    def runSlopeAngleMax(self, val): self.runSlopeAngleMax.set(val)
    @property
    def runSlopeAngleMin(self):  # type: ()->Float
        return Float(self._node.at("runSlopeAngleMin"))
    @runSlopeAngleMin.setter
    def runSlopeAngleMin(self, val): self.runSlopeAngleMin.set(val)
    @property
    def runTrajectoryRotationPitchCurveResourcePath(self):  # type: ()->String
        return String(self._node.at("runTrajectoryRotationPitchCurveResourcePath"))
    @runTrajectoryRotationPitchCurveResourcePath.setter
    def runTrajectoryRotationPitchCurveResourcePath(self, val): self.runTrajectoryRotationPitchCurveResourcePath.set(val)
    @property
    def runTrajectoryRotationYaw(self):  # type: ()->Float
        return Float(self._node.at("runTrajectoryRotationYaw"))
    @runTrajectoryRotationYaw.setter
    def runTrajectoryRotationYaw(self, val): self.runTrajectoryRotationYaw.set(val)
    @property
    def runVerticalSpeedNormMaxToEnter(self):  # type: ()->Float
        return Float(self._node.at("runVerticalSpeedNormMaxToEnter"))
    @runVerticalSpeedNormMaxToEnter.setter
    def runVerticalSpeedNormMaxToEnter(self, val): self.runVerticalSpeedNormMaxToEnter.set(val)
    @property
    def runVerticalSpeedNormMinToEnter(self):  # type: ()->Float
        return Float(self._node.at("runVerticalSpeedNormMinToEnter"))
    @runVerticalSpeedNormMinToEnter.setter
    def runVerticalSpeedNormMinToEnter(self, val): self.runVerticalSpeedNormMinToEnter.set(val)
    pass




