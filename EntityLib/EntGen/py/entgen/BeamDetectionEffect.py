
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.GameEffect import *

from EntityLibPy import Node

class BeamDetectionEffect(HelperObject):
    schema_name = "BeamDetectionEffect"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BeamDetectionEffect
        return BeamDetectionEffect(entlib.load_node_file(sourcefile, entlib.get_schema(BeamDetectionEffect.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BeamDetectionEffect
        return BeamDetectionEffect(entlib.make_node(BeamDetectionEffect.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->GameEffect
        return GameEffect(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




