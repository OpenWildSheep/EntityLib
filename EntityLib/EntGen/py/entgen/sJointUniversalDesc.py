
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Vector2 import *


class sJointUniversalDesc(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sJointUniversalDesc"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(sJointUniversalDesc.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def angleSwing1(self): return Vector2(self._node.at("angleSwing1"))
    @angleSwing1.setter
    def angleSwing1(self, val): self.angleSwing1.set(val)
    @property
    def angleSwing2(self): return Vector2(self._node.at("angleSwing2"))
    @angleSwing2.setter
    def angleSwing2(self, val): self.angleSwing2.set(val)
    pass




