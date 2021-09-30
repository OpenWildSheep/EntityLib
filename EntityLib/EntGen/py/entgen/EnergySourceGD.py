
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.ReviveSide import *
from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *


class EnergySourceGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EnergySourceGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(EnergySourceGD.schema_name))
    @property
    def MaxBuffDuration(self): return Float(self._node.at("MaxBuffDuration"))
    @MaxBuffDuration.setter
    def MaxBuffDuration(self, val): self.MaxBuffDuration.set(val)
    @property
    def NearbyReactionRadius(self): return Float(self._node.at("NearbyReactionRadius"))
    @NearbyReactionRadius.setter
    def NearbyReactionRadius(self, val): self.NearbyReactionRadius.set(val)
    @property
    def Radius(self): return Float(self._node.at("Radius"))
    @Radius.setter
    def Radius(self, val): self.Radius.set(val)
    @property
    def RefreshFrequency(self): return Float(self._node.at("RefreshFrequency"))
    @RefreshFrequency.setter
    def RefreshFrequency(self, val): self.RefreshFrequency.set(val)
    @property
    def ReviveSide(self): return ReviveSide(self._node.at("ReviveSide"))
    @ReviveSide.setter
    def ReviveSide(self, val): self.ReviveSide.set(val)
    @property
    def SourceRegenEffectName(self): return String(self._node.at("SourceRegenEffectName"))
    @SourceRegenEffectName.setter
    def SourceRegenEffectName(self, val): self.SourceRegenEffectName.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




