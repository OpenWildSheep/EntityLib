
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.AttackAbility import *

from EntityLibPy import Node

class AttackWeaponAbility(HelperObject):
    schema_name = "AttackWeaponAbility"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AttackWeaponAbility
        return AttackWeaponAbility(entlib.load_node_file(sourcefile, entlib.get_schema(AttackWeaponAbility.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AttackWeaponAbility
        return AttackWeaponAbility(entlib.make_node(AttackWeaponAbility.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Backward(self):  # type: ()->AttackAbility
        return AttackAbility(self._node.at("Backward"))
    @property
    def Bite(self):  # type: ()->AttackAbility
        return AttackAbility(self._node.at("Bite"))
    @property
    def Charged(self):  # type: ()->AttackAbility
        return AttackAbility(self._node.at("Charged"))
    @property
    def Dash(self):  # type: ()->AttackAbility
        return AttackAbility(self._node.at("Dash"))
    @property
    def Distant(self):  # type: ()->AttackAbility
        return AttackAbility(self._node.at("Distant"))
    @property
    def Dodge(self):  # type: ()->AttackAbility
        return AttackAbility(self._node.at("Dodge"))
    @property
    def JumpOnto(self):  # type: ()->AttackAbility
        return AttackAbility(self._node.at("JumpOnto"))
    @property
    def Landing(self):  # type: ()->AttackAbility
        return AttackAbility(self._node.at("Landing"))
    @property
    def Long(self):  # type: ()->AttackAbility
        return AttackAbility(self._node.at("Long"))
    @property
    def Push(self):  # type: ()->AttackAbility
        return AttackAbility(self._node.at("Push"))
    @property
    def Short(self):  # type: ()->AttackAbility
        return AttackAbility(self._node.at("Short"))
    @property
    def Stomp(self):  # type: ()->AttackAbility
        return AttackAbility(self._node.at("Stomp"))
    @property
    def Unmount(self):  # type: ()->AttackAbility
        return AttackAbility(self._node.at("Unmount"))
    @property
    def Uppercut(self):  # type: ()->AttackAbility
        return AttackAbility(self._node.at("Uppercut"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




