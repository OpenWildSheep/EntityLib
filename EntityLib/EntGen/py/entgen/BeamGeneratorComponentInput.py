
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentInput import *
from entgen.EndPosition import *

from EntityLibPy import Node

class BeamGeneratorComponentInput(HelperObject):
    schema_name = "BeamGeneratorComponentInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BeamGeneratorComponentInput
        return BeamGeneratorComponentInput(entlib.load_node_file(sourcefile, entlib.get_schema(BeamGeneratorComponentInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BeamGeneratorComponentInput
        return BeamGeneratorComponentInput(entlib.make_node(BeamGeneratorComponentInput.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EndPosition(self):  # type: ()->EndPosition
        return EndPosition(self._node.at("EndPosition"))
    @property
    def Super(self):  # type: ()->ComponentInput
        return ComponentInput(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




