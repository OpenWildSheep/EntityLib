
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Float import *
from entgen.Vector3 import *

from EntityLibPy import Node

class MountableSnapLine_ControlPoint(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/MountableSnapLine::ControlPoint"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MountableSnapLine_ControlPoint
        return MountableSnapLine_ControlPoint(entlib.load_node_file(sourcefile, entlib.get_schema(MountableSnapLine_ControlPoint.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MountableSnapLine_ControlPoint
        return MountableSnapLine_ControlPoint(entlib.make_node(MountableSnapLine_ControlPoint.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def boneId(self):  # type: ()->Int
        return Int(self._node.at("boneId"))
    @boneId.setter
    def boneId(self, val): self.boneId.set(val)
    @property
    def offset(self):  # type: ()->Vector3
        return Vector3(self._node.at("offset"))
    @offset.setter
    def offset(self, val): self.offset.set(val)
    @property
    def radius(self):  # type: ()->Float
        return Float(self._node.at("radius"))
    @radius.setter
    def radius(self, val): self.radius.set(val)
    pass




