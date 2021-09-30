
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.Collider import *
from entgen.ConditionalRigidityAttribute import *
from entgen.StickToGround import *


class AnimationTailConstraintsGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimationTailConstraintsGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(AnimationTailConstraintsGD.schema_name))
    @property
    def AngularSpeedMaxForSpeedModeFurious(self): return Float(self._node.at("AngularSpeedMaxForSpeedModeFurious"))
    @AngularSpeedMaxForSpeedModeFurious.setter
    def AngularSpeedMaxForSpeedModeFurious(self, val): self.AngularSpeedMaxForSpeedModeFurious.set(val)
    @property
    def AngularSpeedMaxForSpeedModeNone(self): return Float(self._node.at("AngularSpeedMaxForSpeedModeNone"))
    @AngularSpeedMaxForSpeedModeNone.setter
    def AngularSpeedMaxForSpeedModeNone(self, val): self.AngularSpeedMaxForSpeedModeNone.set(val)
    @property
    def BoneInjectDirectionFromUseAmplitudeFactor(self): return Bool(self._node.at("BoneInjectDirectionFromUseAmplitudeFactor"))
    @BoneInjectDirectionFromUseAmplitudeFactor.setter
    def BoneInjectDirectionFromUseAmplitudeFactor(self, val): self.BoneInjectDirectionFromUseAmplitudeFactor.set(val)
    @property
    def BoneNameEnd(self): return String(self._node.at("BoneNameEnd"))
    @BoneNameEnd.setter
    def BoneNameEnd(self, val): self.BoneNameEnd.set(val)
    @property
    def BoneNameInjectDirectionFrom(self): return String(self._node.at("BoneNameInjectDirectionFrom"))
    @BoneNameInjectDirectionFrom.setter
    def BoneNameInjectDirectionFrom(self, val): self.BoneNameInjectDirectionFrom.set(val)
    @property
    def BoneNameStart(self): return String(self._node.at("BoneNameStart"))
    @BoneNameStart.setter
    def BoneNameStart(self, val): self.BoneNameStart.set(val)
    @property
    def Colliders(self): return (lambda n: Array(Collider, n))(self._node.at("Colliders"))
    @property
    def CollidersRadiusFactorGrounded(self): return Float(self._node.at("CollidersRadiusFactorGrounded"))
    @CollidersRadiusFactorGrounded.setter
    def CollidersRadiusFactorGrounded(self, val): self.CollidersRadiusFactorGrounded.set(val)
    @property
    def CompensateSegmentStretchFactor(self): return Float(self._node.at("CompensateSegmentStretchFactor"))
    @CompensateSegmentStretchFactor.setter
    def CompensateSegmentStretchFactor(self, val): self.CompensateSegmentStretchFactor.set(val)
    @property
    def ConditionalRigidityAttributes(self): return (lambda n: Array(ConditionalRigidityAttribute, n))(self._node.at("ConditionalRigidityAttributes"))
    @property
    def StickToGrounds(self): return (lambda n: Array(StickToGround, n))(self._node.at("StickToGrounds"))
    @property
    def StickToGroundsGravity(self): return Float(self._node.at("StickToGroundsGravity"))
    @StickToGroundsGravity.setter
    def StickToGroundsGravity(self, val): self.StickToGroundsGravity.set(val)
    @property
    def StickToGroundsGravityUnderwater(self): return Float(self._node.at("StickToGroundsGravityUnderwater"))
    @StickToGroundsGravityUnderwater.setter
    def StickToGroundsGravityUnderwater(self, val): self.StickToGroundsGravityUnderwater.set(val)
    @property
    def StickToGroundsRadiusFactorDead(self): return Float(self._node.at("StickToGroundsRadiusFactorDead"))
    @StickToGroundsRadiusFactorDead.setter
    def StickToGroundsRadiusFactorDead(self, val): self.StickToGroundsRadiusFactorDead.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




