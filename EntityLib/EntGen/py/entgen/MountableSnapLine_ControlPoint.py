
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Float import *
from entgen.Vector3 import *


class MountableSnapLine_ControlPoint(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/MountableSnapLine::ControlPoint"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(MountableSnapLine_ControlPoint.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def boneId(self): return Int(self._node.at("boneId"))
    @boneId.setter
    def boneId(self, val): self.boneId.set(val)
    @property
    def offset(self): return Vector3(self._node.at("offset"))
    @offset.setter
    def offset(self, val): self.offset.set(val)
    @property
    def radius(self): return Float(self._node.at("radius"))
    @radius.setter
    def radius(self, val): self.radius.set(val)
    pass




