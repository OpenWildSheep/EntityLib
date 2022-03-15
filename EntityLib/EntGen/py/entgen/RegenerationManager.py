
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.EnergyValue import *
from entgen.String import *
from entgen.Int import *
from entgen.Bool import *
from entgen.Float import *
from entgen.Manager import *
from entgen.RegenerationManager_EnergyAreaSetting import *
from entgen.EnergyIntensity import *

from EntityLibPy import Node

class RegenerationManager(HelperObject):
    schema_name = "RegenerationManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RegenerationManager
        return RegenerationManager(entlib.load_node_file(sourcefile, entlib.get_schema(RegenerationManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RegenerationManager
        return RegenerationManager(entlib.make_node(RegenerationManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BackgroundEnergyValue(self):  # type: ()->EnergyValue
        return EnergyValue(self._node.at("BackgroundEnergyValue"))
    @BackgroundEnergyValue.setter
    def BackgroundEnergyValue(self, val): self.BackgroundEnergyValue.set(val)
    @property
    def DefaultLostRatio(self):  # type: ()->Float
        return Float(self._node.at("DefaultLostRatio"))
    @DefaultLostRatio.setter
    def DefaultLostRatio(self, val): self.DefaultLostRatio.set(val)
    @property
    def DefaultMaxLossPerSecond(self):  # type: ()->Float
        return Float(self._node.at("DefaultMaxLossPerSecond"))
    @DefaultMaxLossPerSecond.setter
    def DefaultMaxLossPerSecond(self, val): self.DefaultMaxLossPerSecond.set(val)
    @property
    def DefaultMaxTransmissionPerSecond(self):  # type: ()->Float
        return Float(self._node.at("DefaultMaxTransmissionPerSecond"))
    @DefaultMaxTransmissionPerSecond.setter
    def DefaultMaxTransmissionPerSecond(self, val): self.DefaultMaxTransmissionPerSecond.set(val)
    @property
    def DefaultTransmittedRatio(self):  # type: ()->Float
        return Float(self._node.at("DefaultTransmittedRatio"))
    @DefaultTransmittedRatio.setter
    def DefaultTransmittedRatio(self, val): self.DefaultTransmittedRatio.set(val)
    @property
    def EnergyAreaSettingsMap(self):  # type: ()->Map[EnergyIntensityEnum, RegenerationManager_EnergyAreaSetting]
        return (lambda n: Map(EnergyIntensityEnum, RegenerationManager_EnergyAreaSetting, n))(self._node.at("EnergyAreaSettingsMap"))
    @property
    def EnergyMaxValue(self):  # type: ()->Float
        return Float(self._node.at("EnergyMaxValue"))
    @EnergyMaxValue.setter
    def EnergyMaxValue(self, val): self.EnergyMaxValue.set(val)
    @property
    def EnergyStrongValueThreshold(self):  # type: ()->Float
        return Float(self._node.at("EnergyStrongValueThreshold"))
    @EnergyStrongValueThreshold.setter
    def EnergyStrongValueThreshold(self, val): self.EnergyStrongValueThreshold.set(val)
    @property
    def EvaporationDecreaseSpeed(self):  # type: ()->Float
        return Float(self._node.at("EvaporationDecreaseSpeed"))
    @EvaporationDecreaseSpeed.setter
    def EvaporationDecreaseSpeed(self, val): self.EvaporationDecreaseSpeed.set(val)
    @property
    def EvaporationMaxValue(self):  # type: ()->Float
        return Float(self._node.at("EvaporationMaxValue"))
    @EvaporationMaxValue.setter
    def EvaporationMaxValue(self, val): self.EvaporationMaxValue.set(val)
    @property
    def InjectedEvaporationMultiplier(self):  # type: ()->Float
        return Float(self._node.at("InjectedEvaporationMultiplier"))
    @InjectedEvaporationMultiplier.setter
    def InjectedEvaporationMultiplier(self, val): self.InjectedEvaporationMultiplier.set(val)
    @property
    def MaxDispatchedRegenQueries(self):  # type: ()->Int
        return Int(self._node.at("MaxDispatchedRegenQueries"))
    @MaxDispatchedRegenQueries.setter
    def MaxDispatchedRegenQueries(self, val): self.MaxDispatchedRegenQueries.set(val)
    @property
    def MaxDynamicRegenEffectCount(self):  # type: ()->Int
        return Int(self._node.at("MaxDynamicRegenEffectCount"))
    @MaxDynamicRegenEffectCount.setter
    def MaxDynamicRegenEffectCount(self, val): self.MaxDynamicRegenEffectCount.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def UseNewRegenSystem(self):  # type: ()->Bool
        return Bool(self._node.at("UseNewRegenSystem"))
    @UseNewRegenSystem.setter
    def UseNewRegenSystem(self, val): self.UseNewRegenSystem.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




