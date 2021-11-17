
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.FluidType import *
from entgen.String import *
from entgen.Float import *
from entgen.Vector2 import *

from EntityLibPy import Node

class FluidData(HelperObject):
    schema_name = "FluidData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FluidData
        return FluidData(entlib.load_node_file(sourcefile, entlib.get_schema(FluidData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FluidData
        return FluidData(entlib.make_node(FluidData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def depth(self):  # type: ()->Float
        return Float(self._node.at("depth"))
    @depth.setter
    def depth(self, val): self.depth.set(val)
    @property
    def energy(self):  # type: ()->Float
        return Float(self._node.at("energy"))
    @energy.setter
    def energy(self, val): self.energy.set(val)
    @property
    def flow(self):  # type: ()->Vector2
        return Vector2(self._node.at("flow"))
    @flow.setter
    def flow(self, val): self.flow.set(val)
    @property
    def level(self):  # type: ()->Float
        return Float(self._node.at("level"))
    @level.setter
    def level(self, val): self.level.set(val)
    @property
    def type(self):  # type: ()->FluidType
        return FluidType(self._node.at("type"))
    @type.setter
    def type(self, val): self.type.set(val)
    pass




