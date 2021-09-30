
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.ComponentGD import *
from entgen.Matrix33 import *
from entgen.DisplaceNoiseListItem import *


class HeightObj(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/HeightObj"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(HeightObj.schema_name))
    @property
    def DisplaceNoiseList(self): return (lambda n: Array(DisplaceNoiseListItem, n))(self._node.at("DisplaceNoiseList"))
    @property
    def EditorSubdivision(self): return Int(self._node.at("EditorSubdivision"))
    @EditorSubdivision.setter
    def EditorSubdivision(self, val): self.EditorSubdivision.set(val)
    @property
    def LocalMatrix(self): return Matrix33(self._node.at("LocalMatrix"))
    @LocalMatrix.setter
    def LocalMatrix(self, val): self.LocalMatrix.set(val)
    @property
    def MeshFile(self): return String(self._node.at("MeshFile"))
    @MeshFile.setter
    def MeshFile(self, val): self.MeshFile.set(val)
    @property
    def MeshName(self): return String(self._node.at("MeshName"))
    @MeshName.setter
    def MeshName(self, val): self.MeshName.set(val)
    @property
    def Priority(self): return Int(self._node.at("Priority"))
    @Priority.setter
    def Priority(self, val): self.Priority.set(val)
    @property
    def Subdivision(self): return Int(self._node.at("Subdivision"))
    @Subdivision.setter
    def Subdivision(self, val): self.Subdivision.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




