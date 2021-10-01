
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.Vector3 import *

from EntityLibPy import Node

class AnimationLegsConstraints_SlopeOffsetInfo(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimationLegsConstraints::SlopeOffsetInfo"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationLegsConstraints_SlopeOffsetInfo
        return AnimationLegsConstraints_SlopeOffsetInfo(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationLegsConstraints_SlopeOffsetInfo.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationLegsConstraints_SlopeOffsetInfo
        return AnimationLegsConstraints_SlopeOffsetInfo(entlib.make_node(AnimationLegsConstraints_SlopeOffsetInfo.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def MaxSlopeAngle(self):  # type: ()->Float
        return Float(self._node.at("MaxSlopeAngle"))
    @MaxSlopeAngle.setter
    def MaxSlopeAngle(self, val): self.MaxSlopeAngle.set(val)
    @property
    def RotationOffset(self):  # type: ()->Vector3
        return Vector3(self._node.at("RotationOffset"))
    @RotationOffset.setter
    def RotationOffset(self, val): self.RotationOffset.set(val)
    @property
    def TranslationOffset(self):  # type: ()->Vector3
        return Vector3(self._node.at("TranslationOffset"))
    @TranslationOffset.setter
    def TranslationOffset(self, val): self.TranslationOffset.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




