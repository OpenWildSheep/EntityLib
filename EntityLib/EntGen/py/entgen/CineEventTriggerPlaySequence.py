
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.CineEventTrigger import *

from EntityLibPy import Node

class CineEventTriggerPlaySequence(HelperObject):
    schema_name = "CineEventTriggerPlaySequence"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CineEventTriggerPlaySequence
        return CineEventTriggerPlaySequence(entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTriggerPlaySequence.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CineEventTriggerPlaySequence
        return CineEventTriggerPlaySequence(entlib.make_node(CineEventTriggerPlaySequence.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def SequenceID(self):  # type: ()->Int
        return Int(self._node.at("SequenceID"))
    @SequenceID.setter
    def SequenceID(self, val): self.SequenceID.set(val)
    @property
    def Super(self):  # type: ()->CineEventTrigger
        return CineEventTrigger(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




