
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Vector3 import *
from entgen.sGameEffectTemplate import *


class GameEffectSpawnerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/GameEffectSpawnerGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(GameEffectSpawnerGD.schema_name))
    @property
    def GameEffectOffset(self): return Vector3(self._node.at("GameEffectOffset"))
    @GameEffectOffset.setter
    def GameEffectOffset(self, val): self.GameEffectOffset.set(val)
    @property
    def StartGameEffects(self): return (lambda n: Array(sGameEffectTemplate, n))(self._node.at("StartGameEffects"))
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




