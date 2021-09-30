
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *


class Collider(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/Collider"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(Collider.schema_name))
    @property
    def BoneName(self): return String(self._node.at("BoneName"))
    @BoneName.setter
    def BoneName(self, val): self.BoneName.set(val)
    @property
    def RadiusFactor(self): return Float(self._node.at("RadiusFactor"))
    @RadiusFactor.setter
    def RadiusFactor(self, val): self.RadiusFactor.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




