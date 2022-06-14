
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class GameEdgeData(HelperObject):
    schema_name = "GameEdgeData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameEdgeData
        return GameEdgeData(entlib.load_node_file(sourcefile, entlib.get_schema(GameEdgeData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameEdgeData
        return GameEdgeData(entlib.make_node(GameEdgeData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EdgeAngleMax(self):  # type: ()->Float
        return Float(self._node.at("EdgeAngleMax"))
    @EdgeAngleMax.setter
    def EdgeAngleMax(self, val): self.EdgeAngleMax.set(val)
    @property
    def EdgeSizeMin(self):  # type: ()->Float
        return Float(self._node.at("EdgeSizeMin"))
    @EdgeSizeMin.setter
    def EdgeSizeMin(self, val): self.EdgeSizeMin.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




