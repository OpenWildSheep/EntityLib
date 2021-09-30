
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.CineEventTest import *


class CineEventTestCurrentGameState(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CineEventTestCurrentGameState"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTestCurrentGameState.schema_name))
    @property
    def GameStateName(self): return String(self._node.at("GameStateName"))
    @GameStateName.setter
    def GameStateName(self, val): self.GameStateName.set(val)
    @property
    def Super(self): return CineEventTest(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




