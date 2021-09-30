
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.AnimTag import *
from entgen.AnimTagTimelineTransition import *
from entgen.String import *


class MoveCapacityData_AnimTagTimelineTransitionItem(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/MoveCapacityData::AnimTagTimelineTransitionItem"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(MoveCapacityData_AnimTagTimelineTransitionItem.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def to(self): return AnimTag(self._node.at("to"))
    @to.setter
    def to(self, val): self.to.set(val)
    @property
    def type(self): return AnimTagTimelineTransition(self._node.at("type"))
    @type.setter
    def type(self, val): self.type.set(val)
    pass




