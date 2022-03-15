
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.FluidType import *
from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.Vector3 import *
from entgen.constraintPlaneWorldPosition import *

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
    def constraintPlaneWorldPosition(self):  # type: ()->constraintPlaneWorldPosition
        return constraintPlaneWorldPosition(self._node.at("constraintPlaneWorldPosition"))
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
    def fluidCurrent(self):  # type: ()->Vector3
        return Vector3(self._node.at("fluidCurrent"))
    @fluidCurrent.setter
    def fluidCurrent(self, val): self.fluidCurrent.set(val)
    @property
    def hasDepthImpactOnControl(self):  # type: ()->Bool
        return Bool(self._node.at("hasDepthImpactOnControl"))
    @hasDepthImpactOnControl.setter
    def hasDepthImpactOnControl(self, val): self.hasDepthImpactOnControl.set(val)
    @property
    def isWaterfall(self):  # type: ()->Bool
        return Bool(self._node.at("isWaterfall"))
    @isWaterfall.setter
    def isWaterfall(self, val): self.isWaterfall.set(val)
    @property
    def level(self):  # type: ()->Float
        return Float(self._node.at("level"))
    @level.setter
    def level(self, val): self.level.set(val)
    @property
    def normal(self):  # type: ()->Vector3
        return Vector3(self._node.at("normal"))
    @normal.setter
    def normal(self, val): self.normal.set(val)
    @property
    def type(self):  # type: ()->FluidType
        return FluidType(self._node.at("type"))
    @type.setter
    def type(self, val): self.type.set(val)
    pass




