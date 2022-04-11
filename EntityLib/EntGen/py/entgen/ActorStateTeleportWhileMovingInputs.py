
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.Position import *
from entgen.Quat import *
from entgen.Vector3 import *

from EntityLibPy import Node

class ActorStateTeleportWhileMovingInputs(HelperObject):
    schema_name = "ActorStateTeleportWhileMovingInputs"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateTeleportWhileMovingInputs
        return ActorStateTeleportWhileMovingInputs(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateTeleportWhileMovingInputs.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateTeleportWhileMovingInputs
        return ActorStateTeleportWhileMovingInputs(entlib.make_node(ActorStateTeleportWhileMovingInputs.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def aerialMount(self):  # type: ()->Bool
        return Bool(self._node.at("aerialMount"))
    @aerialMount.setter
    def aerialMount(self, val): self.aerialMount.set(val)
    @property
    def direction(self):  # type: ()->Vector3
        return Vector3(self._node.at("direction"))
    @direction.setter
    def direction(self, val): self.direction.set(val)
    @property
    def orientation(self):  # type: ()->Quat
        return Quat(self._node.at("orientation"))
    @orientation.setter
    def orientation(self, val): self.orientation.set(val)
    @property
    def position(self):  # type: ()->Position
        return Position(self._node.at("position"))
    @property
    def speedRequired(self):  # type: ()->Float
        return Float(self._node.at("speedRequired"))
    @speedRequired.setter
    def speedRequired(self, val): self.speedRequired.set(val)
    pass




