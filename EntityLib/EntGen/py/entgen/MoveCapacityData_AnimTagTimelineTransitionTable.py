
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.AnimTag import *
from entgen.String import *
from entgen.MoveCapacityData_AnimTagTimelineTransitionItem import *

from EntityLibPy import Node

class MoveCapacityData_AnimTagTimelineTransitionTable(HelperObject):
    schema_name = "MoveCapacityData::AnimTagTimelineTransitionTable"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MoveCapacityData_AnimTagTimelineTransitionTable
        return MoveCapacityData_AnimTagTimelineTransitionTable(entlib.load_node_file(sourcefile, entlib.get_schema(MoveCapacityData_AnimTagTimelineTransitionTable.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MoveCapacityData_AnimTagTimelineTransitionTable
        return MoveCapacityData_AnimTagTimelineTransitionTable(entlib.make_node(MoveCapacityData_AnimTagTimelineTransitionTable.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def from_(self):  # type: ()->AnimTag
        return AnimTag(self._node.at("from"))
    @from_.setter
    def from_(self, val): self.from_.set(val)
    @property
    def transitions(self):  # type: ()->Array[MoveCapacityData_AnimTagTimelineTransitionItem]
        return (lambda n: Array(MoveCapacityData_AnimTagTimelineTransitionItem, n))(self._node.at("transitions"))
    pass




