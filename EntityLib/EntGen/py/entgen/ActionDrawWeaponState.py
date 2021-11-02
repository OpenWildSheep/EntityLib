
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Bool import *
from entgen.Float import *

from EntityLibPy import Node

class ActionDrawWeaponState(HelperObject):
    schema_name = "ActionDrawWeaponState"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionDrawWeaponState
        return ActionDrawWeaponState(entlib.load_node_file(sourcefile, entlib.get_schema(ActionDrawWeaponState.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionDrawWeaponState
        return ActionDrawWeaponState(entlib.make_node(ActionDrawWeaponState.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def m_longRangeWeapon(self):  # type: ()->Bool
        return Bool(self._node.at("m_longRangeWeapon"))
    @m_longRangeWeapon.setter
    def m_longRangeWeapon(self, val): self.m_longRangeWeapon.set(val)
    @property
    def m_noDrawAnimation(self):  # type: ()->Bool
        return Bool(self._node.at("m_noDrawAnimation"))
    @m_noDrawAnimation.setter
    def m_noDrawAnimation(self, val): self.m_noDrawAnimation.set(val)
    @property
    def m_offHandWeapon(self):  # type: ()->Bool
        return Bool(self._node.at("m_offHandWeapon"))
    @m_offHandWeapon.setter
    def m_offHandWeapon(self, val): self.m_offHandWeapon.set(val)
    @property
    def m_sheatheDuration(self):  # type: ()->Float
        return Float(self._node.at("m_sheatheDuration"))
    @m_sheatheDuration.setter
    def m_sheatheDuration(self, val): self.m_sheatheDuration.set(val)
    @property
    def m_shortDrawAnimation(self):  # type: ()->Bool
        return Bool(self._node.at("m_shortDrawAnimation"))
    @m_shortDrawAnimation.setter
    def m_shortDrawAnimation(self, val): self.m_shortDrawAnimation.set(val)
    @property
    def m_timer(self):  # type: ()->Float
        return Float(self._node.at("m_timer"))
    @m_timer.setter
    def m_timer(self, val): self.m_timer.set(val)
    pass




