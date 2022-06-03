
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Float import *
from entgen.Vector3 import *
from entgen.Float import *

from EntityLibPy import Node

class HeightGrid(HelperObject):
    schema_name = "HeightGrid"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->HeightGrid
        return HeightGrid(entlib.load_node_file(sourcefile, entlib.get_schema(HeightGrid.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->HeightGrid
        return HeightGrid(entlib.make_node(HeightGrid.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CenterToCorner(self):  # type: ()->Vector3
        return Vector3(self._node.at("CenterToCorner"))
    @CenterToCorner.setter
    def CenterToCorner(self, val): self.CenterToCorner.set(val)
    @property
    def GridCellSize(self):  # type: ()->Float
        return Float(self._node.at("GridCellSize"))
    @GridCellSize.setter
    def GridCellSize(self, val): self.GridCellSize.set(val)
    @property
    def GridHeight(self):  # type: ()->Int
        return Int(self._node.at("GridHeight"))
    @GridHeight.setter
    def GridHeight(self, val): self.GridHeight.set(val)
    @property
    def GridWidth(self):  # type: ()->Int
        return Int(self._node.at("GridWidth"))
    @GridWidth.setter
    def GridWidth(self, val): self.GridWidth.set(val)
    @property
    def Heights(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("Heights"))
    @Heights.setter
    def Heights(self, val): self.Heights.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




