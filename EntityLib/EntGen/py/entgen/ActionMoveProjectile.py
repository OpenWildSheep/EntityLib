
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.ProjectileTrajectory import *

from EntityLibPy import Node

class ActionMoveProjectile(HelperObject):
    schema_name = "ActionMoveProjectile"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionMoveProjectile
        return ActionMoveProjectile(entlib.load_node_file(sourcefile, entlib.get_schema(ActionMoveProjectile.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionMoveProjectile
        return ActionMoveProjectile(entlib.make_node(ActionMoveProjectile.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def Trajectory(self):  # type: ()->ProjectileTrajectory
        return ProjectileTrajectory(self._node.at("Trajectory"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




