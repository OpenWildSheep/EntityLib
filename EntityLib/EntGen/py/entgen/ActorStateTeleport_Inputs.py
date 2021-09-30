
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Orientation import *
from entgen.Position import *


class ActorStateTeleport_Inputs(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ActorStateTeleport::Inputs"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateTeleport_Inputs.schema_name))
    @property
    def Orientation(self): return Orientation(self._node.at("Orientation"))
    @property
    def Position(self): return Position(self._node.at("Position"))
    @property
    def ResetCamera(self): return Bool(self._node.at("ResetCamera"))
    @ResetCamera.setter
    def ResetCamera(self, val): self.ResetCamera.set(val)
    @property
    def TouchGround(self): return Bool(self._node.at("TouchGround"))
    @TouchGround.setter
    def TouchGround(self, val): self.TouchGround.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




