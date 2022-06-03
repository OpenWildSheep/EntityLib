
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *

from EntityLibPy import Node

class AIContextSlot(HelperObject):
    schema_name = "AIContextSlot"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AIContextSlot
        return AIContextSlot(entlib.load_node_file(sourcefile, entlib.get_schema(AIContextSlot.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AIContextSlot
        return AIContextSlot(entlib.make_node(AIContextSlot.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Count(self):  # type: ()->Int
        return Int(self._node.at("Count"))
    @Count.setter
    def Count(self, val): self.Count.set(val)
    @property
    def Name(self):  # type: ()->String
        return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




