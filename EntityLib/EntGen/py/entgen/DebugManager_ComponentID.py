
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.EntityID import *

from EntityLibPy import Node

class DebugManager_ComponentID(HelperObject):
    schema_name = "DebugManager::ComponentID"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->DebugManager_ComponentID
        return DebugManager_ComponentID(entlib.load_node_file(sourcefile, entlib.get_schema(DebugManager_ComponentID.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->DebugManager_ComponentID
        return DebugManager_ComponentID(entlib.make_node(DebugManager_ComponentID.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ComponentNameID(self):  # type: ()->String
        return String(self._node.at("ComponentNameID"))
    @ComponentNameID.setter
    def ComponentNameID(self, val): self.ComponentNameID.set(val)
    @property
    def EntityID(self):  # type: ()->EntityID
        return EntityID(self._node.at("EntityID"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




