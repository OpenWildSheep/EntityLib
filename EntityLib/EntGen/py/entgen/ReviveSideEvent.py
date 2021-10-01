
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.ReviveSide import *
from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class ReviveSideEvent(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ReviveSideEvent"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ReviveSideEvent
        return ReviveSideEvent(entlib.load_node_file(sourcefile, entlib.get_schema(ReviveSideEvent.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ReviveSideEvent
        return ReviveSideEvent(entlib.make_node(ReviveSideEvent.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ElapsedTime(self):  # type: ()->Float
        return Float(self._node.at("ElapsedTime"))
    @ElapsedTime.setter
    def ElapsedTime(self, val): self.ElapsedTime.set(val)
    @property
    def ReviveSide(self):  # type: ()->ReviveSide
        return ReviveSide(self._node.at("ReviveSide"))
    @ReviveSide.setter
    def ReviveSide(self, val): self.ReviveSide.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




