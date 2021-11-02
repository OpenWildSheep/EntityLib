
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.CineEvent import *

from EntityLibPy import Node

class CineEventTest(HelperObject):
    schema_name = "CineEventTest"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CineEventTest
        return CineEventTest(entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTest.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CineEventTest
        return CineEventTest(entlib.make_node(CineEventTest.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def InvertTest(self):  # type: ()->Bool
        return Bool(self._node.at("InvertTest"))
    @InvertTest.setter
    def InvertTest(self, val): self.InvertTest.set(val)
    @property
    def Super(self):  # type: ()->CineEvent
        return CineEvent(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




