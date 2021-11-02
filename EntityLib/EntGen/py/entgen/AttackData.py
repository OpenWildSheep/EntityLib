
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.AttackType import *
from entgen.String import *
from entgen.AttackWeaponAbility import *

from EntityLibPy import Node

class AttackData(HelperObject):
    schema_name = "AttackData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AttackData
        return AttackData(entlib.load_node_file(sourcefile, entlib.get_schema(AttackData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AttackData
        return AttackData(entlib.make_node(AttackData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DefaultAttackType(self):  # type: ()->AttackType
        return AttackType(self._node.at("DefaultAttackType"))
    @DefaultAttackType.setter
    def DefaultAttackType(self, val): self.DefaultAttackType.set(val)
    @property
    def Hammer(self):  # type: ()->AttackWeaponAbility
        return AttackWeaponAbility(self._node.at("Hammer"))
    @property
    def Knife(self):  # type: ()->AttackWeaponAbility
        return AttackWeaponAbility(self._node.at("Knife"))
    @property
    def None_(self):  # type: ()->AttackWeaponAbility
        return AttackWeaponAbility(self._node.at("None"))
    @property
    def Stick(self):  # type: ()->AttackWeaponAbility
        return AttackWeaponAbility(self._node.at("Stick"))
    @property
    def Sword(self):  # type: ()->AttackWeaponAbility
        return AttackWeaponAbility(self._node.at("Sword"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




