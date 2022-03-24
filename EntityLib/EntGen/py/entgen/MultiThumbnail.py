
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.ListItem import *

from EntityLibPy import Node

class MultiThumbnail(HelperObject):
    schema_name = "MultiThumbnail"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MultiThumbnail
        return MultiThumbnail(entlib.load_node_file(sourcefile, entlib.get_schema(MultiThumbnail.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MultiThumbnail
        return MultiThumbnail(entlib.make_node(MultiThumbnail.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def List(self):  # type: ()->Array[ListItem]
        return (lambda n: Array(ListItem, n))(self._node.at("List"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




