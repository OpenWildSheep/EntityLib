
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.ActionMode import *
from entgen.String import *
from entgen.Float import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class ChargedJumpAnimation(HelperObject):
    schema_name = "ChargedJumpAnimation"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ChargedJumpAnimation
        return ChargedJumpAnimation(entlib.load_node_file(sourcefile, entlib.get_schema(ChargedJumpAnimation.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ChargedJumpAnimation
        return ChargedJumpAnimation(entlib.make_node(ChargedJumpAnimation.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def animActionMode(self):  # type: ()->ActionMode
        return ActionMode(self._node.at("animActionMode"))
    @animActionMode.setter
    def animActionMode(self, val): self.animActionMode.set(val)
    @property
    def lerpFactorScaleXY(self):  # type: ()->Float
        return Float(self._node.at("lerpFactorScaleXY"))
    @lerpFactorScaleXY.setter
    def lerpFactorScaleXY(self, val): self.lerpFactorScaleXY.set(val)
    @property
    def lerpFactorScaleZ(self):  # type: ()->Float
        return Float(self._node.at("lerpFactorScaleZ"))
    @lerpFactorScaleZ.setter
    def lerpFactorScaleZ(self, val): self.lerpFactorScaleZ.set(val)
    @property
    def scaleByPower(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("scaleByPower"))
    pass




