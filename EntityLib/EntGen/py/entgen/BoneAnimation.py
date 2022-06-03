
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Vector3 import *
from entgen.Vector4 import *

from EntityLibPy import Node

class BoneAnimation(HelperObject):
    schema_name = "BoneAnimation"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BoneAnimation
        return BoneAnimation(entlib.load_node_file(sourcefile, entlib.get_schema(BoneAnimation.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BoneAnimation
        return BoneAnimation(entlib.make_node(BoneAnimation.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Name(self):  # type: ()->String
        return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def Rotations(self):  # type: ()->Array[Vector4]
        return (lambda n: Array(Vector4, n))(self._node.at("Rotations"))
    @property
    def Scales(self):  # type: ()->Array[Vector3]
        return (lambda n: Array(Vector3, n))(self._node.at("Scales"))
    @property
    def Translations(self):  # type: ()->Array[Vector4]
        return (lambda n: Array(Vector4, n))(self._node.at("Translations"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




