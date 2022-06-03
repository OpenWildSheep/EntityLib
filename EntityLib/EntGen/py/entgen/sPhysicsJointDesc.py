
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

from EntityLibPy import Node

class sPhysicsJointDesc(HelperObject):
    schema_name = "sPhysicsJointDesc"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sPhysicsJointDesc
        return sPhysicsJointDesc(entlib.load_node_file(sourcefile, entlib.get_schema(sPhysicsJointDesc.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sPhysicsJointDesc
        return sPhysicsJointDesc(entlib.make_node(sPhysicsJointDesc.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Ball(self):  # type: ()->sJointBallDesc
        return sJointBallDesc(self._node.at("Ball"))
    @property
    def Fixed(self):  # type: ()->sJointFixedDesc
        return sJointFixedDesc(self._node.at("Fixed"))
    @property
    def Hinge(self):  # type: ()->sJointHingeDesc
        return sJointHingeDesc(self._node.at("Hinge"))
    @property
    def JointType(self):  # type: ()->String
        return String(self._node.at("JointType"))
    @JointType.setter
    def JointType(self, val): self.JointType.set(val)
    @property
    def Slider(self):  # type: ()->sJointSliderDesc
        return sJointSliderDesc(self._node.at("Slider"))
    @property
    def SwingTwist(self):  # type: ()->sJointSwingTwistDesc
        return sJointSwingTwistDesc(self._node.at("SwingTwist"))
    @property
    def Universal(self):  # type: ()->sJointUniversalDesc
        return sJointUniversalDesc(self._node.at("Universal"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def flags(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("flags"))
    @flags.setter
    def flags(self, val): self.flags.set(val)
    @property
    def idRigodBodyA(self):  # type: ()->Int
        return Int(self._node.at("idRigodBodyA"))
    @idRigodBodyA.setter
    def idRigodBodyA(self, val): self.idRigodBodyA.set(val)
    @property
    def idRigodBodyB(self):  # type: ()->Int
        return Int(self._node.at("idRigodBodyB"))
    @idRigodBodyB.setter
    def idRigodBodyB(self, val): self.idRigodBodyB.set(val)
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
    def translation(self):  # type: ()->Vector3
        return Vector3(self._node.at("translation"))
    @translation.setter
    def translation(self, val): self.translation.set(val)
    pass




