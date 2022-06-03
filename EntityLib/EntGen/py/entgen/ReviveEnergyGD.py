
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.EnergySide import *
from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *

from EntityLibPy import Node

class ReviveEnergyGD(HelperObject):
    schema_name = "ReviveEnergyGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ReviveEnergyGD
        return ReviveEnergyGD(entlib.load_node_file(sourcefile, entlib.get_schema(ReviveEnergyGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ReviveEnergyGD
        return ReviveEnergyGD(entlib.make_node(ReviveEnergyGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def HatchingCost(self):  # type: ()->Float
        return Float(self._node.at("HatchingCost"))
    @HatchingCost.setter
    def HatchingCost(self, val): self.HatchingCost.set(val)
    @property
    def HatchingDuration(self):  # type: ()->Float
        return Float(self._node.at("HatchingDuration"))
    @HatchingDuration.setter
    def HatchingDuration(self, val): self.HatchingDuration.set(val)
    @property
    def InitEnergySide(self):  # type: ()->EnergySide
        return EnergySide(self._node.at("InitEnergySide"))
    @InitEnergySide.setter
    def InitEnergySide(self, val): self.InitEnergySide.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




