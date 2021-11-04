
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.CineEventTrigger import *

from EntityLibPy import Node

class CineEventTriggerGameStateChange(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CineEventTriggerGameStateChange"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CineEventTriggerGameStateChange
        return CineEventTriggerGameStateChange(entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTriggerGameStateChange.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CineEventTriggerGameStateChange
        return CineEventTriggerGameStateChange(entlib.make_node(CineEventTriggerGameStateChange.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def GameStateName(self):  # type: ()->String
        return String(self._node.at("GameStateName"))
    @GameStateName.setter
    def GameStateName(self, val): self.GameStateName.set(val)
    @property
    def Super(self):  # type: ()->CineEventTrigger
        return CineEventTrigger(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




