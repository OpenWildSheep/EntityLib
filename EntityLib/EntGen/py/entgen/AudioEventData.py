
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Float import *

from EntityLibPy import Node

class AudioEventData(HelperObject):
    schema_name = "AudioEventData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AudioEventData
        return AudioEventData(entlib.load_node_file(sourcefile, entlib.get_schema(AudioEventData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AudioEventData
        return AudioEventData(entlib.make_node(AudioEventData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ID(self):  # type: ()->Int
        return Int(self._node.at("ID"))
    @ID.setter
    def ID(self, val): self.ID.set(val)
    @property
    def Name(self):  # type: ()->String
        return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def Range(self):  # type: ()->Float
        return Float(self._node.at("Range"))
    @Range.setter
    def Range(self, val): self.Range.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




