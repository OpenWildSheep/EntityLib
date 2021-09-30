
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.ActorStateTeleport_Inputs import *


class ActorStateTeleport(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ActorStateTeleport"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateTeleport.schema_name))
    @property
    def Inputs(self): return ActorStateTeleport_Inputs(self._node.at("Inputs"))
    @property
    def Super(self): return ActorState(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




