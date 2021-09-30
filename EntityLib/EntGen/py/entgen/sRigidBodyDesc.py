
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Float import *
from entgen.Quat import *
from entgen.Vector3 import *
from entgen.String import *
from entgen.sPhysicShape import *


class sRigidBodyDesc(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sRigidBodyDesc"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(sRigidBodyDesc.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def angles(self): return Vector3(self._node.at("angles"))
    @angles.setter
    def angles(self, val): self.angles.set(val)
    @property
    def flags(self): return (lambda n: PrimArray(String, n))(self._node.at("flags"))
    @flags.setter
    def flags(self, val): self.flags.set(val)
    @property
    def id(self): return Int(self._node.at("id"))
    @id.setter
    def id(self, val): self.id.set(val)
    @property
    def motionType(self): return String(self._node.at("motionType"))
    @motionType.setter
    def motionType(self, val): self.motionType.set(val)
    @property
    def orientation(self): return Quat(self._node.at("orientation"))
    @orientation.setter
    def orientation(self, val): self.orientation.set(val)
    @property
    def parent(self): return String(self._node.at("parent"))
    @parent.setter
    def parent(self, val): self.parent.set(val)
    @property
    def scale(self): return Float(self._node.at("scale"))
    @scale.setter
    def scale(self, val): self.scale.set(val)
    @property
    def shapes(self): return (lambda n: Array(sPhysicShape, n))(self._node.at("shapes"))
    @property
    def translation(self): return Vector3(self._node.at("translation"))
    @translation.setter
    def translation(self, val): self.translation.set(val)
    pass




