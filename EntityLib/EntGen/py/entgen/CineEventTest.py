
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.CineEvent import *


class CineEventTest(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CineEventTest"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTest.schema_name))
    @property
    def InvertTest(self): return Bool(self._node.at("InvertTest"))
    @InvertTest.setter
    def InvertTest(self, val): self.InvertTest.set(val)
    @property
    def Super(self): return CineEvent(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




