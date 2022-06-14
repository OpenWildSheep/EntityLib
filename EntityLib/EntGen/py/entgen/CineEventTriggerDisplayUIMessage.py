
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.CineEventTrigger import *
from entgen.UIMessage import *

from EntityLibPy import Node

class CineEventTriggerDisplayUIMessage(HelperObject):
    schema_name = "CineEventTriggerDisplayUIMessage"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CineEventTriggerDisplayUIMessage
        return CineEventTriggerDisplayUIMessage(entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTriggerDisplayUIMessage.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CineEventTriggerDisplayUIMessage
        return CineEventTriggerDisplayUIMessage(entlib.make_node(CineEventTriggerDisplayUIMessage.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->CineEventTrigger
        return CineEventTrigger(self._node.at("Super"))
    @property
    def UIMessage(self):  # type: ()->UIMessage
        return UIMessage(self._node.at("UIMessage"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




