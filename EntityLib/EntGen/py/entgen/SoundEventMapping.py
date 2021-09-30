
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.String import *
from entgen.String import *
from entgen.String import *


class SoundEventMapping(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/SoundEventMapping"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(SoundEventMapping.schema_name))
    @property
    def Explicit(self): return (lambda n: Map(str, String, n))(self._node.at("Explicit"))
    @property
    def Ignored(self): return (lambda n: PrimitiveSet(str, n))(self._node.at("Ignored"))
    @property
    def Prefixed(self): return (lambda n: Map(str, String, n))(self._node.at("Prefixed"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




