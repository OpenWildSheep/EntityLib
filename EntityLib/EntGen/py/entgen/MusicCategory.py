
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *

from EntityLibPy import Node

class MusicCategory(HelperObject):
    schema_name = "MusicCategory"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MusicCategory
        return MusicCategory(entlib.load_node_file(sourcefile, entlib.get_schema(MusicCategory.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MusicCategory
        return MusicCategory(entlib.make_node(MusicCategory.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EventName(self):  # type: ()->String
        return String(self._node.at("EventName"))
    @EventName.setter
    def EventName(self, val): self.EventName.set(val)
    @property
    def Name(self):  # type: ()->String
        return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def Weight(self):  # type: ()->Int
        return Int(self._node.at("Weight"))
    @Weight.setter
    def Weight(self, val): self.Weight.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




