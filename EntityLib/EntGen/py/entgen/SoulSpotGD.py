
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.String import *


class SoulSpotGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/SoulSpotGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(SoulSpotGD.schema_name))
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def Tags(self): return (lambda n: PrimArray(String, n))(self._node.at("Tags"))
    @Tags.setter
    def Tags(self, val): self.Tags.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




