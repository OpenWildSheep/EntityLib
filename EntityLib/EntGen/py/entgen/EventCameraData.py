
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.Vector3 import *


class EventCameraData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EventCameraData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(EventCameraData.schema_name))
    @property
    def BlendCameraTime(self): return Float(self._node.at("BlendCameraTime"))
    @BlendCameraTime.setter
    def BlendCameraTime(self, val): self.BlendCameraTime.set(val)
    @property
    def CameraAimTriggerActor(self): return Bool(self._node.at("CameraAimTriggerActor"))
    @CameraAimTriggerActor.setter
    def CameraAimTriggerActor(self, val): self.CameraAimTriggerActor.set(val)
    @property
    def CameraOffsets(self): return (lambda n: Array(Vector3, n))(self._node.at("CameraOffsets"))
    @property
    def DOFFarStart(self): return Float(self._node.at("DOFFarStart"))
    @DOFFarStart.setter
    def DOFFarStart(self, val): self.DOFFarStart.set(val)
    @property
    def DOFFarStop(self): return Float(self._node.at("DOFFarStop"))
    @DOFFarStop.setter
    def DOFFarStop(self, val): self.DOFFarStop.set(val)
    @property
    def DOFMultiplier(self): return Float(self._node.at("DOFMultiplier"))
    @DOFMultiplier.setter
    def DOFMultiplier(self, val): self.DOFMultiplier.set(val)
    @property
    def DOFNearStart(self): return Float(self._node.at("DOFNearStart"))
    @DOFNearStart.setter
    def DOFNearStart(self, val): self.DOFNearStart.set(val)
    @property
    def DOFNearStop(self): return Float(self._node.at("DOFNearStop"))
    @DOFNearStop.setter
    def DOFNearStop(self, val): self.DOFNearStop.set(val)
    @property
    def DOFRelativeTarget(self): return Bool(self._node.at("DOFRelativeTarget"))
    @DOFRelativeTarget.setter
    def DOFRelativeTarget(self, val): self.DOFRelativeTarget.set(val)
    @property
    def EventCameraTime(self): return Float(self._node.at("EventCameraTime"))
    @EventCameraTime.setter
    def EventCameraTime(self, val): self.EventCameraTime.set(val)
    @property
    def FOV(self): return Float(self._node.at("FOV"))
    @FOV.setter
    def FOV(self, val): self.FOV.set(val)
    @property
    def FixedCam(self): return Bool(self._node.at("FixedCam"))
    @FixedCam.setter
    def FixedCam(self, val): self.FixedCam.set(val)
    @property
    def FollowCam(self): return Bool(self._node.at("FollowCam"))
    @FollowCam.setter
    def FollowCam(self, val): self.FollowCam.set(val)
    @property
    def FollowTarget(self): return Bool(self._node.at("FollowTarget"))
    @FollowTarget.setter
    def FollowTarget(self, val): self.FollowTarget.set(val)
    @property
    def OffsetsBlendTime(self): return Float(self._node.at("OffsetsBlendTime"))
    @OffsetsBlendTime.setter
    def OffsetsBlendTime(self, val): self.OffsetsBlendTime.set(val)
    @property
    def PositionsAngularBlend(self): return Bool(self._node.at("PositionsAngularBlend"))
    @PositionsAngularBlend.setter
    def PositionsAngularBlend(self, val): self.PositionsAngularBlend.set(val)
    @property
    def PositionsBlendTime(self): return Float(self._node.at("PositionsBlendTime"))
    @PositionsBlendTime.setter
    def PositionsBlendTime(self, val): self.PositionsBlendTime.set(val)
    @property
    def TargetOffsets(self): return (lambda n: Array(Vector3, n))(self._node.at("TargetOffsets"))
    @property
    def UseDOF(self): return Bool(self._node.at("UseDOF"))
    @UseDOF.setter
    def UseDOF(self, val): self.UseDOF.set(val)
    @property
    def UseOffsetsSpline(self): return Bool(self._node.at("UseOffsetsSpline"))
    @UseOffsetsSpline.setter
    def UseOffsetsSpline(self, val): self.UseOffsetsSpline.set(val)
    @property
    def UsePositionsSpline(self): return Bool(self._node.at("UsePositionsSpline"))
    @UsePositionsSpline.setter
    def UsePositionsSpline(self, val): self.UsePositionsSpline.set(val)
    @property
    def UseTriggerActorPosition(self): return Bool(self._node.at("UseTriggerActorPosition"))
    @UseTriggerActorPosition.setter
    def UseTriggerActorPosition(self, val): self.UseTriggerActorPosition.set(val)
    @property
    def UseTriggerActorSight(self): return Bool(self._node.at("UseTriggerActorSight"))
    @UseTriggerActorSight.setter
    def UseTriggerActorSight(self, val): self.UseTriggerActorSight.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




