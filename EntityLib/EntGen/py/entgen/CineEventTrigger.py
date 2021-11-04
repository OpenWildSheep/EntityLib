
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.CineEvent import *

from EntityLibPy import Node

class CineEventTrigger(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CineEventTrigger"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CineEventTrigger
        return CineEventTrigger(entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTrigger.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CineEventTrigger
        return CineEventTrigger(entlib.make_node(CineEventTrigger.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->CineEvent
        return CineEvent(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




