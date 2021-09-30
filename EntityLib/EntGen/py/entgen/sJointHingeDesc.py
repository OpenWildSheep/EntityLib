
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Vector2 import *
from entgen.Vector3 import *


class sJointHingeDesc(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sJointHingeDesc"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(sJointHingeDesc.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def angle(self): return Vector2(self._node.at("angle"))
    @angle.setter
    def angle(self, val): self.angle.set(val)
    @property
    def axis(self): return Vector3(self._node.at("axis"))
    @axis.setter
    def axis(self, val): self.axis.set(val)
    pass




