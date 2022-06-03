
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Float import *

from EntityLibPy import Node

class EntityStateBridgeBeingControlled(HelperObject):
    schema_name = "EntityStateBridgeBeingControlled"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateBridgeBeingControlled
        return EntityStateBridgeBeingControlled(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateBridgeBeingControlled.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateBridgeBeingControlled
        return EntityStateBridgeBeingControlled(entlib.make_node(EntityStateBridgeBeingControlled.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CollisionRaycastLength(self):  # type: ()->Float
        return Float(self._node.at("CollisionRaycastLength"))
    @CollisionRaycastLength.setter
    def CollisionRaycastLength(self, val): self.CollisionRaycastLength.set(val)
    @property
    def HorizontalSpeed(self):  # type: ()->Float
        return Float(self._node.at("HorizontalSpeed"))
    @HorizontalSpeed.setter
    def HorizontalSpeed(self, val): self.HorizontalSpeed.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def VerticalSpeed(self):  # type: ()->Float
        return Float(self._node.at("VerticalSpeed"))
    @VerticalSpeed.setter
    def VerticalSpeed(self, val): self.VerticalSpeed.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




