
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Manager import *

from EntityLibPy import Node

class GameEffectManager(HelperObject):
    schema_name = "GameEffectManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameEffectManager
        return GameEffectManager(entlib.load_node_file(sourcefile, entlib.get_schema(GameEffectManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameEffectManager
        return GameEffectManager(entlib.make_node(GameEffectManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def GameEffectFileExtension(self):  # type: ()->String
        return String(self._node.at("GameEffectFileExtension"))
    @GameEffectFileExtension.setter
    def GameEffectFileExtension(self, val): self.GameEffectFileExtension.set(val)
    @property
    def GameEffectsRootPath(self):  # type: ()->String
        return String(self._node.at("GameEffectsRootPath"))
    @GameEffectsRootPath.setter
    def GameEffectsRootPath(self, val): self.GameEffectsRootPath.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




