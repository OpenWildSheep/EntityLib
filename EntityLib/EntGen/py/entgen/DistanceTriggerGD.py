
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *


class DistanceTriggerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/DistanceTriggerGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(DistanceTriggerGD.schema_name))
    @property
    def Distances(self): return (lambda n: PrimArray(Float, n))(self._node.at("Distances"))
    @Distances.setter
    def Distances(self, val): self.Distances.set(val)
    @property
    def Hystereses(self): return (lambda n: PrimArray(Float, n))(self._node.at("Hystereses"))
    @Hystereses.setter
    def Hystereses(self, val): self.Hystereses.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




