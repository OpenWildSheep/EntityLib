
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentInput import *
from entgen.ReviveEnergyComponentInput_EnergySide import *

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
    def EnergySide(self):  # type: ()->ReviveEnergyComponentInput_EnergySide
        return ReviveEnergyComponentInput_EnergySide(self._node.at("EnergySide"))
    @property
    def Super(self):  # type: ()->ComponentInput
        return ComponentInput(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




