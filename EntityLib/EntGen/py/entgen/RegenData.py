
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.FloatRange import *
from entgen.EntityLODData import *


class RegenData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/RegenData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(RegenData.schema_name))
    @property
    def LODData(self): return (lambda n: Array(EntityLODData, n))(self._node.at("LODData"))
    @property
    def RegenRange(self): return FloatRange(self._node.at("RegenRange"))
    @property
    def RegenRangeHysteresis(self): return Float(self._node.at("RegenRangeHysteresis"))
    @RegenRangeHysteresis.setter
    def RegenRangeHysteresis(self, val): self.RegenRangeHysteresis.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




