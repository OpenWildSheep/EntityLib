
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.String import *

from EntityLibPy import Node

class SoulSpotGD(HelperObject):
    schema_name = "SoulSpotGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SoulSpotGD
        return SoulSpotGD(entlib.load_node_file(sourcefile, entlib.get_schema(SoulSpotGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SoulSpotGD
        return SoulSpotGD(entlib.make_node(SoulSpotGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def Tags(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("Tags"))
    @Tags.setter
    def Tags(self, val): self.Tags.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




