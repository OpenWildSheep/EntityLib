
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Codec import *

from EntityLibPy import Node

class Zlib(HelperObject):
    schema_name = "Zlib"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Zlib
        return Zlib(entlib.load_node_file(sourcefile, entlib.get_schema(Zlib.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Zlib
        return Zlib(entlib.make_node(Zlib.schema_name))
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




