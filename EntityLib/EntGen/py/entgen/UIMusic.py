
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.SyncTempoMode import *
from entgen.String import *

from EntityLibPy import Node

class UIMusic(HelperObject):
    schema_name = "UIMusic"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->UIMusic
        return UIMusic(entlib.load_node_file(sourcefile, entlib.get_schema(UIMusic.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->UIMusic
        return UIMusic(entlib.make_node(UIMusic.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def MusicType(self):  # type: ()->String
        return String(self._node.at("MusicType"))
    @MusicType.setter
    def MusicType(self, val): self.MusicType.set(val)
    @property
    def SkillTree(self):  # type: ()->String
        return String(self._node.at("SkillTree"))
    @SkillTree.setter
    def SkillTree(self, val): self.SkillTree.set(val)
    @property
    def SynchronizationMode(self):  # type: ()->SyncTempoMode
        return SyncTempoMode(self._node.at("SynchronizationMode"))
    @SynchronizationMode.setter
    def SynchronizationMode(self, val): self.SynchronizationMode.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




