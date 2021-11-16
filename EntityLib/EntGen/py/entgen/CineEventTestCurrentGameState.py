
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.CineEventTest import *

from EntityLibPy import Node

class CineEventTestCurrentGameState(HelperObject):
    schema_name = "CineEventTestCurrentGameState"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CineEventTestCurrentGameState
        return CineEventTestCurrentGameState(entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTestCurrentGameState.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CineEventTestCurrentGameState
        return CineEventTestCurrentGameState(entlib.make_node(CineEventTestCurrentGameState.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def GameStateName(self):  # type: ()->String
        return String(self._node.at("GameStateName"))
    @GameStateName.setter
    def GameStateName(self, val): self.GameStateName.set(val)
    @property
    def Super(self):  # type: ()->CineEventTest
        return CineEventTest(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




