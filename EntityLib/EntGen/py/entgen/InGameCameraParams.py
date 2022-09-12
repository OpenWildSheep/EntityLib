
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.ActionMode import *
from entgen.AnimTag import *
from entgen.AutoRotationType import *
from entgen.CameraType import *
from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.InGameCameraParams_AnticipationJump import *
from entgen.Position import *
from entgen.ScaleConverter import *
from entgen.Vector3 import *

from EntityLibPy import Node

class InGameCameraParams(HelperObject):
    schema_name = "InGameCameraParams"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->InGameCameraParams
        return InGameCameraParams(entlib.load_node_file(sourcefile, entlib.get_schema(InGameCameraParams.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->InGameCameraParams
        return InGameCameraParams(entlib.make_node(InGameCameraParams.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ActivationDelay(self):  # type: ()->Float
        return Float(self._node.at("ActivationDelay"))
    @ActivationDelay.setter
    def ActivationDelay(self, val): self.ActivationDelay.set(val)
    @property
    def AnimAction(self):  # type: ()->ActionMode
        return ActionMode(self._node.at("AnimAction"))
    @AnimAction.setter
    def AnimAction(self, val): self.AnimAction.set(val)
    @property
    def AnimTag(self):  # type: ()->AnimTag
        return AnimTag(self._node.at("AnimTag"))
    @AnimTag.setter
    def AnimTag(self, val): self.AnimTag.set(val)
    @property
    def AnticipationCameraSightTime(self):  # type: ()->Float
        return Float(self._node.at("AnticipationCameraSightTime"))
    @AnticipationCameraSightTime.setter
    def AnticipationCameraSightTime(self, val): self.AnticipationCameraSightTime.set(val)
    @property
    def AnticipationForceReset(self):  # type: ()->Bool
        return Bool(self._node.at("AnticipationForceReset"))
    @AnticipationForceReset.setter
    def AnticipationForceReset(self, val): self.AnticipationForceReset.set(val)
    @property
    def AnticipationJump(self):  # type: ()->InGameCameraParams_AnticipationJump
        return InGameCameraParams_AnticipationJump(self._node.at("AnticipationJump"))
    @property
    def AnticipationMaxPitch(self):  # type: ()->Float
        return Float(self._node.at("AnticipationMaxPitch"))
    @AnticipationMaxPitch.setter
    def AnticipationMaxPitch(self, val): self.AnticipationMaxPitch.set(val)
    @property
    def AnticipationMaxYaw(self):  # type: ()->Float
        return Float(self._node.at("AnticipationMaxYaw"))
    @AnticipationMaxYaw.setter
    def AnticipationMaxYaw(self, val): self.AnticipationMaxYaw.set(val)
    @property
    def AnticipationNoMoveLock(self):  # type: ()->Bool
        return Bool(self._node.at("AnticipationNoMoveLock"))
    @AnticipationNoMoveLock.setter
    def AnticipationNoMoveLock(self, val): self.AnticipationNoMoveLock.set(val)
    @property
    def AnticipationPitchAngleMax(self):  # type: ()->Float
        return Float(self._node.at("AnticipationPitchAngleMax"))
    @AnticipationPitchAngleMax.setter
    def AnticipationPitchAngleMax(self, val): self.AnticipationPitchAngleMax.set(val)
    @property
    def AnticipationPitchAngleMin(self):  # type: ()->Float
        return Float(self._node.at("AnticipationPitchAngleMin"))
    @AnticipationPitchAngleMin.setter
    def AnticipationPitchAngleMin(self, val): self.AnticipationPitchAngleMin.set(val)
    @property
    def AnticipationSmooth(self):  # type: ()->Float
        return Float(self._node.at("AnticipationSmooth"))
    @AnticipationSmooth.setter
    def AnticipationSmooth(self, val): self.AnticipationSmooth.set(val)
    @property
    def AnticipationYawAngleMax(self):  # type: ()->Float
        return Float(self._node.at("AnticipationYawAngleMax"))
    @AnticipationYawAngleMax.setter
    def AnticipationYawAngleMax(self, val): self.AnticipationYawAngleMax.set(val)
    @property
    def AnticipationYawAngleMin(self):  # type: ()->Float
        return Float(self._node.at("AnticipationYawAngleMin"))
    @AnticipationYawAngleMin.setter
    def AnticipationYawAngleMin(self, val): self.AnticipationYawAngleMin.set(val)
    @property
    def AnticipationZSmooth(self):  # type: ()->Float
        return Float(self._node.at("AnticipationZSmooth"))
    @AnticipationZSmooth.setter
    def AnticipationZSmooth(self, val): self.AnticipationZSmooth.set(val)
    @property
    def AntipationYawSpeedForce(self):  # type: ()->Float
        return Float(self._node.at("AntipationYawSpeedForce"))
    @AntipationYawSpeedForce.setter
    def AntipationYawSpeedForce(self, val): self.AntipationYawSpeedForce.set(val)
    @property
    def AntipationYawSpeedForceSmooth(self):  # type: ()->Float
        return Float(self._node.at("AntipationYawSpeedForceSmooth"))
    @AntipationYawSpeedForceSmooth.setter
    def AntipationYawSpeedForceSmooth(self, val): self.AntipationYawSpeedForceSmooth.set(val)
    @property
    def AutoRotate(self):  # type: ()->AutoRotationType
        return AutoRotationType(self._node.at("AutoRotate"))
    @AutoRotate.setter
    def AutoRotate(self, val): self.AutoRotate.set(val)
    @property
    def AutoRotateIdealPitch(self):  # type: ()->Float
        return Float(self._node.at("AutoRotateIdealPitch"))
    @AutoRotateIdealPitch.setter
    def AutoRotateIdealPitch(self, val): self.AutoRotateIdealPitch.set(val)
    @property
    def AutoRotatePitchMaxSpeed(self):  # type: ()->Float
        return Float(self._node.at("AutoRotatePitchMaxSpeed"))
    @AutoRotatePitchMaxSpeed.setter
    def AutoRotatePitchMaxSpeed(self, val): self.AutoRotatePitchMaxSpeed.set(val)
    @property
    def AutoRotatePitchMinAngle(self):  # type: ()->Float
        return Float(self._node.at("AutoRotatePitchMinAngle"))
    @AutoRotatePitchMinAngle.setter
    def AutoRotatePitchMinAngle(self, val): self.AutoRotatePitchMinAngle.set(val)
    @property
    def AutoRotatePitchSpeedSmooth(self):  # type: ()->Float
        return Float(self._node.at("AutoRotatePitchSpeedSmooth"))
    @AutoRotatePitchSpeedSmooth.setter
    def AutoRotatePitchSpeedSmooth(self, val): self.AutoRotatePitchSpeedSmooth.set(val)
    @property
    def AutoRotateRollFactor(self):  # type: ()->Float
        return Float(self._node.at("AutoRotateRollFactor"))
    @AutoRotateRollFactor.setter
    def AutoRotateRollFactor(self, val): self.AutoRotateRollFactor.set(val)
    @property
    def AutoRotateUnlockPitchDelta(self):  # type: ()->Float
        return Float(self._node.at("AutoRotateUnlockPitchDelta"))
    @AutoRotateUnlockPitchDelta.setter
    def AutoRotateUnlockPitchDelta(self, val): self.AutoRotateUnlockPitchDelta.set(val)
    @property
    def AutoRotateUnlockYawDelta(self):  # type: ()->Float
        return Float(self._node.at("AutoRotateUnlockYawDelta"))
    @AutoRotateUnlockYawDelta.setter
    def AutoRotateUnlockYawDelta(self, val): self.AutoRotateUnlockYawDelta.set(val)
    @property
    def AutoRotateYawMaxSpeed(self):  # type: ()->Float
        return Float(self._node.at("AutoRotateYawMaxSpeed"))
    @AutoRotateYawMaxSpeed.setter
    def AutoRotateYawMaxSpeed(self, val): self.AutoRotateYawMaxSpeed.set(val)
    @property
    def AutoRotateYawMinAngle(self):  # type: ()->Float
        return Float(self._node.at("AutoRotateYawMinAngle"))
    @AutoRotateYawMinAngle.setter
    def AutoRotateYawMinAngle(self, val): self.AutoRotateYawMinAngle.set(val)
    @property
    def AutoRotateYawMinSpeed(self):  # type: ()->Float
        return Float(self._node.at("AutoRotateYawMinSpeed"))
    @AutoRotateYawMinSpeed.setter
    def AutoRotateYawMinSpeed(self, val): self.AutoRotateYawMinSpeed.set(val)
    @property
    def AutoRotateYawSpeedSmooth(self):  # type: ()->Float
        return Float(self._node.at("AutoRotateYawSpeedSmooth"))
    @AutoRotateYawSpeedSmooth.setter
    def AutoRotateYawSpeedSmooth(self, val): self.AutoRotateYawSpeedSmooth.set(val)
    @property
    def CameraType(self):  # type: ()->CameraType
        return CameraType(self._node.at("CameraType"))
    @CameraType.setter
    def CameraType(self, val): self.CameraType.set(val)
    @property
    def CollisionBackToPosSpeed(self):  # type: ()->Float
        return Float(self._node.at("CollisionBackToPosSpeed"))
    @CollisionBackToPosSpeed.setter
    def CollisionBackToPosSpeed(self, val): self.CollisionBackToPosSpeed.set(val)
    @property
    def CollisionCorrectionSpeed(self):  # type: ()->Float
        return Float(self._node.at("CollisionCorrectionSpeed"))
    @CollisionCorrectionSpeed.setter
    def CollisionCorrectionSpeed(self, val): self.CollisionCorrectionSpeed.set(val)
    @property
    def CollisionDisabled(self):  # type: ()->Bool
        return Bool(self._node.at("CollisionDisabled"))
    @CollisionDisabled.setter
    def CollisionDisabled(self, val): self.CollisionDisabled.set(val)
    @property
    def CollisionMoveCamBackToPosSpeed(self):  # type: ()->Float
        return Float(self._node.at("CollisionMoveCamBackToPosSpeed"))
    @CollisionMoveCamBackToPosSpeed.setter
    def CollisionMoveCamBackToPosSpeed(self, val): self.CollisionMoveCamBackToPosSpeed.set(val)
    @property
    def CollisionTouchGroundBackToPosSpeed(self):  # type: ()->Float
        return Float(self._node.at("CollisionTouchGroundBackToPosSpeed"))
    @CollisionTouchGroundBackToPosSpeed.setter
    def CollisionTouchGroundBackToPosSpeed(self, val): self.CollisionTouchGroundBackToPosSpeed.set(val)
    @property
    def CollisionTouchGroundModePitchThreshold(self):  # type: ()->Float
        return Float(self._node.at("CollisionTouchGroundModePitchThreshold"))
    @CollisionTouchGroundModePitchThreshold.setter
    def CollisionTouchGroundModePitchThreshold(self, val): self.CollisionTouchGroundModePitchThreshold.set(val)
    @property
    def CollisionWantedNearPlane(self):  # type: ()->Float
        return Float(self._node.at("CollisionWantedNearPlane"))
    @CollisionWantedNearPlane.setter
    def CollisionWantedNearPlane(self, val): self.CollisionWantedNearPlane.set(val)
    @property
    def CollisionZOffset(self):  # type: ()->Float
        return Float(self._node.at("CollisionZOffset"))
    @CollisionZOffset.setter
    def CollisionZOffset(self, val): self.CollisionZOffset.set(val)
    @property
    def CollisionZOffsetMaxRadius(self):  # type: ()->Float
        return Float(self._node.at("CollisionZOffsetMaxRadius"))
    @CollisionZOffsetMaxRadius.setter
    def CollisionZOffsetMaxRadius(self, val): self.CollisionZOffsetMaxRadius.set(val)
    @property
    def CollisionZOffsetSmooth(self):  # type: ()->Float
        return Float(self._node.at("CollisionZOffsetSmooth"))
    @CollisionZOffsetSmooth.setter
    def CollisionZOffsetSmooth(self, val): self.CollisionZOffsetSmooth.set(val)
    @property
    def DOFEnabled(self):  # type: ()->Bool
        return Bool(self._node.at("DOFEnabled"))
    @DOFEnabled.setter
    def DOFEnabled(self, val): self.DOFEnabled.set(val)
    @property
    def DOFFarStart(self):  # type: ()->Float
        return Float(self._node.at("DOFFarStart"))
    @DOFFarStart.setter
    def DOFFarStart(self, val): self.DOFFarStart.set(val)
    @property
    def DOFFarStop(self):  # type: ()->Float
        return Float(self._node.at("DOFFarStop"))
    @DOFFarStop.setter
    def DOFFarStop(self, val): self.DOFFarStop.set(val)
    @property
    def DOFMultiplier(self):  # type: ()->Float
        return Float(self._node.at("DOFMultiplier"))
    @DOFMultiplier.setter
    def DOFMultiplier(self, val): self.DOFMultiplier.set(val)
    @property
    def DOFNearStart(self):  # type: ()->Float
        return Float(self._node.at("DOFNearStart"))
    @DOFNearStart.setter
    def DOFNearStart(self, val): self.DOFNearStart.set(val)
    @property
    def DOFNearStop(self):  # type: ()->Float
        return Float(self._node.at("DOFNearStop"))
    @DOFNearStop.setter
    def DOFNearStop(self, val): self.DOFNearStop.set(val)
    @property
    def DecenteringPositionX(self):  # type: ()->Float
        return Float(self._node.at("DecenteringPositionX"))
    @DecenteringPositionX.setter
    def DecenteringPositionX(self, val): self.DecenteringPositionX.set(val)
    @property
    def DecenteringPositionY(self):  # type: ()->Float
        return Float(self._node.at("DecenteringPositionY"))
    @DecenteringPositionY.setter
    def DecenteringPositionY(self, val): self.DecenteringPositionY.set(val)
    @property
    def DecenteringPositionZ(self):  # type: ()->Float
        return Float(self._node.at("DecenteringPositionZ"))
    @DecenteringPositionZ.setter
    def DecenteringPositionZ(self, val): self.DecenteringPositionZ.set(val)
    @property
    def DistanceModifierRamp(self):  # type: ()->Float
        return Float(self._node.at("DistanceModifierRamp"))
    @DistanceModifierRamp.setter
    def DistanceModifierRamp(self, val): self.DistanceModifierRamp.set(val)
    @property
    def DodgeLatenessSmooth(self):  # type: ()->Float
        return Float(self._node.at("DodgeLatenessSmooth"))
    @DodgeLatenessSmooth.setter
    def DodgeLatenessSmooth(self, val): self.DodgeLatenessSmooth.set(val)
    @property
    def DodgeLatenessSmoothThreshold(self):  # type: ()->Float
        return Float(self._node.at("DodgeLatenessSmoothThreshold"))
    @DodgeLatenessSmoothThreshold.setter
    def DodgeLatenessSmoothThreshold(self, val): self.DodgeLatenessSmoothThreshold.set(val)
    @property
    def FOV(self):  # type: ()->Float
        return Float(self._node.at("FOV"))
    @FOV.setter
    def FOV(self, val): self.FOV.set(val)
    @property
    def FOVRamp(self):  # type: ()->Float
        return Float(self._node.at("FOVRamp"))
    @FOVRamp.setter
    def FOVRamp(self, val): self.FOVRamp.set(val)
    @property
    def FightDistanceOffset(self):  # type: ()->Float
        return Float(self._node.at("FightDistanceOffset"))
    @FightDistanceOffset.setter
    def FightDistanceOffset(self, val): self.FightDistanceOffset.set(val)
    @property
    def FightDistanceOffsetSpeed(self):  # type: ()->Float
        return Float(self._node.at("FightDistanceOffsetSpeed"))
    @FightDistanceOffsetSpeed.setter
    def FightDistanceOffsetSpeed(self, val): self.FightDistanceOffsetSpeed.set(val)
    @property
    def FightRotationDuration(self):  # type: ()->Float
        return Float(self._node.at("FightRotationDuration"))
    @FightRotationDuration.setter
    def FightRotationDuration(self, val): self.FightRotationDuration.set(val)
    @property
    def FightRotationInDuration(self):  # type: ()->Float
        return Float(self._node.at("FightRotationInDuration"))
    @FightRotationInDuration.setter
    def FightRotationInDuration(self, val): self.FightRotationInDuration.set(val)
    @property
    def FightRotationOutDuration(self):  # type: ()->Float
        return Float(self._node.at("FightRotationOutDuration"))
    @FightRotationOutDuration.setter
    def FightRotationOutDuration(self, val): self.FightRotationOutDuration.set(val)
    @property
    def FightRotationSpeed(self):  # type: ()->Float
        return Float(self._node.at("FightRotationSpeed"))
    @FightRotationSpeed.setter
    def FightRotationSpeed(self, val): self.FightRotationSpeed.set(val)
    @property
    def FightSpeedRationImpactCoeff(self):  # type: ()->Float
        return Float(self._node.at("FightSpeedRationImpactCoeff"))
    @FightSpeedRationImpactCoeff.setter
    def FightSpeedRationImpactCoeff(self, val): self.FightSpeedRationImpactCoeff.set(val)
    @property
    def InterestPointPosition(self):  # type: ()->Position
        return Position(self._node.at("InterestPointPosition"))
    @property
    def InterestPointSight(self):  # type: ()->Vector3
        return Vector3(self._node.at("InterestPointSight"))
    @InterestPointSight.setter
    def InterestPointSight(self, val): self.InterestPointSight.set(val)
    @property
    def InterestPointSightAngleSpeed(self):  # type: ()->Float
        return Float(self._node.at("InterestPointSightAngleSpeed"))
    @InterestPointSightAngleSpeed.setter
    def InterestPointSightAngleSpeed(self, val): self.InterestPointSightAngleSpeed.set(val)
    @property
    def JoyAccelerationBoostChangingSideH(self):  # type: ()->Float
        return Float(self._node.at("JoyAccelerationBoostChangingSideH"))
    @JoyAccelerationBoostChangingSideH.setter
    def JoyAccelerationBoostChangingSideH(self, val): self.JoyAccelerationBoostChangingSideH.set(val)
    @property
    def JoyAccelerationBoostChangingSideV(self):  # type: ()->Float
        return Float(self._node.at("JoyAccelerationBoostChangingSideV"))
    @JoyAccelerationBoostChangingSideV.setter
    def JoyAccelerationBoostChangingSideV(self, val): self.JoyAccelerationBoostChangingSideV.set(val)
    @property
    def JoyAccelerationH(self):  # type: ()->Float
        return Float(self._node.at("JoyAccelerationH"))
    @JoyAccelerationH.setter
    def JoyAccelerationH(self, val): self.JoyAccelerationH.set(val)
    @property
    def JoyAccelerationV(self):  # type: ()->Float
        return Float(self._node.at("JoyAccelerationV"))
    @JoyAccelerationV.setter
    def JoyAccelerationV(self, val): self.JoyAccelerationV.set(val)
    @property
    def JoyDecelerationH(self):  # type: ()->Float
        return Float(self._node.at("JoyDecelerationH"))
    @JoyDecelerationH.setter
    def JoyDecelerationH(self, val): self.JoyDecelerationH.set(val)
    @property
    def JoyDecelerationV(self):  # type: ()->Float
        return Float(self._node.at("JoyDecelerationV"))
    @JoyDecelerationV.setter
    def JoyDecelerationV(self, val): self.JoyDecelerationV.set(val)
    @property
    def JoyRotationScaleConverterH(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("JoyRotationScaleConverterH"))
    @property
    def JoyRotationScaleConverterV(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("JoyRotationScaleConverterV"))
    @property
    def JoySpeedFactor(self):  # type: ()->Float
        return Float(self._node.at("JoySpeedFactor"))
    @JoySpeedFactor.setter
    def JoySpeedFactor(self, val): self.JoySpeedFactor.set(val)
    @property
    def JoySpeedMaxH(self):  # type: ()->Float
        return Float(self._node.at("JoySpeedMaxH"))
    @JoySpeedMaxH.setter
    def JoySpeedMaxH(self, val): self.JoySpeedMaxH.set(val)
    @property
    def JoySpeedMaxV(self):  # type: ()->Float
        return Float(self._node.at("JoySpeedMaxV"))
    @JoySpeedMaxV.setter
    def JoySpeedMaxV(self, val): self.JoySpeedMaxV.set(val)
    @property
    def JumpEnable(self):  # type: ()->Bool
        return Bool(self._node.at("JumpEnable"))
    @JumpEnable.setter
    def JumpEnable(self, val): self.JumpEnable.set(val)
    @property
    def LockDecenteringDuration(self):  # type: ()->Float
        return Float(self._node.at("LockDecenteringDuration"))
    @LockDecenteringDuration.setter
    def LockDecenteringDuration(self, val): self.LockDecenteringDuration.set(val)
    @property
    def LockDistSpeed(self):  # type: ()->Float
        return Float(self._node.at("LockDistSpeed"))
    @LockDistSpeed.setter
    def LockDistSpeed(self, val): self.LockDistSpeed.set(val)
    @property
    def LockEndTransitionThreshold(self):  # type: ()->Float
        return Float(self._node.at("LockEndTransitionThreshold"))
    @LockEndTransitionThreshold.setter
    def LockEndTransitionThreshold(self, val): self.LockEndTransitionThreshold.set(val)
    @property
    def LockLowSpeedDist(self):  # type: ()->Float
        return Float(self._node.at("LockLowSpeedDist"))
    @LockLowSpeedDist.setter
    def LockLowSpeedDist(self, val): self.LockLowSpeedDist.set(val)
    @property
    def LockMaxDecentering(self):  # type: ()->Float
        return Float(self._node.at("LockMaxDecentering"))
    @LockMaxDecentering.setter
    def LockMaxDecentering(self, val): self.LockMaxDecentering.set(val)
    @property
    def LockMaxDist(self):  # type: ()->Float
        return Float(self._node.at("LockMaxDist"))
    @LockMaxDist.setter
    def LockMaxDist(self, val): self.LockMaxDist.set(val)
    @property
    def LockMinCameraDist(self):  # type: ()->Float
        return Float(self._node.at("LockMinCameraDist"))
    @LockMinCameraDist.setter
    def LockMinCameraDist(self, val): self.LockMinCameraDist.set(val)
    @property
    def LockOffsetTransitionSmooth(self):  # type: ()->Float
        return Float(self._node.at("LockOffsetTransitionSmooth"))
    @LockOffsetTransitionSmooth.setter
    def LockOffsetTransitionSmooth(self, val): self.LockOffsetTransitionSmooth.set(val)
    @property
    def LockPitchSpeed(self):  # type: ()->Float
        return Float(self._node.at("LockPitchSpeed"))
    @LockPitchSpeed.setter
    def LockPitchSpeed(self, val): self.LockPitchSpeed.set(val)
    @property
    def LockPitchSpeedClose(self):  # type: ()->Float
        return Float(self._node.at("LockPitchSpeedClose"))
    @LockPitchSpeedClose.setter
    def LockPitchSpeedClose(self, val): self.LockPitchSpeedClose.set(val)
    @property
    def LockSizeRatioThreshold(self):  # type: ()->Float
        return Float(self._node.at("LockSizeRatioThreshold"))
    @LockSizeRatioThreshold.setter
    def LockSizeRatioThreshold(self, val): self.LockSizeRatioThreshold.set(val)
    @property
    def LockTransitionSmooth(self):  # type: ()->Float
        return Float(self._node.at("LockTransitionSmooth"))
    @LockTransitionSmooth.setter
    def LockTransitionSmooth(self, val): self.LockTransitionSmooth.set(val)
    @property
    def LockTriggerDist(self):  # type: ()->Float
        return Float(self._node.at("LockTriggerDist"))
    @LockTriggerDist.setter
    def LockTriggerDist(self, val): self.LockTriggerDist.set(val)
    @property
    def LockYawSpeed(self):  # type: ()->Float
        return Float(self._node.at("LockYawSpeed"))
    @LockYawSpeed.setter
    def LockYawSpeed(self, val): self.LockYawSpeed.set(val)
    @property
    def LockYawSpeedClose(self):  # type: ()->Float
        return Float(self._node.at("LockYawSpeedClose"))
    @LockYawSpeedClose.setter
    def LockYawSpeedClose(self, val): self.LockYawSpeedClose.set(val)
    @property
    def LookAtOffsetPitch(self):  # type: ()->Float
        return Float(self._node.at("LookAtOffsetPitch"))
    @LookAtOffsetPitch.setter
    def LookAtOffsetPitch(self, val): self.LookAtOffsetPitch.set(val)
    @property
    def LookAtOffsetYaw(self):  # type: ()->Float
        return Float(self._node.at("LookAtOffsetYaw"))
    @LookAtOffsetYaw.setter
    def LookAtOffsetYaw(self, val): self.LookAtOffsetYaw.set(val)
    @property
    def NearPlane(self):  # type: ()->Float
        return Float(self._node.at("NearPlane"))
    @NearPlane.setter
    def NearPlane(self, val): self.NearPlane.set(val)
    @property
    def PitchConstraintAnticipation(self):  # type: ()->Float
        return Float(self._node.at("PitchConstraintAnticipation"))
    @PitchConstraintAnticipation.setter
    def PitchConstraintAnticipation(self, val): self.PitchConstraintAnticipation.set(val)
    @property
    def PitchConstraintMax(self):  # type: ()->Float
        return Float(self._node.at("PitchConstraintMax"))
    @PitchConstraintMax.setter
    def PitchConstraintMax(self, val): self.PitchConstraintMax.set(val)
    @property
    def PitchConstraintMin(self):  # type: ()->Float
        return Float(self._node.at("PitchConstraintMin"))
    @PitchConstraintMin.setter
    def PitchConstraintMin(self, val): self.PitchConstraintMin.set(val)
    @property
    def PitchToFOV(self):  # type: ()->Float
        return Float(self._node.at("PitchToFOV"))
    @PitchToFOV.setter
    def PitchToFOV(self, val): self.PitchToFOV.set(val)
    @property
    def RotationOffsetPitch(self):  # type: ()->Float
        return Float(self._node.at("RotationOffsetPitch"))
    @RotationOffsetPitch.setter
    def RotationOffsetPitch(self, val): self.RotationOffsetPitch.set(val)
    @property
    def RotationOffsetYaw(self):  # type: ()->Float
        return Float(self._node.at("RotationOffsetYaw"))
    @RotationOffsetYaw.setter
    def RotationOffsetYaw(self, val): self.RotationOffsetYaw.set(val)
    @property
    def SpacePitchOffset(self):  # type: ()->Float
        return Float(self._node.at("SpacePitchOffset"))
    @SpacePitchOffset.setter
    def SpacePitchOffset(self, val): self.SpacePitchOffset.set(val)
    @property
    def SpeedToDistanceModifier(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("SpeedToDistanceModifier"))
    @property
    def SpeedToFOV(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("SpeedToFOV"))
    @property
    def TargetBrutalStopSmoothThreshold(self):  # type: ()->Float
        return Float(self._node.at("TargetBrutalStopSmoothThreshold"))
    @TargetBrutalStopSmoothThreshold.setter
    def TargetBrutalStopSmoothThreshold(self, val): self.TargetBrutalStopSmoothThreshold.set(val)
    @property
    def TargetDeadZoneRadius(self):  # type: ()->Float
        return Float(self._node.at("TargetDeadZoneRadius"))
    @TargetDeadZoneRadius.setter
    def TargetDeadZoneRadius(self, val): self.TargetDeadZoneRadius.set(val)
    @property
    def TargetDistance(self):  # type: ()->Float
        return Float(self._node.at("TargetDistance"))
    @TargetDistance.setter
    def TargetDistance(self, val): self.TargetDistance.set(val)
    @property
    def TargetJumpDistOffset(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("TargetJumpDistOffset"))
    @property
    def TargetJumpDistOffsetSmooth(self):  # type: ()->Float
        return Float(self._node.at("TargetJumpDistOffsetSmooth"))
    @TargetJumpDistOffsetSmooth.setter
    def TargetJumpDistOffsetSmooth(self, val): self.TargetJumpDistOffsetSmooth.set(val)
    @property
    def TargetJumpSmooth(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("TargetJumpSmooth"))
    @property
    def TargetMaxSpeed(self):  # type: ()->Float
        return Float(self._node.at("TargetMaxSpeed"))
    @TargetMaxSpeed.setter
    def TargetMaxSpeed(self, val): self.TargetMaxSpeed.set(val)
    @property
    def TargetMinSmooth(self):  # type: ()->Float
        return Float(self._node.at("TargetMinSmooth"))
    @TargetMinSmooth.setter
    def TargetMinSmooth(self, val): self.TargetMinSmooth.set(val)
    @property
    def TargetOffsetX(self):  # type: ()->Float
        return Float(self._node.at("TargetOffsetX"))
    @TargetOffsetX.setter
    def TargetOffsetX(self, val): self.TargetOffsetX.set(val)
    @property
    def TargetOffsetY(self):  # type: ()->Float
        return Float(self._node.at("TargetOffsetY"))
    @TargetOffsetY.setter
    def TargetOffsetY(self, val): self.TargetOffsetY.set(val)
    @property
    def TargetOffsetZ(self):  # type: ()->Float
        return Float(self._node.at("TargetOffsetZ"))
    @TargetOffsetZ.setter
    def TargetOffsetZ(self, val): self.TargetOffsetZ.set(val)
    @property
    def TargetSmoothMultiplier(self):  # type: ()->Float
        return Float(self._node.at("TargetSmoothMultiplier"))
    @TargetSmoothMultiplier.setter
    def TargetSmoothMultiplier(self, val): self.TargetSmoothMultiplier.set(val)
    @property
    def TargetSmoothMultiplierZ(self):  # type: ()->Float
        return Float(self._node.at("TargetSmoothMultiplierZ"))
    @TargetSmoothMultiplierZ.setter
    def TargetSmoothMultiplierZ(self, val): self.TargetSmoothMultiplierZ.set(val)
    @property
    def TargetXOffsetFromYawForce(self):  # type: ()->Float
        return Float(self._node.at("TargetXOffsetFromYawForce"))
    @TargetXOffsetFromYawForce.setter
    def TargetXOffsetFromYawForce(self, val): self.TargetXOffsetFromYawForce.set(val)
    @property
    def TargetXOffsetFromYawSmooth(self):  # type: ()->Float
        return Float(self._node.at("TargetXOffsetFromYawSmooth"))
    @TargetXOffsetFromYawSmooth.setter
    def TargetXOffsetFromYawSmooth(self, val): self.TargetXOffsetFromYawSmooth.set(val)
    @property
    def TargetZOffsetFromPitchForce(self):  # type: ()->Float
        return Float(self._node.at("TargetZOffsetFromPitchForce"))
    @TargetZOffsetFromPitchForce.setter
    def TargetZOffsetFromPitchForce(self, val): self.TargetZOffsetFromPitchForce.set(val)
    @property
    def TargetZOffsetFromPitchSmooth(self):  # type: ()->Float
        return Float(self._node.at("TargetZOffsetFromPitchSmooth"))
    @TargetZOffsetFromPitchSmooth.setter
    def TargetZOffsetFromPitchSmooth(self, val): self.TargetZOffsetFromPitchSmooth.set(val)
    @property
    def UseSpeedToFOV(self):  # type: ()->Bool
        return Bool(self._node.at("UseSpeedToFOV"))
    @UseSpeedToFOV.setter
    def UseSpeedToFOV(self, val): self.UseSpeedToFOV.set(val)
    @property
    def WorldZOffset(self):  # type: ()->Float
        return Float(self._node.at("WorldZOffset"))
    @WorldZOffset.setter
    def WorldZOffset(self, val): self.WorldZOffset.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def defaultParamsRequired(self):  # type: ()->Bool
        return Bool(self._node.at("defaultParamsRequired"))
    @defaultParamsRequired.setter
    def defaultParamsRequired(self, val): self.defaultParamsRequired.set(val)
    pass




