
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.TaggedEntityRef import *


class InventoryGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/InventoryGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(InventoryGD.schema_name))
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def TaggedEntityRefs(self): return (lambda n: Array(TaggedEntityRef, n))(self._node.at("TaggedEntityRefs"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




