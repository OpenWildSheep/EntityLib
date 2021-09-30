
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.BehaviorScriptData import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.String import *


class CreatureAIGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CreatureAIGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(CreatureAIGD.schema_name))
    @property
    def BehaviorModifiersTags(self): return (lambda n: PrimArray(String, n))(self._node.at("BehaviorModifiersTags"))
    @BehaviorModifiersTags.setter
    def BehaviorModifiersTags(self, val): self.BehaviorModifiersTags.set(val)
    @property
    def BehaviorPath(self): return String(self._node.at("BehaviorPath"))
    @BehaviorPath.setter
    def BehaviorPath(self, val): self.BehaviorPath.set(val)
    @property
    def BehaviorState(self): return String(self._node.at("BehaviorState"))
    @BehaviorState.setter
    def BehaviorState(self, val): self.BehaviorState.set(val)
    @property
    def CanBeMaster(self): return Bool(self._node.at("CanBeMaster"))
    @CanBeMaster.setter
    def CanBeMaster(self, val): self.CanBeMaster.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def behaviorScriptData(self): return BehaviorScriptData(self._node.at("behaviorScriptData"))
    @property
    def m_oblivionTimerAfterSuspicious(self): return Float(self._node.at("m_oblivionTimerAfterSuspicious"))
    @m_oblivionTimerAfterSuspicious.setter
    def m_oblivionTimerAfterSuspicious(self, val): self.m_oblivionTimerAfterSuspicious.set(val)
    @property
    def m_oblivionTimerBeforeSuspicious(self): return Float(self._node.at("m_oblivionTimerBeforeSuspicious"))
    @m_oblivionTimerBeforeSuspicious.setter
    def m_oblivionTimerBeforeSuspicious(self, val): self.m_oblivionTimerBeforeSuspicious.set(val)
    @property
    def m_timerBeforeCertain(self): return Float(self._node.at("m_timerBeforeCertain"))
    @m_timerBeforeCertain.setter
    def m_timerBeforeCertain(self, val): self.m_timerBeforeCertain.set(val)
    @property
    def m_timerBeforeSuspicious(self): return Float(self._node.at("m_timerBeforeSuspicious"))
    @m_timerBeforeSuspicious.setter
    def m_timerBeforeSuspicious(self, val): self.m_timerBeforeSuspicious.set(val)
    pass




