
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.FloatRange import *
from entgen.EntityLODData import *

from EntityLibPy import Node

class RegenData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/RegenData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RegenData
        return RegenData(entlib.load_node_file(sourcefile, entlib.get_schema(RegenData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RegenData
        return RegenData(entlib.make_node(RegenData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def LODData(self):  # type: ()->Array[EntityLODData]
        return (lambda n: Array(EntityLODData, n))(self._node.at("LODData"))
    @property
    def RegenRange(self):  # type: ()->FloatRange
        return FloatRange(self._node.at("RegenRange"))
    @property
    def RegenRangeHysteresis(self):  # type: ()->Float
        return Float(self._node.at("RegenRangeHysteresis"))
    @RegenRangeHysteresis.setter
    def RegenRangeHysteresis(self, val): self.RegenRangeHysteresis.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




