
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.String import *
from entgen.String import *

from EntityLibPy import Node

class TagsList(HelperObject):
    schema_name = "TagsList"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TagsList
        return TagsList(entlib.load_node_file(sourcefile, entlib.get_schema(TagsList.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TagsList
        return TagsList(entlib.make_node(TagsList.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Tags(self):  # type: ()->Map[str, PrimitiveSet[str]]
        return (lambda n: Map(str, (lambda n: PrimitiveSet(str, n)), n))(self._node.at("Tags"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




