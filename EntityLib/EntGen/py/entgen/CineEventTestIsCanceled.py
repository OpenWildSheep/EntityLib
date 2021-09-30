
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.CineEventTest import *


class CineEventTestIsCanceled(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CineEventTestIsCanceled"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTestIsCanceled.schema_name))
    @property
    def Super(self): return CineEventTest(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




