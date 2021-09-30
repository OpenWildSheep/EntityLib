
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Vector2 import *
from entgen.ActorCategory import *
from entgen.String import *


class ConditionalRigidityAttribute_Conditions(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ConditionalRigidityAttribute::Conditions"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(ConditionalRigidityAttribute_Conditions.schema_name))
    @property
    def ActorCategories(self): return (lambda n: PrimArray(ActorCategory, n))(self._node.at("ActorCategories"))
    @ActorCategories.setter
    def ActorCategories(self, val): self.ActorCategories.set(val)
    @property
    def ActorStates(self): return (lambda n: PrimArray(String, n))(self._node.at("ActorStates"))
    @ActorStates.setter
    def ActorStates(self, val): self.ActorStates.set(val)
    @property
    def AngularVelocityFactorRange(self): return Vector2(self._node.at("AngularVelocityFactorRange"))
    @AngularVelocityFactorRange.setter
    def AngularVelocityFactorRange(self, val): self.AngularVelocityFactorRange.set(val)
    @property
    def DirectionDotRange(self): return Vector2(self._node.at("DirectionDotRange"))
    @DirectionDotRange.setter
    def DirectionDotRange(self, val): self.DirectionDotRange.set(val)
    @property
    def LinearVelocityFactorRange(self): return Vector2(self._node.at("LinearVelocityFactorRange"))
    @LinearVelocityFactorRange.setter
    def LinearVelocityFactorRange(self, val): self.LinearVelocityFactorRange.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




