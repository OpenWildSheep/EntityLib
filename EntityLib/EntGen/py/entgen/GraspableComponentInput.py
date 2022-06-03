
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentInput import *
from entgen.retiming import *
from entgen.allowedTypesItem import *

from EntityLibPy import Node

class GraspableComponentInput(HelperObject):
    schema_name = "GraspableComponentInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GraspableComponentInput
        return GraspableComponentInput(entlib.load_node_file(sourcefile, entlib.get_schema(GraspableComponentInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GraspableComponentInput
        return GraspableComponentInput(entlib.make_node(GraspableComponentInput.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentInput
        return ComponentInput(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def allowedTypes(self):  # type: ()->Array[allowedTypesItem]
        return (lambda n: Array(allowedTypesItem, n))(self._node.at("allowedTypes"))
    @property
    def retiming(self):  # type: ()->retiming
        return retiming(self._node.at("retiming"))
    pass




