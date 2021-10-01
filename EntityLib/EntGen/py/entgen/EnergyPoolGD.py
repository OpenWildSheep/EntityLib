
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.String import *

from EntityLibPy import Node

class EnergyPoolGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EnergyPoolGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EnergyPoolGD
        return EnergyPoolGD(entlib.load_node_file(sourcefile, entlib.get_schema(EnergyPoolGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EnergyPoolGD
        return EnergyPoolGD(entlib.make_node(EnergyPoolGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DrainConnectionRadius(self):  # type: ()->Float
        return Float(self._node.at("DrainConnectionRadius"))
    @DrainConnectionRadius.setter
    def DrainConnectionRadius(self, val): self.DrainConnectionRadius.set(val)
    @property
    def FactionOverride(self):  # type: ()->Bool
        return Bool(self._node.at("FactionOverride"))
    @FactionOverride.setter
    def FactionOverride(self, val): self.FactionOverride.set(val)
    @property
    def ProbeDetectionRadius(self):  # type: ()->Float
        return Float(self._node.at("ProbeDetectionRadius"))
    @ProbeDetectionRadius.setter
    def ProbeDetectionRadius(self, val): self.ProbeDetectionRadius.set(val)
    @property
    def RegenEffectsOnConversion(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("RegenEffectsOnConversion"))
    @RegenEffectsOnConversion.setter
    def RegenEffectsOnConversion(self, val): self.RegenEffectsOnConversion.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




