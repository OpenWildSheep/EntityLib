
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.FluidType import *
from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.Vector3 import *

from EntityLibPy import Node

class FluidGD(HelperObject):
    schema_name = "FluidGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FluidGD
        return FluidGD(entlib.load_node_file(sourcefile, entlib.get_schema(FluidGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FluidGD
        return FluidGD(entlib.make_node(FluidGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def IsWaterPlane(self):  # type: ()->Bool
        return Bool(self._node.at("IsWaterPlane"))
    @IsWaterPlane.setter
    def IsWaterPlane(self, val): self.IsWaterPlane.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def constrainedPlaneOffset(self):  # type: ()->Float
        return Float(self._node.at("constrainedPlaneOffset"))
    @constrainedPlaneOffset.setter
    def constrainedPlaneOffset(self, val): self.constrainedPlaneOffset.set(val)
    @property
    def fluidCurrent(self):  # type: ()->Vector3
        return Vector3(self._node.at("fluidCurrent"))
    @fluidCurrent.setter
    def fluidCurrent(self, val): self.fluidCurrent.set(val)
    @property
    def hasDepthLimit(self):  # type: ()->Bool
        return Bool(self._node.at("hasDepthLimit"))
    @hasDepthLimit.setter
    def hasDepthLimit(self, val): self.hasDepthLimit.set(val)
    @property
    def isWaterfall(self):  # type: ()->Bool
        return Bool(self._node.at("isWaterfall"))
    @isWaterfall.setter
    def isWaterfall(self, val): self.isWaterfall.set(val)
    @property
    def type(self):  # type: ()->FluidType
        return FluidType(self._node.at("type"))
    @type.setter
    def type(self, val): self.type.set(val)
    @property
    def useHalfShape(self):  # type: ()->Bool
        return Bool(self._node.at("useHalfShape"))
    @useHalfShape.setter
    def useHalfShape(self, val): self.useHalfShape.set(val)
    pass




