
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Bool import *
from entgen.GameInfoDB import *
from entgen.EntityStateSet import *
from entgen.EntityRef import *
from entgen.String import *

from EntityLibPy import Node

class PlayerState(HelperObject):
    schema_name = "PlayerState"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PlayerState
        return PlayerState(entlib.load_node_file(sourcefile, entlib.get_schema(PlayerState.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PlayerState
        return PlayerState(entlib.make_node(PlayerState.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ActiveScene(self):  # type: ()->String
        return String(self._node.at("ActiveScene"))
    @ActiveScene.setter
    def ActiveScene(self, val): self.ActiveScene.set(val)
    @property
    def DynamicStates(self):  # type: ()->Map[str, Map[str, EntityStateSet]]
        return (lambda n: Map(str, (lambda n: Map(str, EntityStateSet, n)), n))(self._node.at("DynamicStates"))
    @property
    def GameInfoDB(self):  # type: ()->GameInfoDB
        return GameInfoDB(self._node.at("GameInfoDB"))
    @property
    def MainScene(self):  # type: ()->String
        return String(self._node.at("MainScene"))
    @MainScene.setter
    def MainScene(self, val): self.MainScene.set(val)
    @property
    def Version(self):  # type: ()->Int
        return Int(self._node.at("Version"))
    @Version.setter
    def Version(self, val): self.Version.set(val)
    @property
    def WEDMode(self):  # type: ()->Bool
        return Bool(self._node.at("WEDMode"))
    @WEDMode.setter
    def WEDMode(self, val): self.WEDMode.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




