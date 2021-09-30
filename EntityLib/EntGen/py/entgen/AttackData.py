
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.AttackType import *
from entgen.String import *
from entgen.AttackWeaponAbility import *


class AttackData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AttackData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(AttackData.schema_name))
    @property
    def DefaultAttackType(self): return AttackType(self._node.at("DefaultAttackType"))
    @DefaultAttackType.setter
    def DefaultAttackType(self, val): self.DefaultAttackType.set(val)
    @property
    def Hammer(self): return AttackWeaponAbility(self._node.at("Hammer"))
    @property
    def Knife(self): return AttackWeaponAbility(self._node.at("Knife"))
    @property
    def None_(self): return AttackWeaponAbility(self._node.at("None_"))
    @property
    def Stick(self): return AttackWeaponAbility(self._node.at("Stick"))
    @property
    def Sword(self): return AttackWeaponAbility(self._node.at("Sword"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




