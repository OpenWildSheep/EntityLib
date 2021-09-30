
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.Archetype import *
from entgen.Specie import *
from entgen.StyleMode import *
from entgen.String import *
from entgen.AbilityData import *
from entgen.AttackData import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.LifeAndDamageData import *
from entgen.ProjectileData import *
from entgen.ShootData import *
from entgen.StunData import *


class ActorGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ActorGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(ActorGD.schema_name))
    @property
    def Archetype(self): return Archetype(self._node.at("Archetype"))
    @Archetype.setter
    def Archetype(self, val): self.Archetype.set(val)
    @property
    def ClassStyleTag(self): return StyleMode(self._node.at("ClassStyleTag"))
    @ClassStyleTag.setter
    def ClassStyleTag(self, val): self.ClassStyleTag.set(val)
    @property
    def FactionName(self): return String(self._node.at("FactionName"))
    @FactionName.setter
    def FactionName(self, val): self.FactionName.set(val)
    @property
    def Icon(self): return String(self._node.at("Icon"))
    @Icon.setter
    def Icon(self, val): self.Icon.set(val)
    @property
    def InSpiritWorld(self): return Bool(self._node.at("InSpiritWorld"))
    @InSpiritWorld.setter
    def InSpiritWorld(self, val): self.InSpiritWorld.set(val)
    @property
    def Specie(self): return Specie(self._node.at("Specie"))
    @Specie.setter
    def Specie(self, val): self.Specie.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def Weapon(self): return Bool(self._node.at("Weapon"))
    @Weapon.setter
    def Weapon(self, val): self.Weapon.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def abilityData(self): return AbilityData(self._node.at("abilityData"))
    @property
    def attackData(self): return AttackData(self._node.at("attackData"))
    @property
    def lifeAndDamageData(self): return LifeAndDamageData(self._node.at("lifeAndDamageData"))
    @property
    def projectileData(self): return ProjectileData(self._node.at("projectileData"))
    @property
    def radius(self): return Float(self._node.at("radius"))
    @radius.setter
    def radius(self, val): self.radius.set(val)
    @property
    def shootData(self): return ShootData(self._node.at("shootData"))
    @property
    def stunData(self): return StunData(self._node.at("stunData"))
    @property
    def volume(self): return Float(self._node.at("volume"))
    @volume.setter
    def volume(self, val): self.volume.set(val)
    pass




