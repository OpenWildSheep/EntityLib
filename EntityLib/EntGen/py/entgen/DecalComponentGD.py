
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class DecalComponentGD(HelperObject):
    schema_name = "DecalComponentGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->DecalComponentGD
        return DecalComponentGD(entlib.load_node_file(sourcefile, entlib.get_schema(DecalComponentGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->DecalComponentGD
        return DecalComponentGD(entlib.make_node(DecalComponentGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Material(self):  # type: ()->String
        return String(self._node.at("Material"))
    @Material.setter
    def Material(self, val): self.Material.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




