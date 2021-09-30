
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.ScaleConverter import *


class CharacterControllerClamberData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CharacterControllerClamberData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(CharacterControllerClamberData.schema_name))
    @property
    def DropOffAngle(self): return Float(self._node.at("DropOffAngle"))
    @DropOffAngle.setter
    def DropOffAngle(self, val): self.DropOffAngle.set(val)
    @property
    def EnterAngle(self): return Float(self._node.at("EnterAngle"))
    @EnterAngle.setter
    def EnterAngle(self, val): self.EnterAngle.set(val)
    @property
    def ExitAngle(self): return Float(self._node.at("ExitAngle"))
    @ExitAngle.setter
    def ExitAngle(self, val): self.ExitAngle.set(val)
    @property
    def IsAllowed(self): return Bool(self._node.at("IsAllowed"))
    @IsAllowed.setter
    def IsAllowed(self, val): self.IsAllowed.set(val)
    @property
    def VerticalOrientationRatio(self): return ScaleConverter(self._node.at("VerticalOrientationRatio"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




