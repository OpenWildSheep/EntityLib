
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.Vector3 import *


class AnimationLegsConstraints_SlopeOffsetInfo(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimationLegsConstraints::SlopeOffsetInfo"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(AnimationLegsConstraints_SlopeOffsetInfo.schema_name))
    @property
    def MaxSlopeAngle(self): return Float(self._node.at("MaxSlopeAngle"))
    @MaxSlopeAngle.setter
    def MaxSlopeAngle(self, val): self.MaxSlopeAngle.set(val)
    @property
    def RotationOffset(self): return Vector3(self._node.at("RotationOffset"))
    @RotationOffset.setter
    def RotationOffset(self, val): self.RotationOffset.set(val)
    @property
    def TranslationOffset(self): return Vector3(self._node.at("TranslationOffset"))
    @TranslationOffset.setter
    def TranslationOffset(self, val): self.TranslationOffset.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




