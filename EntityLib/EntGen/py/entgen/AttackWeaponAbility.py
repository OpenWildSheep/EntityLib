
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.AttackAbility import *


class AttackWeaponAbility(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AttackWeaponAbility"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(AttackWeaponAbility.schema_name))
    @property
    def Backward(self): return AttackAbility(self._node.at("Backward"))
    @property
    def Bite(self): return AttackAbility(self._node.at("Bite"))
    @property
    def Charged(self): return AttackAbility(self._node.at("Charged"))
    @property
    def Dash(self): return AttackAbility(self._node.at("Dash"))
    @property
    def Distant(self): return AttackAbility(self._node.at("Distant"))
    @property
    def Dodge(self): return AttackAbility(self._node.at("Dodge"))
    @property
    def JumpOnto(self): return AttackAbility(self._node.at("JumpOnto"))
    @property
    def Landing(self): return AttackAbility(self._node.at("Landing"))
    @property
    def Long(self): return AttackAbility(self._node.at("Long"))
    @property
    def Push(self): return AttackAbility(self._node.at("Push"))
    @property
    def Short(self): return AttackAbility(self._node.at("Short"))
    @property
    def Stomp(self): return AttackAbility(self._node.at("Stomp"))
    @property
    def Unmount(self): return AttackAbility(self._node.at("Unmount"))
    @property
    def Uppercut(self): return AttackAbility(self._node.at("Uppercut"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




