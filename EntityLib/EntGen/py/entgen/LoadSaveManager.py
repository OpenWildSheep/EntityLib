
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Manager import *

from EntityLibPy import Node

class LoadSaveManager(HelperObject):
    schema_name = "LoadSaveManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->LoadSaveManager
        return LoadSaveManager(entlib.load_node_file(sourcefile, entlib.get_schema(LoadSaveManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->LoadSaveManager
        return LoadSaveManager(entlib.make_node(LoadSaveManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ClothDataFile(self):  # type: ()->String
        return String(self._node.at("ClothDataFile"))
    @ClothDataFile.setter
    def ClothDataFile(self, val): self.ClothDataFile.set(val)
    @property
    def IconDataFile(self):  # type: ()->String
        return String(self._node.at("IconDataFile"))
    @IconDataFile.setter
    def IconDataFile(self, val): self.IconDataFile.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




