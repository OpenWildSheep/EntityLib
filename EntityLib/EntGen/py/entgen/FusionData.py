
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.EntityRef import *
from entgen.Float import *

from EntityLibPy import Node

class FusionData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FusionData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FusionData
        return FusionData(entlib.load_node_file(sourcefile, entlib.get_schema(FusionData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FusionData
        return FusionData(entlib.make_node(FusionData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def IsSoul(self):  # type: ()->Bool
        return Bool(self._node.at("IsSoul"))
    @IsSoul.setter
    def IsSoul(self, val): self.IsSoul.set(val)
    @property
    def SoulEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("SoulEntityRef"))
    @SoulEntityRef.setter
    def SoulEntityRef(self, val): self.SoulEntityRef.set(val)
    @property
    def WarriorDamageFactor(self):  # type: ()->Float
        return Float(self._node.at("WarriorDamageFactor"))
    @WarriorDamageFactor.setter
    def WarriorDamageFactor(self, val): self.WarriorDamageFactor.set(val)
    @property
    def WarriorImpactFactor(self):  # type: ()->Float
        return Float(self._node.at("WarriorImpactFactor"))
    @WarriorImpactFactor.setter
    def WarriorImpactFactor(self, val): self.WarriorImpactFactor.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




