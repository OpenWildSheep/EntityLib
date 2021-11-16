
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class AnimationPhysicsChainConstraintsGD(HelperObject):
    schema_name = "AnimationPhysicsChainConstraintsGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationPhysicsChainConstraintsGD
        return AnimationPhysicsChainConstraintsGD(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationPhysicsChainConstraintsGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationPhysicsChainConstraintsGD
        return AnimationPhysicsChainConstraintsGD(entlib.make_node(AnimationPhysicsChainConstraintsGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BoneNamePrefix(self):  # type: ()->String
        return String(self._node.at("BoneNamePrefix"))
    @BoneNamePrefix.setter
    def BoneNamePrefix(self, val): self.BoneNamePrefix.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




