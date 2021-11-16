
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.ReviveSide import *
from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.VomitData import *
from entgen.Float import *

from EntityLibPy import Node

class RevivedData(HelperObject):
    schema_name = "RevivedData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RevivedData
        return RevivedData(entlib.load_node_file(sourcefile, entlib.get_schema(RevivedData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RevivedData
        return RevivedData(entlib.make_node(RevivedData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CanBeFreed(self):  # type: ()->Bool
        return Bool(self._node.at("CanBeFreed"))
    @CanBeFreed.setter
    def CanBeFreed(self, val): self.CanBeFreed.set(val)
    @property
    def DecreaseOverTimeSpeed(self):  # type: ()->Float
        return Float(self._node.at("DecreaseOverTimeSpeed"))
    @DecreaseOverTimeSpeed.setter
    def DecreaseOverTimeSpeed(self, val): self.DecreaseOverTimeSpeed.set(val)
    @property
    def LifeMinHysteresis(self):  # type: ()->Float
        return Float(self._node.at("LifeMinHysteresis"))
    @LifeMinHysteresis.setter
    def LifeMinHysteresis(self, val): self.LifeMinHysteresis.set(val)
    @property
    def LifeMinReviveSideNeutral(self):  # type: ()->Float
        return Float(self._node.at("LifeMinReviveSideNeutral"))
    @LifeMinReviveSideNeutral.setter
    def LifeMinReviveSideNeutral(self, val): self.LifeMinReviveSideNeutral.set(val)
    @property
    def NonCreatureConvertRatio(self):  # type: ()->Float
        return Float(self._node.at("NonCreatureConvertRatio"))
    @NonCreatureConvertRatio.setter
    def NonCreatureConvertRatio(self, val): self.NonCreatureConvertRatio.set(val)
    @property
    def RequestReviveLocked(self):  # type: ()->Bool
        return Bool(self._node.at("RequestReviveLocked"))
    @RequestReviveLocked.setter
    def RequestReviveLocked(self, val): self.RequestReviveLocked.set(val)
    @property
    def ReviveEnergyMax(self):  # type: ()->Float
        return Float(self._node.at("ReviveEnergyMax"))
    @ReviveEnergyMax.setter
    def ReviveEnergyMax(self, val): self.ReviveEnergyMax.set(val)
    @property
    def ReviveSinAmplitude(self):  # type: ()->Float
        return Float(self._node.at("ReviveSinAmplitude"))
    @ReviveSinAmplitude.setter
    def ReviveSinAmplitude(self, val): self.ReviveSinAmplitude.set(val)
    @property
    def StartSide(self):  # type: ()->ReviveSide
        return ReviveSide(self._node.at("StartSide"))
    @StartSide.setter
    def StartSide(self, val): self.StartSide.set(val)
    @property
    def StateThresholds(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("StateThresholds"))
    @StateThresholds.setter
    def StateThresholds(self, val): self.StateThresholds.set(val)
    @property
    def TimeBeforeFree(self):  # type: ()->Float
        return Float(self._node.at("TimeBeforeFree"))
    @TimeBeforeFree.setter
    def TimeBeforeFree(self, val): self.TimeBeforeFree.set(val)
    @property
    def VomitData(self):  # type: ()->VomitData
        return VomitData(self._node.at("VomitData"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




