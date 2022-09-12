
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class CharacterControllerGroundNormalData(HelperObject):
    schema_name = "CharacterControllerGroundNormalData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CharacterControllerGroundNormalData
        return CharacterControllerGroundNormalData(entlib.load_node_file(sourcefile, entlib.get_schema(CharacterControllerGroundNormalData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CharacterControllerGroundNormalData
        return CharacterControllerGroundNormalData(entlib.make_node(CharacterControllerGroundNormalData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AllowOtherCreatureCast(self):  # type: ()->Bool
        return Bool(self._node.at("AllowOtherCreatureCast"))
    @AllowOtherCreatureCast.setter
    def AllowOtherCreatureCast(self, val): self.AllowOtherCreatureCast.set(val)
    @property
    def Length_Offset_When_Against_Wall(self):  # type: ()->Float
        return Float(self._node.at("Length Offset When Against Wall"))
    @Length_Offset_When_Against_Wall.setter
    def Length_Offset_When_Against_Wall(self, val): self.Length_Offset_When_Against_Wall.set(val)
    @property
    def PercentageEdgeTolerance(self):  # type: ()->Float
        return Float(self._node.at("PercentageEdgeTolerance"))
    @PercentageEdgeTolerance.setter
    def PercentageEdgeTolerance(self, val): self.PercentageEdgeTolerance.set(val)
    @property
    def PercentageExtirpate(self):  # type: ()->Float
        return Float(self._node.at("PercentageExtirpate"))
    @PercentageExtirpate.setter
    def PercentageExtirpate(self, val): self.PercentageExtirpate.set(val)
    @property
    def WallAngle(self):  # type: ()->Float
        return Float(self._node.at("WallAngle"))
    @WallAngle.setter
    def WallAngle(self, val): self.WallAngle.set(val)
    @property
    def WallCosAngleSpeedXYFactor(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("WallCosAngleSpeedXYFactor"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




