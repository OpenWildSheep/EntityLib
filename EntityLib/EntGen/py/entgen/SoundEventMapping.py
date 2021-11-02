
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.String import *
from entgen.String import *
from entgen.String import *

from EntityLibPy import Node

class SoundEventMapping(HelperObject):
    schema_name = "SoundEventMapping"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SoundEventMapping
        return SoundEventMapping(entlib.load_node_file(sourcefile, entlib.get_schema(SoundEventMapping.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SoundEventMapping
        return SoundEventMapping(entlib.make_node(SoundEventMapping.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Explicit(self):  # type: ()->Map[str, String]
        return (lambda n: Map(str, String, n))(self._node.at("Explicit"))
    @property
    def Ignored(self):  # type: ()->PrimitiveSet[str]
        return (lambda n: PrimitiveSet(str, n))(self._node.at("Ignored"))
    @property
    def Prefixed(self):  # type: ()->Map[str, String]
        return (lambda n: Map(str, String, n))(self._node.at("Prefixed"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




