
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.EntityRef import *
from entgen.Float import *


class EnergySpoutGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EnergySpoutGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(EnergySpoutGD.schema_name))
    @property
    def EnergySpeed(self): return Float(self._node.at("EnergySpeed"))
    @EnergySpeed.setter
    def EnergySpeed(self, val): self.EnergySpeed.set(val)
    @property
    def ListenerEntityRef(self): return EntityRef(self._node.at("ListenerEntityRef"))
    @ListenerEntityRef.setter
    def ListenerEntityRef(self, val): self.ListenerEntityRef.set(val)
    @property
    def MinDistanceBetweenRegen(self): return Float(self._node.at("MinDistanceBetweenRegen"))
    @MinDistanceBetweenRegen.setter
    def MinDistanceBetweenRegen(self, val): self.MinDistanceBetweenRegen.set(val)
    @property
    def MinTimeBetweenRegen(self): return Float(self._node.at("MinTimeBetweenRegen"))
    @MinTimeBetweenRegen.setter
    def MinTimeBetweenRegen(self, val): self.MinTimeBetweenRegen.set(val)
    @property
    def Radius(self): return Float(self._node.at("Radius"))
    @Radius.setter
    def Radius(self, val): self.Radius.set(val)
    @property
    def SplineRegenEffectName(self): return String(self._node.at("SplineRegenEffectName"))
    @SplineRegenEffectName.setter
    def SplineRegenEffectName(self, val): self.SplineRegenEffectName.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




