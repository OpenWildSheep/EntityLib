
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class CharacterControllerFallData(HelperObject):
    schema_name = "CharacterControllerFallData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CharacterControllerFallData
        return CharacterControllerFallData(entlib.load_node_file(sourcefile, entlib.get_schema(CharacterControllerFallData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CharacterControllerFallData
        return CharacterControllerFallData(entlib.make_node(CharacterControllerFallData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DamagesPerHeightFall(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("DamagesPerHeightFall"))
    @property
    def MinHeightForDamageFall(self):  # type: ()->Float
        return Float(self._node.at("MinHeightForDamageFall"))
    @MinHeightForDamageFall.setter
    def MinHeightForDamageFall(self, val): self.MinHeightForDamageFall.set(val)
    @property
    def MinHeightForDeathFall(self):  # type: ()->Float
        return Float(self._node.at("MinHeightForDeathFall"))
    @MinHeightForDeathFall.setter
    def MinHeightForDeathFall(self, val): self.MinHeightForDeathFall.set(val)
    @property
    def MinHeightForRecoveryFall(self):  # type: ()->Float
        return Float(self._node.at("MinHeightForRecoveryFall"))
    @MinHeightForRecoveryFall.setter
    def MinHeightForRecoveryFall(self, val): self.MinHeightForRecoveryFall.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




