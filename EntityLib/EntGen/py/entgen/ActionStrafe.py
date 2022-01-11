
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Bool import *
from entgen.Float import *
from entgen.Vector3 import *

from EntityLibPy import Node

class ActionStrafe(HelperObject):
    schema_name = "ActionStrafe"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionStrafe
        return ActionStrafe(entlib.load_node_file(sourcefile, entlib.get_schema(ActionStrafe.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionStrafe
        return ActionStrafe(entlib.make_node(ActionStrafe.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def changeAnimationAllowed(self):  # type: ()->Bool
        return Bool(self._node.at("changeAnimationAllowed"))
    @changeAnimationAllowed.setter
    def changeAnimationAllowed(self, val): self.changeAnimationAllowed.set(val)
    @property
    def speedrequired(self):  # type: ()->Float
        return Float(self._node.at("speedrequired"))
    @speedrequired.setter
    def speedrequired(self, val): self.speedrequired.set(val)
    @property
    def trajectoryDir(self):  # type: ()->Vector3
        return Vector3(self._node.at("trajectoryDir"))
    @trajectoryDir.setter
    def trajectoryDir(self, val): self.trajectoryDir.set(val)
    @property
    def visualDir(self):  # type: ()->Vector3
        return Vector3(self._node.at("visualDir"))
    @visualDir.setter
    def visualDir(self, val): self.visualDir.set(val)
    pass




