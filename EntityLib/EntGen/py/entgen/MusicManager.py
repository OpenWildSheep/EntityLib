
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.EventMusic import *
from entgen.Manager import *
from entgen.ShowdownMusic import *
from entgen.UIMusic import *
from entgen.String import *
from entgen.MusicCategory import *

from EntityLibPy import Node

class MusicManager(HelperObject):
    schema_name = "MusicManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MusicManager
        return MusicManager(entlib.load_node_file(sourcefile, entlib.get_schema(MusicManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MusicManager
        return MusicManager(entlib.make_node(MusicManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Categories(self):  # type: ()->Array[MusicCategory]
        return (lambda n: Array(MusicCategory, n))(self._node.at("Categories"))
    @property
    def EventMusicParam(self):  # type: ()->EventMusic
        return EventMusic(self._node.at("EventMusicParam"))
    @property
    def PlayerMusicTypes(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("PlayerMusicTypes"))
    @PlayerMusicTypes.setter
    def PlayerMusicTypes(self, val): self.PlayerMusicTypes.set(val)
    @property
    def RTPCMixWorldPrefix(self):  # type: ()->String
        return String(self._node.at("RTPCMixWorldPrefix"))
    @RTPCMixWorldPrefix.setter
    def RTPCMixWorldPrefix(self, val): self.RTPCMixWorldPrefix.set(val)
    @property
    def RelationsParamPath(self):  # type: ()->String
        return String(self._node.at("RelationsParamPath"))
    @RelationsParamPath.setter
    def RelationsParamPath(self, val): self.RelationsParamPath.set(val)
    @property
    def ShowdownMusicParam(self):  # type: ()->ShowdownMusic
        return ShowdownMusic(self._node.at("ShowdownMusicParam"))
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def UIMusicParam(self):  # type: ()->UIMusic
        return UIMusic(self._node.at("UIMusicParam"))
    @property
    def WorldMusicTypes(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("WorldMusicTypes"))
    @WorldMusicTypes.setter
    def WorldMusicTypes(self, val): self.WorldMusicTypes.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




