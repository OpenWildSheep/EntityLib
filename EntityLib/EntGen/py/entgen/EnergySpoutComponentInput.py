
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentInput import *

from EntityLibPy import Node

class EnergySpoutComponentInput(HelperObject):
    schema_name = "EnergySpoutComponentInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EnergySpoutComponentInput
        return EnergySpoutComponentInput(entlib.load_node_file(sourcefile, entlib.get_schema(EnergySpoutComponentInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EnergySpoutComponentInput
        return EnergySpoutComponentInput(entlib.make_node(EnergySpoutComponentInput.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentInput
        return ComponentInput(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




