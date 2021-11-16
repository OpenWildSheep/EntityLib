
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.ReviveSide import *
from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *

from EntityLibPy import Node

class EnergySourceGD(HelperObject):
    schema_name = "EnergySourceGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EnergySourceGD
        return EnergySourceGD(entlib.load_node_file(sourcefile, entlib.get_schema(EnergySourceGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EnergySourceGD
        return EnergySourceGD(entlib.make_node(EnergySourceGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def MaxBuffDuration(self):  # type: ()->Float
        return Float(self._node.at("MaxBuffDuration"))
    @MaxBuffDuration.setter
    def MaxBuffDuration(self, val): self.MaxBuffDuration.set(val)
    @property
    def NearbyReactionRadius(self):  # type: ()->Float
        return Float(self._node.at("NearbyReactionRadius"))
    @NearbyReactionRadius.setter
    def NearbyReactionRadius(self, val): self.NearbyReactionRadius.set(val)
    @property
    def Radius(self):  # type: ()->Float
        return Float(self._node.at("Radius"))
    @Radius.setter
    def Radius(self, val): self.Radius.set(val)
    @property
    def RefreshFrequency(self):  # type: ()->Float
        return Float(self._node.at("RefreshFrequency"))
    @RefreshFrequency.setter
    def RefreshFrequency(self, val): self.RefreshFrequency.set(val)
    @property
    def ReviveSide(self):  # type: ()->ReviveSide
        return ReviveSide(self._node.at("ReviveSide"))
    @ReviveSide.setter
    def ReviveSide(self, val): self.ReviveSide.set(val)
    @property
    def SourceRegenEffectName(self):  # type: ()->String
        return String(self._node.at("SourceRegenEffectName"))
    @SourceRegenEffectName.setter
    def SourceRegenEffectName(self, val): self.SourceRegenEffectName.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




