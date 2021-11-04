
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Vector2 import *
from entgen.ActorCategory import *
from entgen.String import *

from EntityLibPy import Node

class ConditionalRigidityAttribute_Conditions(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ConditionalRigidityAttribute::Conditions"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ConditionalRigidityAttribute_Conditions
        return ConditionalRigidityAttribute_Conditions(entlib.load_node_file(sourcefile, entlib.get_schema(ConditionalRigidityAttribute_Conditions.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ConditionalRigidityAttribute_Conditions
        return ConditionalRigidityAttribute_Conditions(entlib.make_node(ConditionalRigidityAttribute_Conditions.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ActorCategories(self):  # type: ()->PrimArray[ActorCategory]
        return (lambda n: PrimArray(ActorCategory, n))(self._node.at("ActorCategories"))
    @ActorCategories.setter
    def ActorCategories(self, val): self.ActorCategories.set(val)
    @property
    def ActorStates(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("ActorStates"))
    @ActorStates.setter
    def ActorStates(self, val): self.ActorStates.set(val)
    @property
    def AngularVelocityFactorRange(self):  # type: ()->Vector2
        return Vector2(self._node.at("AngularVelocityFactorRange"))
    @AngularVelocityFactorRange.setter
    def AngularVelocityFactorRange(self, val): self.AngularVelocityFactorRange.set(val)
    @property
    def DirectionDotRange(self):  # type: ()->Vector2
        return Vector2(self._node.at("DirectionDotRange"))
    @DirectionDotRange.setter
    def DirectionDotRange(self, val): self.DirectionDotRange.set(val)
    @property
    def LinearVelocityFactorRange(self):  # type: ()->Vector2
        return Vector2(self._node.at("LinearVelocityFactorRange"))
    @LinearVelocityFactorRange.setter
    def LinearVelocityFactorRange(self, val): self.LinearVelocityFactorRange.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




