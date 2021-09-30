
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.MeshNavigationAllowedMode import *
from entgen.String import *
from entgen.Bool import *
from entgen.Float import *


class MeshNavigationBehaviorData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/MeshNavigationBehaviorData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(MeshNavigationBehaviorData.schema_name))
    @property
    def EdgeTransitionConstraintAllowed(self): return Bool(self._node.at("EdgeTransitionConstraintAllowed"))
    @EdgeTransitionConstraintAllowed.setter
    def EdgeTransitionConstraintAllowed(self, val): self.EdgeTransitionConstraintAllowed.set(val)
    @property
    def EdgeTransitionConstraintLedgeAngle(self): return Float(self._node.at("EdgeTransitionConstraintLedgeAngle"))
    @EdgeTransitionConstraintLedgeAngle.setter
    def EdgeTransitionConstraintLedgeAngle(self, val): self.EdgeTransitionConstraintLedgeAngle.set(val)
    @property
    def EdgeTransitionConstraintWallAngle(self): return Float(self._node.at("EdgeTransitionConstraintWallAngle"))
    @EdgeTransitionConstraintWallAngle.setter
    def EdgeTransitionConstraintWallAngle(self, val): self.EdgeTransitionConstraintWallAngle.set(val)
    @property
    def MaxNormalAngle(self): return Float(self._node.at("MaxNormalAngle"))
    @MaxNormalAngle.setter
    def MaxNormalAngle(self, val): self.MaxNormalAngle.set(val)
    @property
    def MeshNavigationAllowedMode(self): return MeshNavigationAllowedMode(self._node.at("MeshNavigationAllowedMode"))
    @MeshNavigationAllowedMode.setter
    def MeshNavigationAllowedMode(self, val): self.MeshNavigationAllowedMode.set(val)
    @property
    def RayCastLengthLegFactor(self): return Float(self._node.at("RayCastLengthLegFactor"))
    @RayCastLengthLegFactor.setter
    def RayCastLengthLegFactor(self, val): self.RayCastLengthLegFactor.set(val)
    @property
    def RayCastLengthSpeedFactor(self): return Float(self._node.at("RayCastLengthSpeedFactor"))
    @RayCastLengthSpeedFactor.setter
    def RayCastLengthSpeedFactor(self, val): self.RayCastLengthSpeedFactor.set(val)
    @property
    def RollAllowed(self): return Bool(self._node.at("RollAllowed"))
    @RollAllowed.setter
    def RollAllowed(self, val): self.RollAllowed.set(val)
    @property
    def StickToAnyNormalAllowed(self): return Bool(self._node.at("StickToAnyNormalAllowed"))
    @StickToAnyNormalAllowed.setter
    def StickToAnyNormalAllowed(self, val): self.StickToAnyNormalAllowed.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




