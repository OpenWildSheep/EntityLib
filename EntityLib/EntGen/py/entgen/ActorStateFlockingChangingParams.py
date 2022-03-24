
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.ActorStateFlockingChangingParams_Params import *
from entgen.Bool import *

from EntityLibPy import Node

class ActorStateFlockingChangingParams(HelperObject):
    schema_name = "ActorStateFlockingChangingParams"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateFlockingChangingParams
        return ActorStateFlockingChangingParams(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateFlockingChangingParams.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateFlockingChangingParams
        return ActorStateFlockingChangingParams(entlib.make_node(ActorStateFlockingChangingParams.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Params(self):  # type: ()->ActorStateFlockingChangingParams_Params
        return ActorStateFlockingChangingParams_Params(self._node.at("Params"))
    @property
    def ParamsBud(self):  # type: ()->ActorStateFlockingChangingParams_Params
        return ActorStateFlockingChangingParams_Params(self._node.at("ParamsBud"))
    @property
    def ShouldApplyBudParam(self):  # type: ()->Bool
        return Bool(self._node.at("ShouldApplyBudParam"))
    @ShouldApplyBudParam.setter
    def ShouldApplyBudParam(self, val): self.ShouldApplyBudParam.set(val)
    @property
    def ShouldApplyParam(self):  # type: ()->Bool
        return Bool(self._node.at("ShouldApplyParam"))
    @ShouldApplyParam.setter
    def ShouldApplyParam(self, val): self.ShouldApplyParam.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




