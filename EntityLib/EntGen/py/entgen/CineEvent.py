
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *


class CineEvent(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CineEvent"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(CineEvent.schema_name))
    @property
    def Active(self): return Bool(self._node.at("Active"))
    @Active.setter
    def Active(self, val): self.Active.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




