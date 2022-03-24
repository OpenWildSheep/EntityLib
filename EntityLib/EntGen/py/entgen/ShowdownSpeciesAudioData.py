
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *

from EntityLibPy import Node

class ShowdownSpeciesAudioData(HelperObject):
    schema_name = "ShowdownSpeciesAudioData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ShowdownSpeciesAudioData
        return ShowdownSpeciesAudioData(entlib.load_node_file(sourcefile, entlib.get_schema(ShowdownSpeciesAudioData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ShowdownSpeciesAudioData
        return ShowdownSpeciesAudioData(entlib.make_node(ShowdownSpeciesAudioData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AudioCategory(self):  # type: ()->String
        return String(self._node.at("AudioCategory"))
    @AudioCategory.setter
    def AudioCategory(self, val): self.AudioCategory.set(val)
    @property
    def Species(self):  # type: ()->String
        return String(self._node.at("Species"))
    @Species.setter
    def Species(self, val): self.Species.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




