
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.AnimTag import *
from entgen.AnimTagTimelineTransition import *
from entgen.String import *

from EntityLibPy import Node

class MoveCapacityData_AnimTagTimelineTransitionItem(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/MoveCapacityData::AnimTagTimelineTransitionItem"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MoveCapacityData_AnimTagTimelineTransitionItem
        return MoveCapacityData_AnimTagTimelineTransitionItem(entlib.load_node_file(sourcefile, entlib.get_schema(MoveCapacityData_AnimTagTimelineTransitionItem.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MoveCapacityData_AnimTagTimelineTransitionItem
        return MoveCapacityData_AnimTagTimelineTransitionItem(entlib.make_node(MoveCapacityData_AnimTagTimelineTransitionItem.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def to(self):  # type: ()->AnimTag
        return AnimTag(self._node.at("to"))
    @to.setter
    def to(self, val): self.to.set(val)
    @property
    def type(self):  # type: ()->AnimTagTimelineTransition
        return AnimTagTimelineTransition(self._node.at("type"))
    @type.setter
    def type(self, val): self.type.set(val)
    pass




