
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.String import *
from entgen.String import *


class TagsList(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/TagsList"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(TagsList.schema_name))
    @property
    def Tags(self): return (lambda n: Map(str, (lambda n: PrimitiveSet(str, n)), n))(self._node.at("Tags"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




