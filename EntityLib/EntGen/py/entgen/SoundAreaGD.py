
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class SoundAreaGD(HelperObject):
    schema_name = "SoundAreaGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SoundAreaGD
        return SoundAreaGD(entlib.load_node_file(sourcefile, entlib.get_schema(SoundAreaGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SoundAreaGD
        return SoundAreaGD(entlib.make_node(SoundAreaGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EventEnter(self):  # type: ()->String
        return String(self._node.at("EventEnter"))
    @EventEnter.setter
    def EventEnter(self, val): self.EventEnter.set(val)
    @property
    def EventExit(self):  # type: ()->String
        return String(self._node.at("EventExit"))
    @EventExit.setter
    def EventExit(self, val): self.EventExit.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




