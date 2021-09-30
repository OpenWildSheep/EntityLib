
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.Vector3 import *


class ClothAnimationGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ClothAnimationGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(ClothAnimationGD.schema_name))
    @property
    def ClothSkeletonPath(self): return String(self._node.at("ClothSkeletonPath"))
    @ClothSkeletonPath.setter
    def ClothSkeletonPath(self, val): self.ClothSkeletonPath.set(val)
    @property
    def PhysicsDamping(self): return Float(self._node.at("PhysicsDamping"))
    @PhysicsDamping.setter
    def PhysicsDamping(self, val): self.PhysicsDamping.set(val)
    @property
    def PhysicsFixedDt(self): return Bool(self._node.at("PhysicsFixedDt"))
    @PhysicsFixedDt.setter
    def PhysicsFixedDt(self, val): self.PhysicsFixedDt.set(val)
    @property
    def PhysicsGravity(self): return Vector3(self._node.at("PhysicsGravity"))
    @PhysicsGravity.setter
    def PhysicsGravity(self, val): self.PhysicsGravity.set(val)
    @property
    def PhysicsMass(self): return Float(self._node.at("PhysicsMass"))
    @PhysicsMass.setter
    def PhysicsMass(self, val): self.PhysicsMass.set(val)
    @property
    def PhysicsSpeedInfluence(self): return Float(self._node.at("PhysicsSpeedInfluence"))
    @PhysicsSpeedInfluence.setter
    def PhysicsSpeedInfluence(self, val): self.PhysicsSpeedInfluence.set(val)
    @property
    def PhysicsUseDefaultProperties(self): return Bool(self._node.at("PhysicsUseDefaultProperties"))
    @PhysicsUseDefaultProperties.setter
    def PhysicsUseDefaultProperties(self, val): self.PhysicsUseDefaultProperties.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




