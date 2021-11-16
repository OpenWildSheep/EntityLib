
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.String import *

from EntityLibPy import Node

class EventTriggerGD(HelperObject):
    schema_name = "EventTriggerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EventTriggerGD
        return EventTriggerGD(entlib.load_node_file(sourcefile, entlib.get_schema(EventTriggerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EventTriggerGD
        return EventTriggerGD(entlib.make_node(EventTriggerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Events(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("Events"))
    @Events.setter
    def Events(self, val): self.Events.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




