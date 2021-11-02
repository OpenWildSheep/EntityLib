
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.TaggedEntityRef import *

from EntityLibPy import Node

class InventoryGD(HelperObject):
    schema_name = "InventoryGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->InventoryGD
        return InventoryGD(entlib.load_node_file(sourcefile, entlib.get_schema(InventoryGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->InventoryGD
        return InventoryGD(entlib.make_node(InventoryGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def TaggedEntityRefs(self):  # type: ()->Array[TaggedEntityRef]
        return (lambda n: Array(TaggedEntityRef, n))(self._node.at("TaggedEntityRefs"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




