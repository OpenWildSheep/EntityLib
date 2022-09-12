
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class AnticipationJump(HelperObject):
    schema_name = "AnticipationJump"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnticipationJump
        return AnticipationJump(entlib.load_node_file(sourcefile, entlib.get_schema(AnticipationJump.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnticipationJump
        return AnticipationJump(entlib.make_node(AnticipationJump.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AnticipationJumpMaxPitch(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("AnticipationJumpMaxPitch"))
    @property
    def AnticipationJumpMinPitch(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("AnticipationJumpMinPitch"))
    @property
    def AnticipationJumpSpeedPitchSmoothCoeff(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("AnticipationJumpSpeedPitchSmoothCoeff"))
    @property
    def AnticipationJumpTime(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("AnticipationJumpTime"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




