
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.Manager import *
from entgen.UIMessage import *
from entgen.UIMessage import *

from EntityLibPy import Node

class UIManager(HelperObject):
    schema_name = "UIManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->UIManager
        return UIManager(entlib.load_node_file(sourcefile, entlib.get_schema(UIManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->UIManager
        return UIManager(entlib.make_node(UIManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BarAlpha(self):  # type: ()->Float
        return Float(self._node.at("BarAlpha"))
    @BarAlpha.setter
    def BarAlpha(self, val): self.BarAlpha.set(val)
    @property
    def BarHeight(self):  # type: ()->Float
        return Float(self._node.at("BarHeight"))
    @BarHeight.setter
    def BarHeight(self, val): self.BarHeight.set(val)
    @property
    def BarWidth(self):  # type: ()->Float
        return Float(self._node.at("BarWidth"))
    @BarWidth.setter
    def BarWidth(self, val): self.BarWidth.set(val)
    @property
    def BlankMaterialPath(self):  # type: ()->String
        return String(self._node.at("BlankMaterialPath"))
    @BlankMaterialPath.setter
    def BlankMaterialPath(self, val): self.BlankMaterialPath.set(val)
    @property
    def EnableReticle(self):  # type: ()->Bool
        return Bool(self._node.at("EnableReticle"))
    @EnableReticle.setter
    def EnableReticle(self, val): self.EnableReticle.set(val)
    @property
    def EnableReticleLock(self):  # type: ()->Bool
        return Bool(self._node.at("EnableReticleLock"))
    @EnableReticleLock.setter
    def EnableReticleLock(self, val): self.EnableReticleLock.set(val)
    @property
    def Font(self):  # type: ()->String
        return String(self._node.at("Font"))
    @Font.setter
    def Font(self, val): self.Font.set(val)
    @property
    def HaloBigGRC(self):  # type: ()->String
        return String(self._node.at("HaloBigGRC"))
    @HaloBigGRC.setter
    def HaloBigGRC(self, val): self.HaloBigGRC.set(val)
    @property
    def HaloSmallGRC(self):  # type: ()->String
        return String(self._node.at("HaloSmallGRC"))
    @HaloSmallGRC.setter
    def HaloSmallGRC(self, val): self.HaloSmallGRC.set(val)
    @property
    def LaunchedMessages(self):  # type: ()->Array[UIMessage]
        return (lambda n: Array(UIMessage, n))(self._node.at("LaunchedMessages"))
    @property
    def LaunchedSceneMessage(self):  # type: ()->UIMessage
        return UIMessage(self._node.at("LaunchedSceneMessage"))
    @property
    def ShowFoodBar(self):  # type: ()->Bool
        return Bool(self._node.at("ShowFoodBar"))
    @ShowFoodBar.setter
    def ShowFoodBar(self, val): self.ShowFoodBar.set(val)
    @property
    def ShowLifeBar(self):  # type: ()->Bool
        return Bool(self._node.at("ShowLifeBar"))
    @ShowLifeBar.setter
    def ShowLifeBar(self, val): self.ShowLifeBar.set(val)
    @property
    def ShowOxygenBar(self):  # type: ()->Bool
        return Bool(self._node.at("ShowOxygenBar"))
    @ShowOxygenBar.setter
    def ShowOxygenBar(self, val): self.ShowOxygenBar.set(val)
    @property
    def ShowTempBar(self):  # type: ()->Bool
        return Bool(self._node.at("ShowTempBar"))
    @ShowTempBar.setter
    def ShowTempBar(self, val): self.ShowTempBar.set(val)
    @property
    def ShowThirstBar(self):  # type: ()->Bool
        return Bool(self._node.at("ShowThirstBar"))
    @ShowThirstBar.setter
    def ShowThirstBar(self, val): self.ShowThirstBar.set(val)
    @property
    def ShowTiredBar(self):  # type: ()->Bool
        return Bool(self._node.at("ShowTiredBar"))
    @ShowTiredBar.setter
    def ShowTiredBar(self, val): self.ShowTiredBar.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




