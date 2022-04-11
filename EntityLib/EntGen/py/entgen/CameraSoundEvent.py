
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *

from EntityLibPy import Node

class CameraSoundEvent(HelperObject):
    schema_name = "CameraSoundEvent"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CameraSoundEvent
        return CameraSoundEvent(entlib.load_node_file(sourcefile, entlib.get_schema(CameraSoundEvent.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CameraSoundEvent
        return CameraSoundEvent(entlib.make_node(CameraSoundEvent.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def eventName(self):  # type: ()->String
        return String(self._node.at("eventName"))
    @eventName.setter
    def eventName(self, val): self.eventName.set(val)
    @property
    def from_(self):  # type: ()->String
        return String(self._node.at("from"))
    @from_.setter
    def from_(self, val): self.from_.set(val)
    @property
    def to(self):  # type: ()->String
        return String(self._node.at("to"))
    @to.setter
    def to(self, val): self.to.set(val)
    pass




