
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.Vector2 import *
from entgen.String import *

from EntityLibPy import Node

class HeightMapComponentGD(HelperObject):
    schema_name = "HeightMapComponentGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->HeightMapComponentGD
        return HeightMapComponentGD(entlib.load_node_file(sourcefile, entlib.get_schema(HeightMapComponentGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->HeightMapComponentGD
        return HeightMapComponentGD(entlib.make_node(HeightMapComponentGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def HeightMapArchivePath(self):  # type: ()->String
        return String(self._node.at("HeightMapArchivePath"))
    @HeightMapArchivePath.setter
    def HeightMapArchivePath(self, val): self.HeightMapArchivePath.set(val)
    @property
    def HeightMapPaths(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("HeightMapPaths"))
    @HeightMapPaths.setter
    def HeightMapPaths(self, val): self.HeightMapPaths.set(val)
    @property
    def HeightScale(self):  # type: ()->Float
        return Float(self._node.at("HeightScale"))
    @HeightScale.setter
    def HeightScale(self, val): self.HeightScale.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def SwapX(self):  # type: ()->Bool
        return Bool(self._node.at("SwapX"))
    @SwapX.setter
    def SwapX(self, val): self.SwapX.set(val)
    @property
    def SwapY(self):  # type: ()->Bool
        return Bool(self._node.at("SwapY"))
    @SwapY.setter
    def SwapY(self, val): self.SwapY.set(val)
    @property
    def WorldSize(self):  # type: ()->Vector2
        return Vector2(self._node.at("WorldSize"))
    @WorldSize.setter
    def WorldSize(self, val): self.WorldSize.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




