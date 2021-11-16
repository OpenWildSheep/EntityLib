
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

from EntityLibPy import Node

class sRigidBodyDesc(HelperObject):
    schema_name = "sRigidBodyDesc"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sRigidBodyDesc
        return sRigidBodyDesc(entlib.load_node_file(sourcefile, entlib.get_schema(sRigidBodyDesc.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sRigidBodyDesc
        return sRigidBodyDesc(entlib.make_node(sRigidBodyDesc.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def angles(self):  # type: ()->Vector3
        return Vector3(self._node.at("angles"))
    @angles.setter
    def angles(self, val): self.angles.set(val)
    @property
    def flags(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("flags"))
    @flags.setter
    def flags(self, val): self.flags.set(val)
    @property
    def id(self):  # type: ()->Int
        return Int(self._node.at("id"))
    @id.setter
    def id(self, val): self.id.set(val)
    @property
    def motionType(self):  # type: ()->String
        return String(self._node.at("motionType"))
    @motionType.setter
    def motionType(self, val): self.motionType.set(val)
    @property
    def orientation(self):  # type: ()->Quat
        return Quat(self._node.at("orientation"))
    @orientation.setter
    def orientation(self, val): self.orientation.set(val)
    @property
    def parent(self):  # type: ()->String
        return String(self._node.at("parent"))
    @parent.setter
    def parent(self, val): self.parent.set(val)
    @property
    def scale(self):  # type: ()->Float
        return Float(self._node.at("scale"))
    @scale.setter
    def scale(self, val): self.scale.set(val)
    @property
    def shapes(self):  # type: ()->Array[sPhysicShape]
        return (lambda n: Array(sPhysicShape, n))(self._node.at("shapes"))
    @property
    def translation(self):  # type: ()->Vector3
        return Vector3(self._node.at("translation"))
    @translation.setter
    def translation(self, val): self.translation.set(val)
    pass




