
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *

from EntityLibPy import Node

class TagInfo(HelperObject):
    schema_name = "TagInfo"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TagInfo
        return TagInfo(entlib.load_node_file(sourcefile, entlib.get_schema(TagInfo.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TagInfo
        return TagInfo(entlib.make_node(TagInfo.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AudioWeight(self):  # type: ()->Int
        return Int(self._node.at("AudioWeight"))
    @AudioWeight.setter
    def AudioWeight(self, val): self.AudioWeight.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




