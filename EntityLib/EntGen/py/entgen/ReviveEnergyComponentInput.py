
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentInput import *
from entgen.Energy import *
from entgen.LastValidedReviveSide import *
from entgen.ReviveEnergyComponentInput_ReviveSide import *

from EntityLibPy import Node

class ReviveEnergyComponentInput(HelperObject):
    schema_name = "ReviveEnergyComponentInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ReviveEnergyComponentInput
        return ReviveEnergyComponentInput(entlib.load_node_file(sourcefile, entlib.get_schema(ReviveEnergyComponentInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ReviveEnergyComponentInput
        return ReviveEnergyComponentInput(entlib.make_node(ReviveEnergyComponentInput.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Energy(self):  # type: ()->Energy
        return Energy(self._node.at("Energy"))
    @property
    def LastValidedReviveSide(self):  # type: ()->LastValidedReviveSide
        return LastValidedReviveSide(self._node.at("LastValidedReviveSide"))
    @property
    def ReviveSide(self):  # type: ()->ReviveEnergyComponentInput_ReviveSide
        return ReviveEnergyComponentInput_ReviveSide(self._node.at("ReviveSide"))
    @property
    def Super(self):  # type: ()->ComponentInput
        return ComponentInput(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




