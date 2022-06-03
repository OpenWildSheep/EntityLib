
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class PhysicsImpactMakerGD(HelperObject):
    schema_name = "PhysicsImpactMakerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PhysicsImpactMakerGD
        return PhysicsImpactMakerGD(entlib.load_node_file(sourcefile, entlib.get_schema(PhysicsImpactMakerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PhysicsImpactMakerGD
        return PhysicsImpactMakerGD(entlib.make_node(PhysicsImpactMakerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AttackAngle(self):  # type: ()->Float
        return Float(self._node.at("AttackAngle"))
    @AttackAngle.setter
    def AttackAngle(self, val): self.AttackAngle.set(val)
    @property
    def BreakEverything(self):  # type: ()->Bool
        return Bool(self._node.at("BreakEverything"))
    @BreakEverything.setter
    def BreakEverything(self, val): self.BreakEverything.set(val)
    @property
    def DamageAndImpactBySpeed(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("DamageAndImpactBySpeed"))
    @property
    def DamageTag(self):  # type: ()->String
        return String(self._node.at("DamageTag"))
    @DamageTag.setter
    def DamageTag(self, val): self.DamageTag.set(val)
    @property
    def DirectionInfluence(self):  # type: ()->Float
        return Float(self._node.at("DirectionInfluence"))
    @DirectionInfluence.setter
    def DirectionInfluence(self, val): self.DirectionInfluence.set(val)
    @property
    def DirectionUpdateThreshold(self):  # type: ()->Float
        return Float(self._node.at("DirectionUpdateThreshold"))
    @DirectionUpdateThreshold.setter
    def DirectionUpdateThreshold(self, val): self.DirectionUpdateThreshold.set(val)
    @property
    def ForceBySpeed(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("ForceBySpeed"))
    @property
    def HitImpactTag(self):  # type: ()->String
        return String(self._node.at("HitImpactTag"))
    @HitImpactTag.setter
    def HitImpactTag(self, val): self.HitImpactTag.set(val)
    @property
    def Restitution(self):  # type: ()->Float
        return Float(self._node.at("Restitution"))
    @Restitution.setter
    def Restitution(self, val): self.Restitution.set(val)
    @property
    def SmoothedSpeedControlRate(self):  # type: ()->Float
        return Float(self._node.at("SmoothedSpeedControlRate"))
    @SmoothedSpeedControlRate.setter
    def SmoothedSpeedControlRate(self, val): self.SmoothedSpeedControlRate.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




