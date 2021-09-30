
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *


class BreakableGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/BreakableGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(BreakableGD.schema_name))
    @property
    def BreakSoundBank(self): return String(self._node.at("BreakSoundBank"))
    @BreakSoundBank.setter
    def BreakSoundBank(self, val): self.BreakSoundBank.set(val)
    @property
    def BreakSoundEvent(self): return String(self._node.at("BreakSoundEvent"))
    @BreakSoundEvent.setter
    def BreakSoundEvent(self, val): self.BreakSoundEvent.set(val)
    @property
    def GameEffectOnBroken(self): return String(self._node.at("GameEffectOnBroken"))
    @GameEffectOnBroken.setter
    def GameEffectOnBroken(self, val): self.GameEffectOnBroken.set(val)
    @property
    def GameEffectOnDestruction(self): return String(self._node.at("GameEffectOnDestruction"))
    @GameEffectOnDestruction.setter
    def GameEffectOnDestruction(self, val): self.GameEffectOnDestruction.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def isBreakableWithAttack(self): return Bool(self._node.at("isBreakableWithAttack"))
    @isBreakableWithAttack.setter
    def isBreakableWithAttack(self, val): self.isBreakableWithAttack.set(val)
    pass




