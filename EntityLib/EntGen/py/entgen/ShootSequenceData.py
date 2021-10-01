
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class ShootSequenceData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ShootSequenceData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ShootSequenceData
        return ShootSequenceData(entlib.load_node_file(sourcefile, entlib.get_schema(ShootSequenceData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ShootSequenceData
        return ShootSequenceData(entlib.make_node(ShootSequenceData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Param(self):  # type: ()->Float
        return Float(self._node.at("Param"))
    @Param.setter
    def Param(self, val): self.Param.set(val)
    @property
    def Type_(self):  # type: ()->String
        return String(self._node.at("Type_"))
    @Type_.setter
    def Type_(self, val): self.Type_.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




