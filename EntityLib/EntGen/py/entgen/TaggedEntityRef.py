
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.EntityRef import *
from entgen.InventoryTags import *

from EntityLibPy import Node

class TaggedEntityRef(HelperObject):
    schema_name = "TaggedEntityRef"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TaggedEntityRef
        return TaggedEntityRef(entlib.load_node_file(sourcefile, entlib.get_schema(TaggedEntityRef.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TaggedEntityRef
        return TaggedEntityRef(entlib.make_node(TaggedEntityRef.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("EntityRef"))
    @EntityRef.setter
    def EntityRef(self, val): self.EntityRef.set(val)
    @property
    def Tags(self):  # type: ()->PrimArray[InventoryTags]
        return (lambda n: PrimArray(InventoryTags, n))(self._node.at("Tags"))
    @Tags.setter
    def Tags(self, val): self.Tags.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




