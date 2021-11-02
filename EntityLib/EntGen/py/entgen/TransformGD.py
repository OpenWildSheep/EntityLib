
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Matrix33 import *
from entgen.Quat import *
from entgen.Vector3 import *

from EntityLibPy import Node

class TransformGD(HelperObject):
    schema_name = "TransformGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TransformGD
        return TransformGD(entlib.load_node_file(sourcefile, entlib.get_schema(TransformGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TransformGD
        return TransformGD(entlib.make_node(TransformGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EDITOR_InheritScaleFromSubSceneHolder(self):  # type: ()->Bool
        return Bool(self._node.at("EDITOR_InheritScaleFromSubSceneHolder"))
    @EDITOR_InheritScaleFromSubSceneHolder.setter
    def EDITOR_InheritScaleFromSubSceneHolder(self, val): self.EDITOR_InheritScaleFromSubSceneHolder.set(val)
    @property
    def EDITOR_PropagateScaleToSubScene(self):  # type: ()->Bool
        return Bool(self._node.at("EDITOR_PropagateScaleToSubScene"))
    @EDITOR_PropagateScaleToSubScene.setter
    def EDITOR_PropagateScaleToSubScene(self, val): self.EDITOR_PropagateScaleToSubScene.set(val)
    @property
    def Matrix(self):  # type: ()->Matrix33
        return Matrix33(self._node.at("Matrix"))
    @Matrix.setter
    def Matrix(self, val): self.Matrix.set(val)
    @property
    def Orientation(self):  # type: ()->Quat
        return Quat(self._node.at("Orientation"))
    @Orientation.setter
    def Orientation(self, val): self.Orientation.set(val)
    @property
    def Position(self):  # type: ()->Vector3
        return Vector3(self._node.at("Position"))
    @Position.setter
    def Position(self, val): self.Position.set(val)
    @property
    def Scale(self):  # type: ()->Vector3
        return Vector3(self._node.at("Scale"))
    @Scale.setter
    def Scale(self, val): self.Scale.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




