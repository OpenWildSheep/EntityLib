
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *


class ShootSequenceData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ShootSequenceData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(ShootSequenceData.schema_name))
    @property
    def Param(self): return Float(self._node.at("Param"))
    @Param.setter
    def Param(self, val): self.Param.set(val)
    @property
    def Type_(self): return String(self._node.at("Type_"))
    @Type_.setter
    def Type_(self, val): self.Type_.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




