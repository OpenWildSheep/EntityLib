
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Float import *

from EntityLibPy import Node

class EntityStatePhysicsMove(HelperObject):
    schema_name = "EntityStatePhysicsMove"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStatePhysicsMove
        return EntityStatePhysicsMove(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStatePhysicsMove.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStatePhysicsMove
        return EntityStatePhysicsMove(entlib.make_node(EntityStatePhysicsMove.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AngularVelocityMultiplier(self):  # type: ()->Float
        return Float(self._node.at("AngularVelocityMultiplier"))
    @AngularVelocityMultiplier.setter
    def AngularVelocityMultiplier(self, val): self.AngularVelocityMultiplier.set(val)
    @property
    def CustomGravity(self):  # type: ()->Float
        return Float(self._node.at("CustomGravity"))
    @CustomGravity.setter
    def CustomGravity(self, val): self.CustomGravity.set(val)
    @property
    def ForceMultiplier(self):  # type: ()->Float
        return Float(self._node.at("ForceMultiplier"))
    @ForceMultiplier.setter
    def ForceMultiplier(self, val): self.ForceMultiplier.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




