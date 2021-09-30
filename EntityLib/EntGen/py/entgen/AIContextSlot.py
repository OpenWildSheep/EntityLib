
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *


class AIContextSlot(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AIContextSlot"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(AIContextSlot.schema_name))
    @property
    def Count(self): return Int(self._node.at("Count"))
    @Count.setter
    def Count(self, val): self.Count.set(val)
    @property
    def Name(self): return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




