
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.ConstrainedMoveContextInput import *

from EntityLibPy import Node

class ConstrainedMoveGD(HelperObject):
    schema_name = "ConstrainedMoveGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ConstrainedMoveGD
        return ConstrainedMoveGD(entlib.load_node_file(sourcefile, entlib.get_schema(ConstrainedMoveGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ConstrainedMoveGD
        return ConstrainedMoveGD(entlib.make_node(ConstrainedMoveGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ConstrainedMoveContextInput(self):  # type: ()->ConstrainedMoveContextInput
        return ConstrainedMoveContextInput(self._node.at("ConstrainedMoveContextInput"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




