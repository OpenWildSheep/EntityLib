
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.AnimationEventsGeneratorGD_TrackedBone import *


class AnimationEventsGeneratorGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimationEventsGeneratorGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(AnimationEventsGeneratorGD.schema_name))
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def TrackedBones(self): return (lambda n: Array(AnimationEventsGeneratorGD_TrackedBone, n))(self._node.at("TrackedBones"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




