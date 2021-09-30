
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.EntityRef import *
from entgen.Float import *


class FusionData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FusionData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(FusionData.schema_name))
    @property
    def IsSoul(self): return Bool(self._node.at("IsSoul"))
    @IsSoul.setter
    def IsSoul(self, val): self.IsSoul.set(val)
    @property
    def SoulEntityRef(self): return EntityRef(self._node.at("SoulEntityRef"))
    @SoulEntityRef.setter
    def SoulEntityRef(self, val): self.SoulEntityRef.set(val)
    @property
    def WarriorDamageFactor(self): return Float(self._node.at("WarriorDamageFactor"))
    @WarriorDamageFactor.setter
    def WarriorDamageFactor(self, val): self.WarriorDamageFactor.set(val)
    @property
    def WarriorImpactFactor(self): return Float(self._node.at("WarriorImpactFactor"))
    @WarriorImpactFactor.setter
    def WarriorImpactFactor(self, val): self.WarriorImpactFactor.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




