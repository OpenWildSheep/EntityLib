
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Orientation import *
from entgen.Position import *

from EntityLibPy import Node

class ActorStateTeleport_Inputs(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ActorStateTeleport::Inputs"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateTeleport_Inputs
        return ActorStateTeleport_Inputs(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateTeleport_Inputs.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateTeleport_Inputs
        return ActorStateTeleport_Inputs(entlib.make_node(ActorStateTeleport_Inputs.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Orientation(self):  # type: ()->Orientation
        return Orientation(self._node.at("Orientation"))
    @property
    def Position(self):  # type: ()->Position
        return Position(self._node.at("Position"))
    @property
    def ResetCamera(self):  # type: ()->Bool
        return Bool(self._node.at("ResetCamera"))
    @ResetCamera.setter
    def ResetCamera(self, val): self.ResetCamera.set(val)
    @property
    def TouchGround(self):  # type: ()->Bool
        return Bool(self._node.at("TouchGround"))
    @TouchGround.setter
    def TouchGround(self, val): self.TouchGround.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




