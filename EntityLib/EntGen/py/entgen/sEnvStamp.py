
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Bool import *
from entgen.Float import *
from entgen.Vector3 import *

from EntityLibPy import Node

class sEnvStamp(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sEnvStamp"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sEnvStamp
        return sEnvStamp(entlib.load_node_file(sourcefile, entlib.get_schema(sEnvStamp.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sEnvStamp
        return sEnvStamp(entlib.make_node(sEnvStamp.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AffectCoverage(self):  # type: ()->Bool
        return Bool(self._node.at("AffectCoverage"))
    @AffectCoverage.setter
    def AffectCoverage(self, val): self.AffectCoverage.set(val)
    @property
    def AffectFogColor(self):  # type: ()->Bool
        return Bool(self._node.at("AffectFogColor"))
    @AffectFogColor.setter
    def AffectFogColor(self, val): self.AffectFogColor.set(val)
    @property
    def AffectFogDensity(self):  # type: ()->Bool
        return Bool(self._node.at("AffectFogDensity"))
    @AffectFogDensity.setter
    def AffectFogDensity(self, val): self.AffectFogDensity.set(val)
    @property
    def AffectFogFalloff(self):  # type: ()->Bool
        return Bool(self._node.at("AffectFogFalloff"))
    @AffectFogFalloff.setter
    def AffectFogFalloff(self, val): self.AffectFogFalloff.set(val)
    @property
    def AffectFogHeight(self):  # type: ()->Bool
        return Bool(self._node.at("AffectFogHeight"))
    @AffectFogHeight.setter
    def AffectFogHeight(self, val): self.AffectFogHeight.set(val)
    @property
    def AffectPull(self):  # type: ()->Bool
        return Bool(self._node.at("AffectPull"))
    @AffectPull.setter
    def AffectPull(self, val): self.AffectPull.set(val)
    @property
    def AffectType(self):  # type: ()->Bool
        return Bool(self._node.at("AffectType"))
    @AffectType.setter
    def AffectType(self, val): self.AffectType.set(val)
    @property
    def AffectWetness(self):  # type: ()->Bool
        return Bool(self._node.at("AffectWetness"))
    @AffectWetness.setter
    def AffectWetness(self, val): self.AffectWetness.set(val)
    @property
    def AtlasID(self):  # type: ()->Int
        return Int(self._node.at("AtlasID"))
    @AtlasID.setter
    def AtlasID(self, val): self.AtlasID.set(val)
    @property
    def FogColor(self):  # type: ()->Vector3
        return Vector3(self._node.at("FogColor"))
    @FogColor.setter
    def FogColor(self, val): self.FogColor.set(val)
    @property
    def IsCloud(self):  # type: ()->Bool
        return Bool(self._node.at("IsCloud"))
    @IsCloud.setter
    def IsCloud(self, val): self.IsCloud.set(val)
    @property
    def PositionOffset(self):  # type: ()->Vector3
        return Vector3(self._node.at("PositionOffset"))
    @PositionOffset.setter
    def PositionOffset(self, val): self.PositionOffset.set(val)
    @property
    def Rotation(self):  # type: ()->Float
        return Float(self._node.at("Rotation"))
    @Rotation.setter
    def Rotation(self, val): self.Rotation.set(val)
    @property
    def Size(self):  # type: ()->Float
        return Float(self._node.at("Size"))
    @Size.setter
    def Size(self, val): self.Size.set(val)
    @property
    def Strength(self):  # type: ()->Float
        return Float(self._node.at("Strength"))
    @Strength.setter
    def Strength(self, val): self.Strength.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




