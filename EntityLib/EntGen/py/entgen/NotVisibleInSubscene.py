
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class NotVisibleInSubscene(HelperObject):
    schema_name = "NotVisibleInSubscene"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->NotVisibleInSubscene
        return NotVisibleInSubscene(entlib.load_node_file(sourcefile, entlib.get_schema(NotVisibleInSubscene.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->NotVisibleInSubscene
        return NotVisibleInSubscene(entlib.make_node(NotVisibleInSubscene.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




