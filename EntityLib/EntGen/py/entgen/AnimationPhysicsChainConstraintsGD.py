
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *


class AnimationPhysicsChainConstraintsGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimationPhysicsChainConstraintsGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(AnimationPhysicsChainConstraintsGD.schema_name))
    @property
    def BoneNamePrefix(self): return String(self._node.at("BoneNamePrefix"))
    @BoneNamePrefix.setter
    def BoneNamePrefix(self, val): self.BoneNamePrefix.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




