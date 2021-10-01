
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.CineEventTrigger import *

from EntityLibPy import Node

class CineEventTriggerEventHandlerPost(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CineEventTriggerEventHandlerPost"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CineEventTriggerEventHandlerPost
        return CineEventTriggerEventHandlerPost(entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTriggerEventHandlerPost.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CineEventTriggerEventHandlerPost
        return CineEventTriggerEventHandlerPost(entlib.make_node(CineEventTriggerEventHandlerPost.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EventCategory(self):  # type: ()->String
        return String(self._node.at("EventCategory"))
    @EventCategory.setter
    def EventCategory(self, val): self.EventCategory.set(val)
    @property
    def EventName(self):  # type: ()->String
        return String(self._node.at("EventName"))
    @EventName.setter
    def EventName(self, val): self.EventName.set(val)
    @property
    def Super(self):  # type: ()->CineEventTrigger
        return CineEventTrigger(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




