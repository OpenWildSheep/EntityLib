
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.ComponentGD import *
from entgen.Matrix33 import *

from EntityLibPy import Node

class BiomePatch(HelperObject):
    schema_name = "BiomePatch"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BiomePatch
        return BiomePatch(entlib.load_node_file(sourcefile, entlib.get_schema(BiomePatch.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BiomePatch
        return BiomePatch(entlib.make_node(BiomePatch.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def LocalMatrix(self):  # type: ()->Matrix33
        return Matrix33(self._node.at("LocalMatrix"))
    @LocalMatrix.setter
    def LocalMatrix(self, val): self.LocalMatrix.set(val)
    @property
    def MaterialGroupName(self):  # type: ()->String
        return String(self._node.at("MaterialGroupName"))
    @MaterialGroupName.setter
    def MaterialGroupName(self, val): self.MaterialGroupName.set(val)
    @property
    def MeshFile(self):  # type: ()->String
        return String(self._node.at("MeshFile"))
    @MeshFile.setter
    def MeshFile(self, val): self.MeshFile.set(val)
    @property
    def Priority(self):  # type: ()->Int
        return Int(self._node.at("Priority"))
    @Priority.setter
    def Priority(self, val): self.Priority.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




