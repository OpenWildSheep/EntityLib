
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *

from EntityLibPy import Node

class AnimationRegenConstraintsGD(HelperObject):
    schema_name = "AnimationRegenConstraintsGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationRegenConstraintsGD
        return AnimationRegenConstraintsGD(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationRegenConstraintsGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationRegenConstraintsGD
        return AnimationRegenConstraintsGD(entlib.make_node(AnimationRegenConstraintsGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def MaxDisplace(self):  # type: ()->Float
        return Float(self._node.at("MaxDisplace"))
    @MaxDisplace.setter
    def MaxDisplace(self, val): self.MaxDisplace.set(val)
    @property
    def MaxRegenSpeed(self):  # type: ()->Float
        return Float(self._node.at("MaxRegenSpeed"))
    @MaxRegenSpeed.setter
    def MaxRegenSpeed(self, val): self.MaxRegenSpeed.set(val)
    @property
    def MinDisplace(self):  # type: ()->Float
        return Float(self._node.at("MinDisplace"))
    @MinDisplace.setter
    def MinDisplace(self, val): self.MinDisplace.set(val)
    @property
    def RegenMultiplier(self):  # type: ()->Float
        return Float(self._node.at("RegenMultiplier"))
    @RegenMultiplier.setter
    def RegenMultiplier(self, val): self.RegenMultiplier.set(val)
    @property
    def RegenToDisplaceCurve(self):  # type: ()->String
        return String(self._node.at("RegenToDisplaceCurve"))
    @RegenToDisplaceCurve.setter
    def RegenToDisplaceCurve(self, val): self.RegenToDisplaceCurve.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




