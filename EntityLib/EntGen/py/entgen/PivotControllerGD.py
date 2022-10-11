
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *

from EntityLibPy import Node

class PivotControllerGD(HelperObject):
    schema_name = "PivotControllerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PivotControllerGD
        return PivotControllerGD(entlib.load_node_file(sourcefile, entlib.get_schema(PivotControllerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PivotControllerGD
        return PivotControllerGD(entlib.make_node(PivotControllerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def GrowthTime(self):  # type: ()->Float
        return Float(self._node.at("GrowthTime"))
    @GrowthTime.setter
    def GrowthTime(self, val): self.GrowthTime.set(val)
    @property
    def InitialGrowth(self):  # type: ()->Float
        return Float(self._node.at("InitialGrowth"))
    @InitialGrowth.setter
    def InitialGrowth(self, val): self.InitialGrowth.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




