
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Codec import *

from EntityLibPy import Node

class Lz4Fast(HelperObject):
    schema_name = "Lz4Fast"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Lz4Fast
        return Lz4Fast(entlib.load_node_file(sourcefile, entlib.get_schema(Lz4Fast.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Lz4Fast
        return Lz4Fast(entlib.make_node(Lz4Fast.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->Codec
        return Codec(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




