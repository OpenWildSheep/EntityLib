
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.EntityRef import *
from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Float import *

from EntityLibPy import Node

class BreakableGD(HelperObject):
    schema_name = "BreakableGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BreakableGD
        return BreakableGD(entlib.load_node_file(sourcefile, entlib.get_schema(BreakableGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BreakableGD
        return BreakableGD(entlib.make_node(BreakableGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AssemblyEntity(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("AssemblyEntity"))
    @AssemblyEntity.setter
    def AssemblyEntity(self, val): self.AssemblyEntity.set(val)
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
    def ChildEntity(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("ChildEntity"))
    @ChildEntity.setter
    def ChildEntity(self, val): self.ChildEntity.set(val)
    @property
    def FadeoutDuration(self):  # type: ()->Float
        return Float(self._node.at("FadeoutDuration"))
    @FadeoutDuration.setter
    def FadeoutDuration(self, val): self.FadeoutDuration.set(val)
    @property
    def GameEffectOnBreaking(self):  # type: ()->String
        return String(self._node.at("GameEffectOnBreaking"))
    @GameEffectOnBreaking.setter
    def GameEffectOnBreaking(self, val): self.GameEffectOnBreaking.set(val)
    @property
    def MaxContactAngle(self):  # type: ()->Float
        return Float(self._node.at("MaxContactAngle"))
    @MaxContactAngle.setter
    def MaxContactAngle(self, val): self.MaxContactAngle.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def TimeBeforeFade(self):  # type: ()->Float
        return Float(self._node.at("TimeBeforeFade"))
    @TimeBeforeFade.setter
    def TimeBeforeFade(self, val): self.TimeBeforeFade.set(val)
    @property
    def UnbrokenEntity(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("UnbrokenEntity"))
    @UnbrokenEntity.setter
    def UnbrokenEntity(self, val): self.UnbrokenEntity.set(val)
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




