
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.String import *


class EnergyPoolGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EnergyPoolGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(EnergyPoolGD.schema_name))
    @property
    def DrainConnectionRadius(self): return Float(self._node.at("DrainConnectionRadius"))
    @DrainConnectionRadius.setter
    def DrainConnectionRadius(self, val): self.DrainConnectionRadius.set(val)
    @property
    def FactionOverride(self): return Bool(self._node.at("FactionOverride"))
    @FactionOverride.setter
    def FactionOverride(self, val): self.FactionOverride.set(val)
    @property
    def ProbeDetectionRadius(self): return Float(self._node.at("ProbeDetectionRadius"))
    @ProbeDetectionRadius.setter
    def ProbeDetectionRadius(self, val): self.ProbeDetectionRadius.set(val)
    @property
    def RegenEffectsOnConversion(self): return (lambda n: PrimArray(String, n))(self._node.at("RegenEffectsOnConversion"))
    @RegenEffectsOnConversion.setter
    def RegenEffectsOnConversion(self, val): self.RegenEffectsOnConversion.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




