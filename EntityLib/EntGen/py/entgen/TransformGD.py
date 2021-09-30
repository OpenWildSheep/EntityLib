
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Matrix33 import *
from entgen.Quat import *
from entgen.Vector3 import *


class TransformGD(HelperObject):
    schema_name = "./MergedComponents.json#/definitions/TransformGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(TransformGD.schema_name))
    @property
    def EDITOR_InheritScaleFromSubSceneHolder(self): return Bool(self._node.at("EDITOR_InheritScaleFromSubSceneHolder"))
    @EDITOR_InheritScaleFromSubSceneHolder.setter
    def EDITOR_InheritScaleFromSubSceneHolder(self, val): self.EDITOR_InheritScaleFromSubSceneHolder.set(val)
    @property
    def EDITOR_PropagateScaleToSubScene(self): return Bool(self._node.at("EDITOR_PropagateScaleToSubScene"))
    @EDITOR_PropagateScaleToSubScene.setter
    def EDITOR_PropagateScaleToSubScene(self, val): self.EDITOR_PropagateScaleToSubScene.set(val)
    @property
    def Matrix(self): return Matrix33(self._node.at("Matrix"))
    @Matrix.setter
    def Matrix(self, val): self.Matrix.set(val)
    @property
    def Orientation(self): return Quat(self._node.at("Orientation"))
    @Orientation.setter
    def Orientation(self, val): self.Orientation.set(val)
    @property
    def Position(self): return Vector3(self._node.at("Position"))
    @Position.setter
    def Position(self, val): self.Position.set(val)
    @property
    def Scale(self): return Vector3(self._node.at("Scale"))
    @Scale.setter
    def Scale(self, val): self.Scale.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




