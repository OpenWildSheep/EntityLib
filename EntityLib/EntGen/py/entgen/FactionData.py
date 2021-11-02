
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *

from EntityLibPy import Node

class FactionData(HelperObject):
    schema_name = "FactionData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FactionData
        return FactionData(entlib.load_node_file(sourcefile, entlib.get_schema(FactionData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FactionData
        return FactionData(entlib.make_node(FactionData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def name(self):  # type: ()->String
        return String(self._node.at("name"))
    @name.setter
    def name(self, val): self.name.set(val)
    pass




