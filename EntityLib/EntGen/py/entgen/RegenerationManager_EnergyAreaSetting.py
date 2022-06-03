
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class RegenerationManager_EnergyAreaSetting(HelperObject):
    schema_name = "RegenerationManager::EnergyAreaSetting"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RegenerationManager_EnergyAreaSetting
        return RegenerationManager_EnergyAreaSetting(entlib.load_node_file(sourcefile, entlib.get_schema(RegenerationManager_EnergyAreaSetting.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RegenerationManager_EnergyAreaSetting
        return RegenerationManager_EnergyAreaSetting(entlib.make_node(RegenerationManager_EnergyAreaSetting.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def RegenValue(self):  # type: ()->Float
        return Float(self._node.at("RegenValue"))
    @RegenValue.setter
    def RegenValue(self, val): self.RegenValue.set(val)
    @property
    def SmoothMargin(self):  # type: ()->Float
        return Float(self._node.at("SmoothMargin"))
    @SmoothMargin.setter
    def SmoothMargin(self, val): self.SmoothMargin.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




