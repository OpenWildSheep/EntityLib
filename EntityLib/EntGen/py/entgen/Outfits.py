
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *

from EntityLibPy import Node

class Outfits(HelperObject):
    schema_name = "Outfits"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Outfits
        return Outfits(entlib.load_node_file(sourcefile, entlib.get_schema(Outfits.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Outfits
        return Outfits(entlib.make_node(Outfits.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Flying(self):  # type: ()->String
        return String(self._node.at("Flying"))
    @Flying.setter
    def Flying(self, val): self.Flying.set(val)
    @property
    def Normal(self):  # type: ()->String
        return String(self._node.at("Normal"))
    @Normal.setter
    def Normal(self, val): self.Normal.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




