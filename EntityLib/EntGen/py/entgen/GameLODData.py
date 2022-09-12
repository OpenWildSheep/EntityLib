
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.Float import *

from EntityLibPy import Node

class GameLODData(HelperObject):
    schema_name = "GameLODData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameLODData
        return GameLODData(entlib.load_node_file(sourcefile, entlib.get_schema(GameLODData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameLODData
        return GameLODData(entlib.make_node(GameLODData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CreatureDistance(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("CreatureDistance"))
    @CreatureDistance.setter
    def CreatureDistance(self, val): self.CreatureDistance.set(val)
    @property
    def DistanceHysteresis(self):  # type: ()->Float
        return Float(self._node.at("DistanceHysteresis"))
    @DistanceHysteresis.setter
    def DistanceHysteresis(self, val): self.DistanceHysteresis.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




