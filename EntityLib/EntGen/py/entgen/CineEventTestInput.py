
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.CineEventTest import *

from EntityLibPy import Node

class CineEventTestInput(HelperObject):
    schema_name = "CineEventTestInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CineEventTestInput
        return CineEventTestInput(entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTestInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CineEventTestInput
        return CineEventTestInput(entlib.make_node(CineEventTestInput.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AnyButtonInput(self):  # type: ()->Bool
        return Bool(self._node.at("AnyButtonInput"))
    @AnyButtonInput.setter
    def AnyButtonInput(self, val): self.AnyButtonInput.set(val)
    @property
    def AnyJoyInput(self):  # type: ()->Bool
        return Bool(self._node.at("AnyJoyInput"))
    @AnyJoyInput.setter
    def AnyJoyInput(self, val): self.AnyJoyInput.set(val)
    @property
    def Super(self):  # type: ()->CineEventTest
        return CineEventTest(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




