
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class GameBiteData(HelperObject):
    schema_name = "GameBiteData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameBiteData
        return GameBiteData(entlib.load_node_file(sourcefile, entlib.get_schema(GameBiteData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameBiteData
        return GameBiteData(entlib.make_node(GameBiteData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BiterShakeStamina(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("BiterShakeStamina"))
    @BiterShakeStamina.setter
    def BiterShakeStamina(self, val): self.BiterShakeStamina.set(val)
    @property
    def BiterStrength(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("BiterStrength"))
    @BiterStrength.setter
    def BiterStrength(self, val): self.BiterStrength.set(val)
    @property
    def BittenResistance(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("BittenResistance"))
    @BittenResistance.setter
    def BittenResistance(self, val): self.BittenResistance.set(val)
    @property
    def BittenShakeExhaustion(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("BittenShakeExhaustion"))
    @BittenShakeExhaustion.setter
    def BittenShakeExhaustion(self, val): self.BittenShakeExhaustion.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




