
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.CineEventTest import *


class CineEventTestInput(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CineEventTestInput"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTestInput.schema_name))
    @property
    def AnyButtonInput(self): return Bool(self._node.at("AnyButtonInput"))
    @AnyButtonInput.setter
    def AnyButtonInput(self, val): self.AnyButtonInput.set(val)
    @property
    def AnyJoyInput(self): return Bool(self._node.at("AnyJoyInput"))
    @AnyJoyInput.setter
    def AnyJoyInput(self, val): self.AnyJoyInput.set(val)
    @property
    def Super(self): return CineEventTest(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




