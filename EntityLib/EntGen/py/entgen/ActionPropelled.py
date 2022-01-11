
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Bool import *
from entgen.Float import *
from entgen.Vector3 import *

from EntityLibPy import Node

class ActionPropelled(HelperObject):
    schema_name = "ActionPropelled"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionPropelled
        return ActionPropelled(entlib.load_node_file(sourcefile, entlib.get_schema(ActionPropelled.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionPropelled
        return ActionPropelled(entlib.make_node(ActionPropelled.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AirControlMultiplier(self):  # type: ()->Float
        return Float(self._node.at("AirControlMultiplier"))
    @AirControlMultiplier.setter
    def AirControlMultiplier(self, val): self.AirControlMultiplier.set(val)
    @property
    def FallHeightProtection(self):  # type: ()->Float
        return Float(self._node.at("FallHeightProtection"))
    @FallHeightProtection.setter
    def FallHeightProtection(self, val): self.FallHeightProtection.set(val)
    @property
    def InstantVisualOrientation(self):  # type: ()->Bool
        return Bool(self._node.at("InstantVisualOrientation"))
    @InstantVisualOrientation.setter
    def InstantVisualOrientation(self, val): self.InstantVisualOrientation.set(val)
    @property
    def PropelForce(self):  # type: ()->Vector3
        return Vector3(self._node.at("PropelForce"))
    @PropelForce.setter
    def PropelForce(self, val): self.PropelForce.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




