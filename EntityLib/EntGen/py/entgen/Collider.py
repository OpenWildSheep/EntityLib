
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class Collider(HelperObject):
    schema_name = "Collider"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Collider
        return Collider(entlib.load_node_file(sourcefile, entlib.get_schema(Collider.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Collider
        return Collider(entlib.make_node(Collider.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BoneName(self):  # type: ()->String
        return String(self._node.at("BoneName"))
    @BoneName.setter
    def BoneName(self, val): self.BoneName.set(val)
    @property
    def RadiusFactor(self):  # type: ()->Float
        return Float(self._node.at("RadiusFactor"))
    @RadiusFactor.setter
    def RadiusFactor(self, val): self.RadiusFactor.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




