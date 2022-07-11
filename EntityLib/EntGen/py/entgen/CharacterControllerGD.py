
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.CharacterControllerClamberData import *
from entgen.CharacterControllerFallData import *
from entgen.CharacterControllerGroundNormalData import *
from entgen.CharacterControllerSlideData import *
from entgen.ClimbEdgeData import *
from entgen.ComponentGD import *
from entgen.HeadCollisionBehaviorData import *
from entgen.HitWallData import *
from entgen.ImmersedBehaviorData import *
from entgen.InputCollisionBehaviorData import *
from entgen.MeshNavigationBehaviorData import *
from entgen.MoveCapacityData import *
from entgen.PredictionBehaviorData import *
from entgen.Vector3 import *

from EntityLibPy import Node

class CharacterControllerGD(HelperObject):
    schema_name = "CharacterControllerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CharacterControllerGD
        return CharacterControllerGD(entlib.load_node_file(sourcefile, entlib.get_schema(CharacterControllerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CharacterControllerGD
        return CharacterControllerGD(entlib.make_node(CharacterControllerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AllowHeightMapFallback(self):  # type: ()->Bool
        return Bool(self._node.at("AllowHeightMapFallback"))
    @AllowHeightMapFallback.setter
    def AllowHeightMapFallback(self, val): self.AllowHeightMapFallback.set(val)
    @property
    def ClamberData(self):  # type: ()->CharacterControllerClamberData
        return CharacterControllerClamberData(self._node.at("ClamberData"))
    @property
    def FallData(self):  # type: ()->CharacterControllerFallData
        return CharacterControllerFallData(self._node.at("FallData"))
    @property
    def GroundNormalData(self):  # type: ()->CharacterControllerGroundNormalData
        return CharacterControllerGroundNormalData(self._node.at("GroundNormalData"))
    @property
    def HeadCollisionData(self):  # type: ()->HeadCollisionBehaviorData
        return HeadCollisionBehaviorData(self._node.at("HeadCollisionData"))
    @property
    def HitWallData(self):  # type: ()->HitWallData
        return HitWallData(self._node.at("HitWallData"))
    @property
    def ImmersedData(self):  # type: ()->ImmersedBehaviorData
        return ImmersedBehaviorData(self._node.at("ImmersedData"))
    @property
    def InputCollisionData(self):  # type: ()->InputCollisionBehaviorData
        return InputCollisionBehaviorData(self._node.at("InputCollisionData"))
    @property
    def MeshNavigationData(self):  # type: ()->MeshNavigationBehaviorData
        return MeshNavigationBehaviorData(self._node.at("MeshNavigationData"))
    @property
    def PredictionData(self):  # type: ()->PredictionBehaviorData
        return PredictionBehaviorData(self._node.at("PredictionData"))
    @property
    def RotationSmooth(self):  # type: ()->Vector3
        return Vector3(self._node.at("RotationSmooth"))
    @RotationSmooth.setter
    def RotationSmooth(self, val): self.RotationSmooth.set(val)
    @property
    def SlideData(self):  # type: ()->CharacterControllerSlideData
        return CharacterControllerSlideData(self._node.at("SlideData"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def climbEdgeData(self):  # type: ()->ClimbEdgeData
        return ClimbEdgeData(self._node.at("climbEdgeData"))
    @property
    def moveCapacityData(self):  # type: ()->MoveCapacityData
        return MoveCapacityData(self._node.at("moveCapacityData"))
    pass




