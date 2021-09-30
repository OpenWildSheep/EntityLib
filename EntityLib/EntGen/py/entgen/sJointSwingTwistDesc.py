
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Vector2 import *


class sJointSwingTwistDesc(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sJointSwingTwistDesc"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(sJointSwingTwistDesc.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def swingAngle(self): return Vector2(self._node.at("swingAngle"))
    @swingAngle.setter
    def swingAngle(self, val): self.swingAngle.set(val)
    @property
    def twistAngle(self): return Vector2(self._node.at("twistAngle"))
    @twistAngle.setter
    def twistAngle(self, val): self.twistAngle.set(val)
    pass




