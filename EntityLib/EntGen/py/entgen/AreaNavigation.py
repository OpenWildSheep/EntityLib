
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *

from EntityLibPy import Node

class AreaNavigation(HelperObject):
    schema_name = "AreaNavigation"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AreaNavigation
        return AreaNavigation(entlib.load_node_file(sourcefile, entlib.get_schema(AreaNavigation.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AreaNavigation
        return AreaNavigation(entlib.make_node(AreaNavigation.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def GroundAreaCost(self):  # type: ()->Float
        return Float(self._node.at("GroundAreaCost"))
    @GroundAreaCost.setter
    def GroundAreaCost(self, val): self.GroundAreaCost.set(val)
    @property
    def MovesInWater(self):  # type: ()->Bool
        return Bool(self._node.at("MovesInWater"))
    @MovesInWater.setter
    def MovesInWater(self, val): self.MovesInWater.set(val)
    @property
    def MovesOnGround(self):  # type: ()->Bool
        return Bool(self._node.at("MovesOnGround"))
    @MovesOnGround.setter
    def MovesOnGround(self, val): self.MovesOnGround.set(val)
    @property
    def WaterAreaCost(self):  # type: ()->Float
        return Float(self._node.at("WaterAreaCost"))
    @WaterAreaCost.setter
    def WaterAreaCost(self, val): self.WaterAreaCost.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




