
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.AnimTag import *
from entgen.String import *
from entgen.MoveCapacityData_AnimTagTimelineTransitionItem import *


class MoveCapacityData_AnimTagTimelineTransitionTable(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/MoveCapacityData::AnimTagTimelineTransitionTable"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(MoveCapacityData_AnimTagTimelineTransitionTable.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def from_(self): return AnimTag(self._node.at("from_"))
    @from_.setter
    def from_(self, val): self.from_.set(val)
    @property
    def transitions(self): return (lambda n: Array(MoveCapacityData_AnimTagTimelineTransitionItem, n))(self._node.at("transitions"))
    pass




