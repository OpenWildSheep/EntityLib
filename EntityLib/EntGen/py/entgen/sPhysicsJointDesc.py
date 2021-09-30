
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Quat import *
from entgen.Vector3 import *
from entgen.sJointBallDesc import *
from entgen.sJointFixedDesc import *
from entgen.sJointHingeDesc import *
from entgen.sJointSliderDesc import *
from entgen.sJointSwingTwistDesc import *
from entgen.sJointUniversalDesc import *
from entgen.String import *


class sPhysicsJointDesc(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sPhysicsJointDesc"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(sPhysicsJointDesc.schema_name))
    @property
    def Ball(self): return sJointBallDesc(self._node.at("Ball"))
    @property
    def Fixed(self): return sJointFixedDesc(self._node.at("Fixed"))
    @property
    def Hinge(self): return sJointHingeDesc(self._node.at("Hinge"))
    @property
    def JointType(self): return String(self._node.at("JointType"))
    @JointType.setter
    def JointType(self, val): self.JointType.set(val)
    @property
    def Slider(self): return sJointSliderDesc(self._node.at("Slider"))
    @property
    def SwingTwist(self): return sJointSwingTwistDesc(self._node.at("SwingTwist"))
    @property
    def Universal(self): return sJointUniversalDesc(self._node.at("Universal"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def flags(self): return (lambda n: PrimArray(String, n))(self._node.at("flags"))
    @flags.setter
    def flags(self, val): self.flags.set(val)
    @property
    def idRigodBodyA(self): return Int(self._node.at("idRigodBodyA"))
    @idRigodBodyA.setter
    def idRigodBodyA(self, val): self.idRigodBodyA.set(val)
    @property
    def idRigodBodyB(self): return Int(self._node.at("idRigodBodyB"))
    @idRigodBodyB.setter
    def idRigodBodyB(self, val): self.idRigodBodyB.set(val)
    @property
    def orientation(self): return Quat(self._node.at("orientation"))
    @orientation.setter
    def orientation(self, val): self.orientation.set(val)
    @property
    def parent(self): return String(self._node.at("parent"))
    @parent.setter
    def parent(self, val): self.parent.set(val)
    @property
    def translation(self): return Vector3(self._node.at("translation"))
    @translation.setter
    def translation(self, val): self.translation.set(val)
    pass




