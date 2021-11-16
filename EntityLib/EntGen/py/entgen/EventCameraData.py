
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.Vector3 import *

from EntityLibPy import Node

class EventCameraData(HelperObject):
    schema_name = "EventCameraData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EventCameraData
        return EventCameraData(entlib.load_node_file(sourcefile, entlib.get_schema(EventCameraData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EventCameraData
        return EventCameraData(entlib.make_node(EventCameraData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BlendCameraTime(self):  # type: ()->Float
        return Float(self._node.at("BlendCameraTime"))
    @BlendCameraTime.setter
    def BlendCameraTime(self, val): self.BlendCameraTime.set(val)
    @property
    def CameraAimTriggerActor(self):  # type: ()->Bool
        return Bool(self._node.at("CameraAimTriggerActor"))
    @CameraAimTriggerActor.setter
    def CameraAimTriggerActor(self, val): self.CameraAimTriggerActor.set(val)
    @property
    def CameraOffsets(self):  # type: ()->Array[Vector3]
        return (lambda n: Array(Vector3, n))(self._node.at("CameraOffsets"))
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
    def DOFRelativeTarget(self):  # type: ()->Bool
        return Bool(self._node.at("DOFRelativeTarget"))
    @DOFRelativeTarget.setter
    def DOFRelativeTarget(self, val): self.DOFRelativeTarget.set(val)
    @property
    def EventCameraTime(self):  # type: ()->Float
        return Float(self._node.at("EventCameraTime"))
    @EventCameraTime.setter
    def EventCameraTime(self, val): self.EventCameraTime.set(val)
    @property
    def FOV(self):  # type: ()->Float
        return Float(self._node.at("FOV"))
    @FOV.setter
    def FOV(self, val): self.FOV.set(val)
    @property
    def FixedCam(self):  # type: ()->Bool
        return Bool(self._node.at("FixedCam"))
    @FixedCam.setter
    def FixedCam(self, val): self.FixedCam.set(val)
    @property
    def FollowCam(self):  # type: ()->Bool
        return Bool(self._node.at("FollowCam"))
    @FollowCam.setter
    def FollowCam(self, val): self.FollowCam.set(val)
    @property
    def FollowTarget(self):  # type: ()->Bool
        return Bool(self._node.at("FollowTarget"))
    @FollowTarget.setter
    def FollowTarget(self, val): self.FollowTarget.set(val)
    @property
    def OffsetsBlendTime(self):  # type: ()->Float
        return Float(self._node.at("OffsetsBlendTime"))
    @OffsetsBlendTime.setter
    def OffsetsBlendTime(self, val): self.OffsetsBlendTime.set(val)
    @property
    def PositionsAngularBlend(self):  # type: ()->Bool
        return Bool(self._node.at("PositionsAngularBlend"))
    @PositionsAngularBlend.setter
    def PositionsAngularBlend(self, val): self.PositionsAngularBlend.set(val)
    @property
    def PositionsBlendTime(self):  # type: ()->Float
        return Float(self._node.at("PositionsBlendTime"))
    @PositionsBlendTime.setter
    def PositionsBlendTime(self, val): self.PositionsBlendTime.set(val)
    @property
    def TargetOffsets(self):  # type: ()->Array[Vector3]
        return (lambda n: Array(Vector3, n))(self._node.at("TargetOffsets"))
    @property
    def UseDOF(self):  # type: ()->Bool
        return Bool(self._node.at("UseDOF"))
    @UseDOF.setter
    def UseDOF(self, val): self.UseDOF.set(val)
    @property
    def UseOffsetsSpline(self):  # type: ()->Bool
        return Bool(self._node.at("UseOffsetsSpline"))
    @UseOffsetsSpline.setter
    def UseOffsetsSpline(self, val): self.UseOffsetsSpline.set(val)
    @property
    def UsePositionsSpline(self):  # type: ()->Bool
        return Bool(self._node.at("UsePositionsSpline"))
    @UsePositionsSpline.setter
    def UsePositionsSpline(self, val): self.UsePositionsSpline.set(val)
    @property
    def UseTriggerActorPosition(self):  # type: ()->Bool
        return Bool(self._node.at("UseTriggerActorPosition"))
    @UseTriggerActorPosition.setter
    def UseTriggerActorPosition(self, val): self.UseTriggerActorPosition.set(val)
    @property
    def UseTriggerActorSight(self):  # type: ()->Bool
        return Bool(self._node.at("UseTriggerActorSight"))
    @UseTriggerActorSight.setter
    def UseTriggerActorSight(self, val): self.UseTriggerActorSight.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




