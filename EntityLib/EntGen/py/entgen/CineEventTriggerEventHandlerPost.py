
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.CineEventTrigger import *


class CineEventTriggerEventHandlerPost(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CineEventTriggerEventHandlerPost"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTriggerEventHandlerPost.schema_name))
    @property
    def EventCategory(self): return String(self._node.at("EventCategory"))
    @EventCategory.setter
    def EventCategory(self, val): self.EventCategory.set(val)
    @property
    def EventName(self): return String(self._node.at("EventName"))
    @EventName.setter
    def EventName(self, val): self.EventName.set(val)
    @property
    def Super(self): return CineEventTrigger(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




