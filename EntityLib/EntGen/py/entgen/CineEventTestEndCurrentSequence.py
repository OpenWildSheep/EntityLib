
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.CineEventTest import *

from EntityLibPy import Node

class CineEventTestEndCurrentSequence(HelperObject):
    schema_name = "CineEventTestEndCurrentSequence"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CineEventTestEndCurrentSequence
        return CineEventTestEndCurrentSequence(entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTestEndCurrentSequence.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CineEventTestEndCurrentSequence
        return CineEventTestEndCurrentSequence(entlib.make_node(CineEventTestEndCurrentSequence.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->CineEventTest
        return CineEventTest(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




