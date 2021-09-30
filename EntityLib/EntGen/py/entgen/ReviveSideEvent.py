
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.ReviveSide import *
from entgen.String import *
from entgen.Float import *


class ReviveSideEvent(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ReviveSideEvent"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(ReviveSideEvent.schema_name))
    @property
    def ElapsedTime(self): return Float(self._node.at("ElapsedTime"))
    @ElapsedTime.setter
    def ElapsedTime(self, val): self.ElapsedTime.set(val)
    @property
    def ReviveSide(self): return ReviveSide(self._node.at("ReviveSide"))
    @ReviveSide.setter
    def ReviveSide(self, val): self.ReviveSide.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




