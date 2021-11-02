
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Quat import *
from entgen.Vector3 import *

from EntityLibPy import Node

class Transform3D(HelperObject):
    schema_name = "Transform3D"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Transform3D
        return Transform3D(entlib.load_node_file(sourcefile, entlib.get_schema(Transform3D.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Transform3D
        return Transform3D(entlib.make_node(Transform3D.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def orientation(self):  # type: ()->Quat
        return Quat(self._node.at("orientation"))
    @orientation.setter
    def orientation(self, val): self.orientation.set(val)
    @property
    def scale(self):  # type: ()->Vector3
        return Vector3(self._node.at("scale"))
    @scale.setter
    def scale(self, val): self.scale.set(val)
    @property
    def translation(self):  # type: ()->Vector3
        return Vector3(self._node.at("translation"))
    @translation.setter
    def translation(self, val): self.translation.set(val)
    pass




