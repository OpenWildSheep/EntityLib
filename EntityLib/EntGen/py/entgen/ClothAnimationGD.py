
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.Vector3 import *

from EntityLibPy import Node

class ClothAnimationGD(HelperObject):
    schema_name = "ClothAnimationGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ClothAnimationGD
        return ClothAnimationGD(entlib.load_node_file(sourcefile, entlib.get_schema(ClothAnimationGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ClothAnimationGD
        return ClothAnimationGD(entlib.make_node(ClothAnimationGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ClothSkeletonPath(self):  # type: ()->String
        return String(self._node.at("ClothSkeletonPath"))
    @ClothSkeletonPath.setter
    def ClothSkeletonPath(self, val): self.ClothSkeletonPath.set(val)
    @property
    def PhysicsDamping(self):  # type: ()->Float
        return Float(self._node.at("PhysicsDamping"))
    @PhysicsDamping.setter
    def PhysicsDamping(self, val): self.PhysicsDamping.set(val)
    @property
    def PhysicsFixedDt(self):  # type: ()->Bool
        return Bool(self._node.at("PhysicsFixedDt"))
    @PhysicsFixedDt.setter
    def PhysicsFixedDt(self, val): self.PhysicsFixedDt.set(val)
    @property
    def PhysicsGravity(self):  # type: ()->Vector3
        return Vector3(self._node.at("PhysicsGravity"))
    @PhysicsGravity.setter
    def PhysicsGravity(self, val): self.PhysicsGravity.set(val)
    @property
    def PhysicsMass(self):  # type: ()->Float
        return Float(self._node.at("PhysicsMass"))
    @PhysicsMass.setter
    def PhysicsMass(self, val): self.PhysicsMass.set(val)
    @property
    def PhysicsSpeedInfluence(self):  # type: ()->Float
        return Float(self._node.at("PhysicsSpeedInfluence"))
    @PhysicsSpeedInfluence.setter
    def PhysicsSpeedInfluence(self, val): self.PhysicsSpeedInfluence.set(val)
    @property
    def PhysicsUseDefaultProperties(self):  # type: ()->Bool
        return Bool(self._node.at("PhysicsUseDefaultProperties"))
    @PhysicsUseDefaultProperties.setter
    def PhysicsUseDefaultProperties(self, val): self.PhysicsUseDefaultProperties.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




