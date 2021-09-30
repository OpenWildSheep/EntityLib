
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.EntityRef import *
from entgen.InventoryTags import *


class TaggedEntityRef(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/TaggedEntityRef"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(TaggedEntityRef.schema_name))
    @property
    def EntityRef(self): return EntityRef(self._node.at("EntityRef"))
    @EntityRef.setter
    def EntityRef(self, val): self.EntityRef.set(val)
    @property
    def Tags(self): return (lambda n: PrimArray(InventoryTags, n))(self._node.at("Tags"))
    @Tags.setter
    def Tags(self, val): self.Tags.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




