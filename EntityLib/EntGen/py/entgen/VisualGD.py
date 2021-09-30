
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.EDITOR_LODsItem import *
from entgen.RUNTIME_LODsItem import *


class VisualGD(HelperObject):
    schema_name = "./MergedComponents.json#/definitions/VisualGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(VisualGD.schema_name))
    @property
    def AlwaysStatic(self): return Bool(self._node.at("AlwaysStatic"))
    @AlwaysStatic.setter
    def AlwaysStatic(self, val): self.AlwaysStatic.set(val)
    @property
    def EDITOR_GenerateFur(self): return Bool(self._node.at("EDITOR_GenerateFur"))
    @EDITOR_GenerateFur.setter
    def EDITOR_GenerateFur(self, val): self.EDITOR_GenerateFur.set(val)
    @property
    def EDITOR_LODs(self): return (lambda n: Array(EDITOR_LODsItem, n))(self._node.at("EDITOR_LODs"))
    @property
    def RUNTIME_LODScale(self): return Float(self._node.at("RUNTIME_LODScale"))
    @RUNTIME_LODScale.setter
    def RUNTIME_LODScale(self, val): self.RUNTIME_LODScale.set(val)
    @property
    def RUNTIME_LODs(self): return (lambda n: Array(RUNTIME_LODsItem, n))(self._node.at("RUNTIME_LODs"))
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def VisualResourcePath(self): return String(self._node.at("VisualResourcePath"))
    @VisualResourcePath.setter
    def VisualResourcePath(self, val): self.VisualResourcePath.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




