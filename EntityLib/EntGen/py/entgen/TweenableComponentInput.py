
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentInput import *
from entgen.Progress import *

from EntityLibPy import Node

class TweenableComponentInput(HelperObject):
    schema_name = "TweenableComponentInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TweenableComponentInput
        return TweenableComponentInput(entlib.load_node_file(sourcefile, entlib.get_schema(TweenableComponentInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TweenableComponentInput
        return TweenableComponentInput(entlib.make_node(TweenableComponentInput.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Progress(self):  # type: ()->Progress
        return Progress(self._node.at("Progress"))
    @property
    def Super(self):  # type: ()->ComponentInput
        return ComponentInput(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




