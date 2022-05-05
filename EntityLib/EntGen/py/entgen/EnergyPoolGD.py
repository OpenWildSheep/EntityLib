
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.TransitionSettings import *
from entgen.String import *
from entgen.EnergyPoolGD_EnergyArea import *

from EntityLibPy import Node

class EnergyPoolGD(HelperObject):
    schema_name = "EnergyPoolGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EnergyPoolGD
        return EnergyPoolGD(entlib.load_node_file(sourcefile, entlib.get_schema(EnergyPoolGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EnergyPoolGD
        return EnergyPoolGD(entlib.make_node(EnergyPoolGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EnergyAreas(self):  # type: ()->Array[EnergyPoolGD_EnergyArea]
        return (lambda n: Array(EnergyPoolGD_EnergyArea, n))(self._node.at("EnergyAreas"))
    @property
    def FactionOverride(self):  # type: ()->Bool
        return Bool(self._node.at("FactionOverride"))
    @FactionOverride.setter
    def FactionOverride(self, val): self.FactionOverride.set(val)
    @property
    def RegenEffectsOnConversion(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("RegenEffectsOnConversion"))
    @RegenEffectsOnConversion.setter
    def RegenEffectsOnConversion(self, val): self.RegenEffectsOnConversion.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def TransitionSettings(self):  # type: ()->TransitionSettings
        return TransitionSettings(self._node.at("TransitionSettings"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




