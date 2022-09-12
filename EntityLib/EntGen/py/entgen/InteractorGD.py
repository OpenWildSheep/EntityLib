
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.BoneStartPoint import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.ScoreComputation import *
from entgen.String import *

from EntityLibPy import Node

class InteractorGD(HelperObject):
    schema_name = "InteractorGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->InteractorGD
        return InteractorGD(entlib.load_node_file(sourcefile, entlib.get_schema(InteractorGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->InteractorGD
        return InteractorGD(entlib.make_node(InteractorGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BeamBonusPossessScore(self):  # type: ()->Float
        return Float(self._node.at("BeamBonusPossessScore"))
    @BeamBonusPossessScore.setter
    def BeamBonusPossessScore(self, val): self.BeamBonusPossessScore.set(val)
    @property
    def BeamEffectsNames(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("BeamEffectsNames"))
    @BeamEffectsNames.setter
    def BeamEffectsNames(self, val): self.BeamEffectsNames.set(val)
    @property
    def BoneStartPoint(self):  # type: ()->BoneStartPoint
        return BoneStartPoint(self._node.at("BoneStartPoint"))
    @property
    def InteractionScore(self):  # type: ()->ScoreComputation
        return ScoreComputation(self._node.at("InteractionScore"))
    @property
    def MaxBeamRange(self):  # type: ()->Float
        return Float(self._node.at("MaxBeamRange"))
    @MaxBeamRange.setter
    def MaxBeamRange(self, val): self.MaxBeamRange.set(val)
    @property
    def PossessScore(self):  # type: ()->ScoreComputation
        return ScoreComputation(self._node.at("PossessScore"))
    @property
    def RandomSphereCastsAngle(self):  # type: ()->Float
        return Float(self._node.at("RandomSphereCastsAngle"))
    @RandomSphereCastsAngle.setter
    def RandomSphereCastsAngle(self, val): self.RandomSphereCastsAngle.set(val)
    @property
    def RandomSphereCastsNb(self):  # type: ()->Int
        return Int(self._node.at("RandomSphereCastsNb"))
    @RandomSphereCastsNb.setter
    def RandomSphereCastsNb(self, val): self.RandomSphereCastsNb.set(val)
    @property
    def RememberTargetMaxTime(self):  # type: ()->Float
        return Float(self._node.at("RememberTargetMaxTime"))
    @RememberTargetMaxTime.setter
    def RememberTargetMaxTime(self, val): self.RememberTargetMaxTime.set(val)
    @property
    def SphereCastRadius(self):  # type: ()->Float
        return Float(self._node.at("SphereCastRadius"))
    @SphereCastRadius.setter
    def SphereCastRadius(self, val): self.SphereCastRadius.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def UnmountLongPressDuration(self):  # type: ()->Float
        return Float(self._node.at("UnmountLongPressDuration"))
    @UnmountLongPressDuration.setter
    def UnmountLongPressDuration(self, val): self.UnmountLongPressDuration.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




