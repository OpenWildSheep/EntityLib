
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *

from EntityLibPy import Node

class CineEvent(HelperObject):
    schema_name = "CineEvent"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CineEvent
        return CineEvent(entlib.load_node_file(sourcefile, entlib.get_schema(CineEvent.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CineEvent
        return CineEvent(entlib.make_node(CineEvent.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Active(self):  # type: ()->Bool
        return Bool(self._node.at("Active"))
    @Active.setter
    def Active(self, val): self.Active.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




