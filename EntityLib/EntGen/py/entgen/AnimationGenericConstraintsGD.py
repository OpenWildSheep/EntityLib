
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.AnimationMode import *
from entgen.AnimationSpace import *
from entgen.String import *
from entgen.Int import *
from entgen.ComponentGD import *
from entgen.Float import *

from EntityLibPy import Node

class AnimationGenericConstraintsGD(HelperObject):
    schema_name = "AnimationGenericConstraintsGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationGenericConstraintsGD
        return AnimationGenericConstraintsGD(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationGenericConstraintsGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationGenericConstraintsGD
        return AnimationGenericConstraintsGD(entlib.make_node(AnimationGenericConstraintsGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AnimationMode(self):  # type: ()->AnimationMode
        return AnimationMode(self._node.at("AnimationMode"))
    @AnimationMode.setter
    def AnimationMode(self, val): self.AnimationMode.set(val)
    @property
    def AnimationPass(self):  # type: ()->Int
        return Int(self._node.at("AnimationPass"))
    @AnimationPass.setter
    def AnimationPass(self, val): self.AnimationPass.set(val)
    @property
    def AnimationSpace(self):  # type: ()->AnimationSpace
        return AnimationSpace(self._node.at("AnimationSpace"))
    @AnimationSpace.setter
    def AnimationSpace(self, val): self.AnimationSpace.set(val)
    @property
    def ControlRate(self):  # type: ()->Float
        return Float(self._node.at("ControlRate"))
    @ControlRate.setter
    def ControlRate(self, val): self.ControlRate.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




