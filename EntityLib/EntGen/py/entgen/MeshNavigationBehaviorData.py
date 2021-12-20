
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.MeshNavigationAllowedMode import *
from entgen.String import *
from entgen.Bool import *
from entgen.Float import *

from EntityLibPy import Node

class MeshNavigationBehaviorData(HelperObject):
    schema_name = "MeshNavigationBehaviorData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MeshNavigationBehaviorData
        return MeshNavigationBehaviorData(entlib.load_node_file(sourcefile, entlib.get_schema(MeshNavigationBehaviorData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MeshNavigationBehaviorData
        return MeshNavigationBehaviorData(entlib.make_node(MeshNavigationBehaviorData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DeltaAngleMinToPrepareToHoldingOnToNavigationMesh(self):  # type: ()->Float
        return Float(self._node.at("DeltaAngleMinToPrepareToHoldingOnToNavigationMesh"))
    @DeltaAngleMinToPrepareToHoldingOnToNavigationMesh.setter
    def DeltaAngleMinToPrepareToHoldingOnToNavigationMesh(self, val): self.DeltaAngleMinToPrepareToHoldingOnToNavigationMesh.set(val)
    @property
    def EdgeTransitionConstraintAllowed(self):  # type: ()->Bool
        return Bool(self._node.at("EdgeTransitionConstraintAllowed"))
    @EdgeTransitionConstraintAllowed.setter
    def EdgeTransitionConstraintAllowed(self, val): self.EdgeTransitionConstraintAllowed.set(val)
    @property
    def EdgeTransitionConstraintLedgeAngle(self):  # type: ()->Float
        return Float(self._node.at("EdgeTransitionConstraintLedgeAngle"))
    @EdgeTransitionConstraintLedgeAngle.setter
    def EdgeTransitionConstraintLedgeAngle(self, val): self.EdgeTransitionConstraintLedgeAngle.set(val)
    @property
    def EdgeTransitionConstraintWallAngle(self):  # type: ()->Float
        return Float(self._node.at("EdgeTransitionConstraintWallAngle"))
    @EdgeTransitionConstraintWallAngle.setter
    def EdgeTransitionConstraintWallAngle(self, val): self.EdgeTransitionConstraintWallAngle.set(val)
    @property
    def MaxNormalAngle(self):  # type: ()->Float
        return Float(self._node.at("MaxNormalAngle"))
    @MaxNormalAngle.setter
    def MaxNormalAngle(self, val): self.MaxNormalAngle.set(val)
    @property
    def MeshNavigationAllowedMode(self):  # type: ()->MeshNavigationAllowedMode
        return MeshNavigationAllowedMode(self._node.at("MeshNavigationAllowedMode"))
    @MeshNavigationAllowedMode.setter
    def MeshNavigationAllowedMode(self, val): self.MeshNavigationAllowedMode.set(val)
    @property
    def OrientationRateToPrepareToHoldingOnToNavigationMesh(self):  # type: ()->Float
        return Float(self._node.at("OrientationRateToPrepareToHoldingOnToNavigationMesh"))
    @OrientationRateToPrepareToHoldingOnToNavigationMesh.setter
    def OrientationRateToPrepareToHoldingOnToNavigationMesh(self, val): self.OrientationRateToPrepareToHoldingOnToNavigationMesh.set(val)
    @property
    def RayCastLengthLegFactor(self):  # type: ()->Float
        return Float(self._node.at("RayCastLengthLegFactor"))
    @RayCastLengthLegFactor.setter
    def RayCastLengthLegFactor(self, val): self.RayCastLengthLegFactor.set(val)
    @property
    def RayCastLengthSpeedFactor(self):  # type: ()->Float
        return Float(self._node.at("RayCastLengthSpeedFactor"))
    @RayCastLengthSpeedFactor.setter
    def RayCastLengthSpeedFactor(self, val): self.RayCastLengthSpeedFactor.set(val)
    @property
    def RollAllowed(self):  # type: ()->Bool
        return Bool(self._node.at("RollAllowed"))
    @RollAllowed.setter
    def RollAllowed(self, val): self.RollAllowed.set(val)
    @property
    def SlopeAngleMinToAllowStickedLand(self):  # type: ()->Float
        return Float(self._node.at("SlopeAngleMinToAllowStickedLand"))
    @SlopeAngleMinToAllowStickedLand.setter
    def SlopeAngleMinToAllowStickedLand(self, val): self.SlopeAngleMinToAllowStickedLand.set(val)
    @property
    def StickToAnyNormalAllowed(self):  # type: ()->Bool
        return Bool(self._node.at("StickToAnyNormalAllowed"))
    @StickToAnyNormalAllowed.setter
    def StickToAnyNormalAllowed(self, val): self.StickToAnyNormalAllowed.set(val)
    @property
    def VerticalAngleMinToUseLandingTreeAnimation(self):  # type: ()->Float
        return Float(self._node.at("VerticalAngleMinToUseLandingTreeAnimation"))
    @VerticalAngleMinToUseLandingTreeAnimation.setter
    def VerticalAngleMinToUseLandingTreeAnimation(self, val): self.VerticalAngleMinToUseLandingTreeAnimation.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




