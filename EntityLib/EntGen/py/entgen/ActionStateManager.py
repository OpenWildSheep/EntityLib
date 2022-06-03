
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Manager import *

from EntityLibPy import Node

class ActionStateManager(HelperObject):
    schema_name = "ActionStateManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionStateManager
        return ActionStateManager(entlib.load_node_file(sourcefile, entlib.get_schema(ActionStateManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionStateManager
        return ActionStateManager(entlib.make_node(ActionStateManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ArbiterConfigFile(self):  # type: ()->String
        return String(self._node.at("ArbiterConfigFile"))
    @ArbiterConfigFile.setter
    def ArbiterConfigFile(self, val): self.ArbiterConfigFile.set(val)
    @property
    def ForceTraceActorState(self):  # type: ()->Bool
        return Bool(self._node.at("ForceTraceActorState"))
    @ForceTraceActorState.setter
    def ForceTraceActorState(self, val): self.ForceTraceActorState.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




