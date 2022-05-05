
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.AttackComponentGD_AerialAttackData import *
from entgen.AttackPositionRetimingData import *
from entgen.ComponentGD import *
from entgen.lightAttackData import *
from entgen.strongAttackData import *

from EntityLibPy import Node

class AttackComponentGD(HelperObject):
    schema_name = "AttackComponentGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AttackComponentGD
        return AttackComponentGD(entlib.load_node_file(sourcefile, entlib.get_schema(AttackComponentGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AttackComponentGD
        return AttackComponentGD(entlib.make_node(AttackComponentGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AerialAttackData(self):  # type: ()->AttackComponentGD_AerialAttackData
        return AttackComponentGD_AerialAttackData(self._node.at("AerialAttackData"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def attackPositionRetimingData(self):  # type: ()->AttackPositionRetimingData
        return AttackPositionRetimingData(self._node.at("attackPositionRetimingData"))
    @property
    def lightAttackData(self):  # type: ()->lightAttackData
        return lightAttackData(self._node.at("lightAttackData"))
    @property
    def strongAttackData(self):  # type: ()->strongAttackData
        return strongAttackData(self._node.at("strongAttackData"))
    pass




