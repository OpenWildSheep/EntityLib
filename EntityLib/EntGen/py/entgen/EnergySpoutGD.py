
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.EntityRef import *
from entgen.Float import *

from EntityLibPy import Node

class EnergySpoutGD(HelperObject):
    schema_name = "EnergySpoutGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EnergySpoutGD
        return EnergySpoutGD(entlib.load_node_file(sourcefile, entlib.get_schema(EnergySpoutGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EnergySpoutGD
        return EnergySpoutGD(entlib.make_node(EnergySpoutGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EnergySpeed(self):  # type: ()->Float
        return Float(self._node.at("EnergySpeed"))
    @EnergySpeed.setter
    def EnergySpeed(self, val): self.EnergySpeed.set(val)
    @property
    def ListenerEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("ListenerEntityRef"))
    @ListenerEntityRef.setter
    def ListenerEntityRef(self, val): self.ListenerEntityRef.set(val)
    @property
    def MinDistanceBetweenRegen(self):  # type: ()->Float
        return Float(self._node.at("MinDistanceBetweenRegen"))
    @MinDistanceBetweenRegen.setter
    def MinDistanceBetweenRegen(self, val): self.MinDistanceBetweenRegen.set(val)
    @property
    def MinTimeBetweenRegen(self):  # type: ()->Float
        return Float(self._node.at("MinTimeBetweenRegen"))
    @MinTimeBetweenRegen.setter
    def MinTimeBetweenRegen(self, val): self.MinTimeBetweenRegen.set(val)
    @property
    def Radius(self):  # type: ()->Float
        return Float(self._node.at("Radius"))
    @Radius.setter
    def Radius(self, val): self.Radius.set(val)
    @property
    def SplineRegenEffectName(self):  # type: ()->String
        return String(self._node.at("SplineRegenEffectName"))
    @SplineRegenEffectName.setter
    def SplineRegenEffectName(self, val): self.SplineRegenEffectName.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




