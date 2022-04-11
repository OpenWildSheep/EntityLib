
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.HitStyle import *
from entgen.HitType import *
from entgen.Size import *
from entgen.String import *
from entgen.Int import *
from entgen.Bool import *
from entgen.Float import *
from entgen.Position import *
from entgen.Vector3 import *

from EntityLibPy import Node

class BaseParameters(HelperObject):
    schema_name = "BaseParameters"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BaseParameters
        return BaseParameters(entlib.load_node_file(sourcefile, entlib.get_schema(BaseParameters.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BaseParameters
        return BaseParameters(entlib.make_node(BaseParameters.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def additionalSpeedRequired(self):  # type: ()->Float
        return Float(self._node.at("additionalSpeedRequired"))
    @additionalSpeedRequired.setter
    def additionalSpeedRequired(self, val): self.additionalSpeedRequired.set(val)
    @property
    def direction(self):  # type: ()->Vector3
        return Vector3(self._node.at("direction"))
    @direction.setter
    def direction(self, val): self.direction.set(val)
    @property
    def flags(self):  # type: ()->Int
        return Int(self._node.at("flags"))
    @flags.setter
    def flags(self, val): self.flags.set(val)
    @property
    def force(self):  # type: ()->Float
        return Float(self._node.at("force"))
    @force.setter
    def force(self, val): self.force.set(val)
    @property
    def position(self):  # type: ()->Position
        return Position(self._node.at("position"))
    @property
    def shouldIgnoreSourceContactsDuringHit(self):  # type: ()->Bool
        return Bool(self._node.at("shouldIgnoreSourceContactsDuringHit"))
    @shouldIgnoreSourceContactsDuringHit.setter
    def shouldIgnoreSourceContactsDuringHit(self, val): self.shouldIgnoreSourceContactsDuringHit.set(val)
    @property
    def size(self):  # type: ()->Size
        return Size(self._node.at("size"))
    @size.setter
    def size(self, val): self.size.set(val)
    @property
    def style(self):  # type: ()->HitStyle
        return HitStyle(self._node.at("style"))
    @style.setter
    def style(self, val): self.style.set(val)
    @property
    def type(self):  # type: ()->HitType
        return HitType(self._node.at("type"))
    @type.setter
    def type(self, val): self.type.set(val)
    pass




