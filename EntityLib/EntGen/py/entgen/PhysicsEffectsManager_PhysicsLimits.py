
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *

from EntityLibPy import Node

class PhysicsEffectsManager_PhysicsLimits(HelperObject):
    schema_name = "PhysicsEffectsManager::PhysicsLimits"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PhysicsEffectsManager_PhysicsLimits
        return PhysicsEffectsManager_PhysicsLimits(entlib.load_node_file(sourcefile, entlib.get_schema(PhysicsEffectsManager_PhysicsLimits.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PhysicsEffectsManager_PhysicsLimits
        return PhysicsEffectsManager_PhysicsLimits(entlib.make_node(PhysicsEffectsManager_PhysicsLimits.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AvgShapesPerRigidBody(self):  # type: ()->Int
        return Int(self._node.at("AvgShapesPerRigidBody"))
    @AvgShapesPerRigidBody.setter
    def AvgShapesPerRigidBody(self, val): self.AvgShapesPerRigidBody.set(val)
    @property
    def MaxDynamicRigidBodies(self):  # type: ()->Int
        return Int(self._node.at("MaxDynamicRigidBodies"))
    @MaxDynamicRigidBodies.setter
    def MaxDynamicRigidBodies(self, val): self.MaxDynamicRigidBodies.set(val)
    @property
    def MaxNonContactPairs(self):  # type: ()->Int
        return Int(self._node.at("MaxNonContactPairs"))
    @MaxNonContactPairs.setter
    def MaxNonContactPairs(self, val): self.MaxNonContactPairs.set(val)
    @property
    def MaxStaticRigidBodies(self):  # type: ()->Int
        return Int(self._node.at("MaxStaticRigidBodies"))
    @MaxStaticRigidBodies.setter
    def MaxStaticRigidBodies(self, val): self.MaxStaticRigidBodies.set(val)
    @property
    def MaxTriggerRigidBodies(self):  # type: ()->Int
        return Int(self._node.at("MaxTriggerRigidBodies"))
    @MaxTriggerRigidBodies.setter
    def MaxTriggerRigidBodies(self, val): self.MaxTriggerRigidBodies.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




