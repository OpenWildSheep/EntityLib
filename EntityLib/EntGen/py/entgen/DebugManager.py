
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.DebugDisplayFlags import *
from entgen.DebugManager_PlayerState import *
from entgen.Manager import *
from entgen.Online import *
from entgen.String import *
from entgen.Bool import *
from entgen.String import *
from entgen.DebugManager_ComponentID import *
from entgen.TrackedEntitiesItem import *

from EntityLibPy import Node

class DebugManager(HelperObject):
    schema_name = "DebugManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->DebugManager
        return DebugManager(entlib.load_node_file(sourcefile, entlib.get_schema(DebugManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->DebugManager
        return DebugManager(entlib.make_node(DebugManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CheatCodes(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("CheatCodes"))
    @CheatCodes.setter
    def CheatCodes(self, val): self.CheatCodes.set(val)
    @property
    def DisplayComponentType(self):  # type: ()->Map[str, Bool]
        return (lambda n: Map(str, Bool, n))(self._node.at("DisplayComponentType"))
    @property
    def DisplayManagerWindow(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayManagerWindow"))
    @DisplayManagerWindow.setter
    def DisplayManagerWindow(self, val): self.DisplayManagerWindow.set(val)
    @property
    def DisplayNodeType(self):  # type: ()->Map[str, Bool]
        return (lambda n: Map(str, Bool, n))(self._node.at("DisplayNodeType"))
    @property
    def DisplayNodeTypeWithAlwaysAutoResize(self):  # type: ()->Map[str, Bool]
        return (lambda n: Map(str, Bool, n))(self._node.at("DisplayNodeTypeWithAlwaysAutoResize"))
    @property
    def DisplayResourceWindow(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayResourceWindow"))
    @DisplayResourceWindow.setter
    def DisplayResourceWindow(self, val): self.DisplayResourceWindow.set(val)
    @property
    def Flags(self):  # type: ()->DebugDisplayFlags
        return DebugDisplayFlags(self._node.at("Flags"))
    @property
    def Online(self):  # type: ()->Online
        return Online(self._node.at("Online"))
    @property
    def PlayerState(self):  # type: ()->DebugManager_PlayerState
        return DebugManager_PlayerState(self._node.at("PlayerState"))
    @property
    def StreamPublicationCommand(self):  # type: ()->String
        return String(self._node.at("StreamPublicationCommand"))
    @StreamPublicationCommand.setter
    def StreamPublicationCommand(self, val): self.StreamPublicationCommand.set(val)
    @property
    def StreamingServerIP(self):  # type: ()->String
        return String(self._node.at("StreamingServerIP"))
    @StreamingServerIP.setter
    def StreamingServerIP(self, val): self.StreamingServerIP.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def TrackedEntities(self):  # type: ()->Array[TrackedEntitiesItem]
        return (lambda n: Array(TrackedEntitiesItem, n))(self._node.at("TrackedEntities"))
    @property
    def TrackedEntitiesSplitComponents(self):  # type: ()->Array[DebugManager_ComponentID]
        return (lambda n: Array(DebugManager_ComponentID, n))(self._node.at("TrackedEntitiesSplitComponents"))
    @property
    def WipAnimation(self):  # type: ()->Bool
        return Bool(self._node.at("WipAnimation"))
    @WipAnimation.setter
    def WipAnimation(self, val): self.WipAnimation.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




