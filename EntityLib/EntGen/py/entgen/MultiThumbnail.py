
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.ListItem import *


class MultiThumbnail(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/MultiThumbnail"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(MultiThumbnail.schema_name))
    @property
    def List(self): return (lambda n: Array(ListItem, n))(self._node.at("List"))
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




