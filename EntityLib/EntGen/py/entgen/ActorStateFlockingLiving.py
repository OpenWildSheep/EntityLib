
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Bool import *

from EntityLibPy import Node

class ActorStateFlockingLiving(HelperObject):
    schema_name = "ActorStateFlockingLiving"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateFlockingLiving
        return ActorStateFlockingLiving(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateFlockingLiving.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateFlockingLiving
        return ActorStateFlockingLiving(entlib.make_node(ActorStateFlockingLiving.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CanCreateHitRigidBodies(self):  # type: ()->Bool
        return Bool(self._node.at("CanCreateHitRigidBodies"))
    @CanCreateHitRigidBodies.setter
    def CanCreateHitRigidBodies(self, val): self.CanCreateHitRigidBodies.set(val)
    @property
    def Killed(self):  # type: ()->Bool
        return Bool(self._node.at("Killed"))
    @Killed.setter
    def Killed(self, val): self.Killed.set(val)
    @property
    def Regenerated(self):  # type: ()->Bool
        return Bool(self._node.at("Regenerated"))
    @Regenerated.setter
    def Regenerated(self, val): self.Regenerated.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




