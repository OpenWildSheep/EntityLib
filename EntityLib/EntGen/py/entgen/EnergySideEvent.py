
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.EnergySide import *
from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class EnergySideEvent(HelperObject):
    schema_name = "EnergySideEvent"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EnergySideEvent
        return EnergySideEvent(entlib.load_node_file(sourcefile, entlib.get_schema(EnergySideEvent.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EnergySideEvent
        return EnergySideEvent(entlib.make_node(EnergySideEvent.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ElapsedTime(self):  # type: ()->Float
        return Float(self._node.at("ElapsedTime"))
    @ElapsedTime.setter
    def ElapsedTime(self, val): self.ElapsedTime.set(val)
    @property
    def EnergySide(self):  # type: ()->EnergySide
        return EnergySide(self._node.at("EnergySide"))
    @EnergySide.setter
    def EnergySide(self, val): self.EnergySide.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




