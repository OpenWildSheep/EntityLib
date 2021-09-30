
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.String import *


class SystemicCreature(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/SystemicCreature"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(SystemicCreature.schema_name))
    @property
    def BehaviorModifierTagList(self): return (lambda n: PrimArray(String, n))(self._node.at("BehaviorModifierTagList"))
    @BehaviorModifierTagList.setter
    def BehaviorModifierTagList(self, val): self.BehaviorModifierTagList.set(val)
    @property
    def BehaviorPath(self): return String(self._node.at("BehaviorPath"))
    @BehaviorPath.setter
    def BehaviorPath(self, val): self.BehaviorPath.set(val)
    @property
    def BehaviorState(self): return String(self._node.at("BehaviorState"))
    @BehaviorState.setter
    def BehaviorState(self, val): self.BehaviorState.set(val)
    @property
    def Burried(self): return Bool(self._node.at("Burried"))
    @Burried.setter
    def Burried(self, val): self.Burried.set(val)
    @property
    def CameraTarget(self): return Bool(self._node.at("CameraTarget"))
    @CameraTarget.setter
    def CameraTarget(self, val): self.CameraTarget.set(val)
    @property
    def CanBeMaster(self): return Bool(self._node.at("CanBeMaster"))
    @CanBeMaster.setter
    def CanBeMaster(self, val): self.CanBeMaster.set(val)
    @property
    def Faction(self): return String(self._node.at("Faction"))
    @Faction.setter
    def Faction(self, val): self.Faction.set(val)
    @property
    def Inventory(self): return String(self._node.at("Inventory"))
    @Inventory.setter
    def Inventory(self, val): self.Inventory.set(val)
    @property
    def Invincible(self): return Bool(self._node.at("Invincible"))
    @Invincible.setter
    def Invincible(self, val): self.Invincible.set(val)
    @property
    def Life(self): return Float(self._node.at("Life"))
    @Life.setter
    def Life(self, val): self.Life.set(val)
    @property
    def Name(self): return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def PlayerSpawn(self): return Bool(self._node.at("PlayerSpawn"))
    @PlayerSpawn.setter
    def PlayerSpawn(self, val): self.PlayerSpawn.set(val)
    @property
    def ScriptList(self): return (lambda n: PrimArray(String, n))(self._node.at("ScriptList"))
    @ScriptList.setter
    def ScriptList(self, val): self.ScriptList.set(val)
    @property
    def Spawner(self): return String(self._node.at("Spawner"))
    @Spawner.setter
    def Spawner(self, val): self.Spawner.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def UniqueID(self): return String(self._node.at("UniqueID"))
    @UniqueID.setter
    def UniqueID(self, val): self.UniqueID.set(val)
    @property
    def Warrior(self): return Bool(self._node.at("Warrior"))
    @Warrior.setter
    def Warrior(self, val): self.Warrior.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




