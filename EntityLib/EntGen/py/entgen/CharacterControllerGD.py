
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.CharacterControllerClamberData import *
from entgen.CharacterControllerGroundNormalData import *
from entgen.CharacterControllerSlideData import *
from entgen.ComponentGD import *
from entgen.HeadCollisionBehaviorData import *
from entgen.ImmersedBehaviorData import *
from entgen.InputCollisionBehaviorData import *
from entgen.MeshNavigationBehaviorData import *
from entgen.MoveCapacityData import *
from entgen.PredictionBehaviorData import *
from entgen.Vector3 import *


class CharacterControllerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CharacterControllerGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(CharacterControllerGD.schema_name))
    @property
    def AllowHeightMapFallback(self): return Bool(self._node.at("AllowHeightMapFallback"))
    @AllowHeightMapFallback.setter
    def AllowHeightMapFallback(self, val): self.AllowHeightMapFallback.set(val)
    @property
    def ClamberData(self): return CharacterControllerClamberData(self._node.at("ClamberData"))
    @property
    def GroundNormalData(self): return CharacterControllerGroundNormalData(self._node.at("GroundNormalData"))
    @property
    def HeadCollisionData(self): return HeadCollisionBehaviorData(self._node.at("HeadCollisionData"))
    @property
    def ImmersedData(self): return ImmersedBehaviorData(self._node.at("ImmersedData"))
    @property
    def InputCollisionData(self): return InputCollisionBehaviorData(self._node.at("InputCollisionData"))
    @property
    def MeshNavigationData(self): return MeshNavigationBehaviorData(self._node.at("MeshNavigationData"))
    @property
    def PredictionData(self): return PredictionBehaviorData(self._node.at("PredictionData"))
    @property
    def RotationSmooth(self): return Vector3(self._node.at("RotationSmooth"))
    @RotationSmooth.setter
    def RotationSmooth(self, val): self.RotationSmooth.set(val)
    @property
    def SlideData(self): return CharacterControllerSlideData(self._node.at("SlideData"))
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def moveCapacityData(self): return MoveCapacityData(self._node.at("moveCapacityData"))
    pass




