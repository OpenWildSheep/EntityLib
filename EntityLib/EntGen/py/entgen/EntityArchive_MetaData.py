
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *

from EntityLibPy import Node

class EntityArchive_MetaData(HelperObject):
    schema_name = "EntityArchive::MetaData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityArchive_MetaData
        return EntityArchive_MetaData(entlib.load_node_file(sourcefile, entlib.get_schema(EntityArchive_MetaData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityArchive_MetaData
        return EntityArchive_MetaData(entlib.make_node(EntityArchive_MetaData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Name(self):  # type: ()->String
        return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def RawDataPath(self):  # type: ()->String
        return String(self._node.at("RawDataPath"))
    @RawDataPath.setter
    def RawDataPath(self, val): self.RawDataPath.set(val)
    @property
    def Version(self):  # type: ()->Int
        return Int(self._node.at("Version"))
    @Version.setter
    def Version(self, val): self.Version.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




