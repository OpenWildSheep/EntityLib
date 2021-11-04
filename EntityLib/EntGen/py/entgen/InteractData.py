
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class InteractData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/InteractData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->InteractData
        return InteractData(entlib.load_node_file(sourcefile, entlib.get_schema(InteractData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->InteractData
        return InteractData(entlib.make_node(InteractData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def distance(self):  # type: ()->Float
        return Float(self._node.at("distance"))
    @distance.setter
    def distance(self, val): self.distance.set(val)
    pass




