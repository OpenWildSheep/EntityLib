
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.CineEventTrigger import *


class CineEventTriggerPlaySequence(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CineEventTriggerPlaySequence"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTriggerPlaySequence.schema_name))
    @property
    def SequenceID(self): return Int(self._node.at("SequenceID"))
    @SequenceID.setter
    def SequenceID(self, val): self.SequenceID.set(val)
    @property
    def Super(self): return CineEventTrigger(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




