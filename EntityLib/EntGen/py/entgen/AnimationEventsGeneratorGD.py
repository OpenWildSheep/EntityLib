
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.AnimationEventsGeneratorGD_TrackedBone import *

from EntityLibPy import Node

class AnimationEventsGeneratorGD(HelperObject):
    schema_name = "AnimationEventsGeneratorGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationEventsGeneratorGD
        return AnimationEventsGeneratorGD(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationEventsGeneratorGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationEventsGeneratorGD
        return AnimationEventsGeneratorGD(entlib.make_node(AnimationEventsGeneratorGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def TrackedBones(self):  # type: ()->Array[AnimationEventsGeneratorGD_TrackedBone]
        return (lambda n: Array(AnimationEventsGeneratorGD_TrackedBone, n))(self._node.at("TrackedBones"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




