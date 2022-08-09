
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Float import *

from EntityLibPy import Node

class MinModifParams(HelperObject):
    schema_name = "MinModifParams"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MinModifParams
        return MinModifParams(entlib.load_node_file(sourcefile, entlib.get_schema(MinModifParams.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MinModifParams
        return MinModifParams(entlib.make_node(MinModifParams.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BorderSize(self):  # type: ()->Int
        return Int(self._node.at("BorderSize"))
    @BorderSize.setter
    def BorderSize(self, val): self.BorderSize.set(val)
    @property
    def CellSize(self):  # type: ()->Float
        return Float(self._node.at("CellSize"))
    @CellSize.setter
    def CellSize(self, val): self.CellSize.set(val)
    @property
    def MergeRegionArea(self):  # type: ()->Int
        return Int(self._node.at("MergeRegionArea"))
    @MergeRegionArea.setter
    def MergeRegionArea(self, val): self.MergeRegionArea.set(val)
    @property
    def MinRegionArea(self):  # type: ()->Int
        return Int(self._node.at("MinRegionArea"))
    @MinRegionArea.setter
    def MinRegionArea(self, val): self.MinRegionArea.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




