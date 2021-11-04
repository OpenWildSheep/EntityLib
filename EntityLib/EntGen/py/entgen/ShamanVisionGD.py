
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class ShamanVisionGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ShamanVisionGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ShamanVisionGD
        return ShamanVisionGD(entlib.load_node_file(sourcefile, entlib.get_schema(ShamanVisionGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ShamanVisionGD
        return ShamanVisionGD(entlib.make_node(ShamanVisionGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




