
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *

from EntityLibPy import Node

class DistanceTriggerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/DistanceTriggerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->DistanceTriggerGD
        return DistanceTriggerGD(entlib.load_node_file(sourcefile, entlib.get_schema(DistanceTriggerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->DistanceTriggerGD
        return DistanceTriggerGD(entlib.make_node(DistanceTriggerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Distances(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("Distances"))
    @Distances.setter
    def Distances(self, val): self.Distances.set(val)
    @property
    def Hystereses(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("Hystereses"))
    @Hystereses.setter
    def Hystereses(self, val): self.Hystereses.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




