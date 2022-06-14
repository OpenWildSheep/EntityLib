
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentInput import *
from entgen.EndPosition import *
from entgen.IsActive import *

from EntityLibPy import Node

class InteractorComponentInput(HelperObject):
    schema_name = "InteractorComponentInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->InteractorComponentInput
        return InteractorComponentInput(entlib.load_node_file(sourcefile, entlib.get_schema(InteractorComponentInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->InteractorComponentInput
        return InteractorComponentInput(entlib.make_node(InteractorComponentInput.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EndPosition(self):  # type: ()->EndPosition
        return EndPosition(self._node.at("EndPosition"))
    @property
    def IsActive(self):  # type: ()->IsActive
        return IsActive(self._node.at("IsActive"))
    @property
    def Super(self):  # type: ()->ComponentInput
        return ComponentInput(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




