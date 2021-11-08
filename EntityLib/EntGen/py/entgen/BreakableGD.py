
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class BreakableGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/BreakableGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BreakableGD
        return BreakableGD(entlib.load_node_file(sourcefile, entlib.get_schema(BreakableGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BreakableGD
        return BreakableGD(entlib.make_node(BreakableGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BreakSoundBank(self):  # type: ()->String
        return String(self._node.at("BreakSoundBank"))
    @BreakSoundBank.setter
    def BreakSoundBank(self, val): self.BreakSoundBank.set(val)
    @property
    def BreakSoundEvent(self):  # type: ()->String
        return String(self._node.at("BreakSoundEvent"))
    @BreakSoundEvent.setter
    def BreakSoundEvent(self, val): self.BreakSoundEvent.set(val)
    @property
    def GameEffectOnBroken(self):  # type: ()->String
        return String(self._node.at("GameEffectOnBroken"))
    @GameEffectOnBroken.setter
    def GameEffectOnBroken(self, val): self.GameEffectOnBroken.set(val)
    @property
    def GameEffectOnDestruction(self):  # type: ()->String
        return String(self._node.at("GameEffectOnDestruction"))
    @GameEffectOnDestruction.setter
    def GameEffectOnDestruction(self, val): self.GameEffectOnDestruction.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def isBreakableWithAttack(self):  # type: ()->Bool
        return Bool(self._node.at("isBreakableWithAttack"))
    @isBreakableWithAttack.setter
    def isBreakableWithAttack(self, val): self.isBreakableWithAttack.set(val)
    pass



