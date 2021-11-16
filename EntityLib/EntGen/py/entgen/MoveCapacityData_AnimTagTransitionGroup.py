
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.AnimTag import *

from EntityLibPy import Node

class MoveCapacityData_AnimTagTransitionGroup(HelperObject):
    schema_name = "MoveCapacityData::AnimTagTransitionGroup"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MoveCapacityData_AnimTagTransitionGroup
        return MoveCapacityData_AnimTagTransitionGroup(entlib.load_node_file(sourcefile, entlib.get_schema(MoveCapacityData_AnimTagTransitionGroup.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MoveCapacityData_AnimTagTransitionGroup
        return MoveCapacityData_AnimTagTransitionGroup(entlib.make_node(MoveCapacityData_AnimTagTransitionGroup.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def animTags(self):  # type: ()->PrimArray[AnimTag]
        return (lambda n: PrimArray(AnimTag, n))(self._node.at("animTags"))
    @animTags.setter
    def animTags(self, val): self.animTags.set(val)
    @property
    def blendIn(self):  # type: ()->Float
        return Float(self._node.at("blendIn"))
    @blendIn.setter
    def blendIn(self, val): self.blendIn.set(val)
    pass




