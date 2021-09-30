
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *


class InteractData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/InteractData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(InteractData.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def distance(self): return Float(self._node.at("distance"))
    @distance.setter
    def distance(self, val): self.distance.set(val)
    pass




