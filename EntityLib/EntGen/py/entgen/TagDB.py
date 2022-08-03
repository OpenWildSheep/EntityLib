
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.TagInfo import *
from entgen.String import *

from EntityLibPy import Node

class TagDB(HelperObject):
    schema_name = "TagDB"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TagDB
        return TagDB(entlib.load_node_file(sourcefile, entlib.get_schema(TagDB.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TagDB
        return TagDB(entlib.make_node(TagDB.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def TagInfoTable(self):  # type: ()->Map[str, TagInfo]
        return (lambda n: Map(str, TagInfo, n))(self._node.at("TagInfoTable"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




