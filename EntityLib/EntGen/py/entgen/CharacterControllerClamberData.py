
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class CharacterControllerClamberData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CharacterControllerClamberData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CharacterControllerClamberData
        return CharacterControllerClamberData(entlib.load_node_file(sourcefile, entlib.get_schema(CharacterControllerClamberData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CharacterControllerClamberData
        return CharacterControllerClamberData(entlib.make_node(CharacterControllerClamberData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DropOffAngle(self):  # type: ()->Float
        return Float(self._node.at("DropOffAngle"))
    @DropOffAngle.setter
    def DropOffAngle(self, val): self.DropOffAngle.set(val)
    @property
    def EnterAngle(self):  # type: ()->Float
        return Float(self._node.at("EnterAngle"))
    @EnterAngle.setter
    def EnterAngle(self, val): self.EnterAngle.set(val)
    @property
    def ExitAngle(self):  # type: ()->Float
        return Float(self._node.at("ExitAngle"))
    @ExitAngle.setter
    def ExitAngle(self, val): self.ExitAngle.set(val)
    @property
    def IsAllowed(self):  # type: ()->Bool
        return Bool(self._node.at("IsAllowed"))
    @IsAllowed.setter
    def IsAllowed(self, val): self.IsAllowed.set(val)
    @property
    def VerticalOrientationRatio(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("VerticalOrientationRatio"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




