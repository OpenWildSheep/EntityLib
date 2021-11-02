
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.Manager import *

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
    def EnergyMaxValue(self):  # type: ()->Float
        return Float(self._node.at("EnergyMaxValue"))
    @EnergyMaxValue.setter
    def EnergyMaxValue(self, val): self.EnergyMaxValue.set(val)
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
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




