
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.CapabilitiesAndTags import *
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
    def CapabilitiesAndTags(self):  # type: ()->CapabilitiesAndTags
        return CapabilitiesAndTags(self._node.at("CapabilitiesAndTags"))
    @property
    def GroundAreaCost(self):  # type: ()->Float
        return Float(self._node.at("GroundAreaCost"))
    @GroundAreaCost.setter
    def GroundAreaCost(self, val): self.GroundAreaCost.set(val)
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




