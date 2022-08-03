
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.EnergyValue import *
from entgen.String import *
from entgen.Int import *
from entgen.Bool import *
from entgen.Float import *
from entgen.Manager import *
from entgen.RegenAreaTransitionSettings import *
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
    def DefaultTransitionWaveSettings(self):  # type: ()->RegenAreaTransitionSettings
        return RegenAreaTransitionSettings(self._node.at("DefaultTransitionWaveSettings"))
    @property
    def EnergyAreaSettingsMap(self):  # type: ()->Map[EnergyIntensityEnum, RegenerationManager_EnergyAreaSetting]
        return (lambda n: Map(EnergyIntensityEnum, RegenerationManager_EnergyAreaSetting, n))(self._node.at("EnergyAreaSettingsMap"))
    @property
    def EnergyStrongValueThreshold(self):  # type: ()->Float
        return Float(self._node.at("EnergyStrongValueThreshold"))
    @EnergyStrongValueThreshold.setter
    def EnergyStrongValueThreshold(self, val): self.EnergyStrongValueThreshold.set(val)
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
    def MaxRegenAreaPerCluster(self):  # type: ()->Int
        return Int(self._node.at("MaxRegenAreaPerCluster"))
    @MaxRegenAreaPerCluster.setter
    def MaxRegenAreaPerCluster(self, val): self.MaxRegenAreaPerCluster.set(val)
    @property
    def RegenAreaClusterWorldSize(self):  # type: ()->Int
        return Int(self._node.at("RegenAreaClusterWorldSize"))
    @RegenAreaClusterWorldSize.setter
    def RegenAreaClusterWorldSize(self, val): self.RegenAreaClusterWorldSize.set(val)
    @property
    def RegenAreaClustering(self):  # type: ()->Bool
        return Bool(self._node.at("RegenAreaClustering"))
    @RegenAreaClustering.setter
    def RegenAreaClustering(self, val): self.RegenAreaClustering.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




