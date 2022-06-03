
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.sGameEffectTemplate import *

from EntityLibPy import Node

class GameEffectSpawnerGD(HelperObject):
    schema_name = "GameEffectSpawnerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameEffectSpawnerGD
        return GameEffectSpawnerGD(entlib.load_node_file(sourcefile, entlib.get_schema(GameEffectSpawnerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameEffectSpawnerGD
        return GameEffectSpawnerGD(entlib.make_node(GameEffectSpawnerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def StartGameEffects(self):  # type: ()->Array[sGameEffectTemplate]
        return (lambda n: Array(sGameEffectTemplate, n))(self._node.at("StartGameEffects"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




