
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.SyncTempoMode import *
from entgen.String import *
from entgen.Int import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.SoundEventMapping import *
from entgen.String import *
from entgen.String import *
from entgen.String import *


class SoundEmitterGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/SoundEmitterGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(SoundEmitterGD.schema_name))
    @property
    def ActivationDistance(self): return Float(self._node.at("ActivationDistance"))
    @ActivationDistance.setter
    def ActivationDistance(self, val): self.ActivationDistance.set(val)
    @property
    def ActivationSound(self): return (lambda n: PrimArray(String, n))(self._node.at("ActivationSound"))
    @ActivationSound.setter
    def ActivationSound(self, val): self.ActivationSound.set(val)
    @property
    def ActivationSync(self): return SyncTempoMode(self._node.at("ActivationSync"))
    @ActivationSync.setter
    def ActivationSync(self, val): self.ActivationSync.set(val)
    @property
    def AuxSend(self): return String(self._node.at("AuxSend"))
    @AuxSend.setter
    def AuxSend(self, val): self.AuxSend.set(val)
    @property
    def Bank(self): return (lambda n: PrimArray(String, n))(self._node.at("Bank"))
    @Bank.setter
    def Bank(self, val): self.Bank.set(val)
    @property
    def BoidRadius(self): return Float(self._node.at("BoidRadius"))
    @BoidRadius.setter
    def BoidRadius(self, val): self.BoidRadius.set(val)
    @property
    def BoidRadiusToInnerEdgeRatio(self): return Float(self._node.at("BoidRadiusToInnerEdgeRatio"))
    @BoidRadiusToInnerEdgeRatio.setter
    def BoidRadiusToInnerEdgeRatio(self, val): self.BoidRadiusToInnerEdgeRatio.set(val)
    @property
    def BoidRadiusToOuterEdgeRatio(self): return Float(self._node.at("BoidRadiusToOuterEdgeRatio"))
    @BoidRadiusToOuterEdgeRatio.setter
    def BoidRadiusToOuterEdgeRatio(self, val): self.BoidRadiusToOuterEdgeRatio.set(val)
    @property
    def BoidRealPositionComputation(self): return Bool(self._node.at("BoidRealPositionComputation"))
    @BoidRealPositionComputation.setter
    def BoidRealPositionComputation(self, val): self.BoidRealPositionComputation.set(val)
    @property
    def CreatureType(self): return String(self._node.at("CreatureType"))
    @CreatureType.setter
    def CreatureType(self, val): self.CreatureType.set(val)
    @property
    def Echoes(self): return Bool(self._node.at("Echoes"))
    @Echoes.setter
    def Echoes(self, val): self.Echoes.set(val)
    @property
    def EchoesSend(self): return Float(self._node.at("EchoesSend"))
    @EchoesSend.setter
    def EchoesSend(self, val): self.EchoesSend.set(val)
    @property
    def EventDistance(self): return Float(self._node.at("EventDistance"))
    @EventDistance.setter
    def EventDistance(self, val): self.EventDistance.set(val)
    @property
    def EventMapping(self): return SoundEventMapping(self._node.at("EventMapping"))
    @property
    def ExplicitEventMapping(self): return (lambda n: Map(str, String, n))(self._node.at("ExplicitEventMapping"))
    @property
    def InEvents(self): return (lambda n: PrimArray(String, n))(self._node.at("InEvents"))
    @InEvents.setter
    def InEvents(self, val): self.InEvents.set(val)
    @property
    def OutEvents(self): return (lambda n: PrimArray(String, n))(self._node.at("OutEvents"))
    @OutEvents.setter
    def OutEvents(self, val): self.OutEvents.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def UnactivationSound(self): return (lambda n: PrimArray(String, n))(self._node.at("UnactivationSound"))
    @UnactivationSound.setter
    def UnactivationSound(self, val): self.UnactivationSound.set(val)
    @property
    def UnactivationSync(self): return SyncTempoMode(self._node.at("UnactivationSync"))
    @UnactivationSync.setter
    def UnactivationSync(self, val): self.UnactivationSync.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def dopplerActivated(self): return Bool(self._node.at("dopplerActivated"))
    @dopplerActivated.setter
    def dopplerActivated(self, val): self.dopplerActivated.set(val)
    @property
    def relativeHeightPriority(self): return Int(self._node.at("relativeHeightPriority"))
    @relativeHeightPriority.setter
    def relativeHeightPriority(self, val): self.relativeHeightPriority.set(val)
    @property
    def sendSoundAreaEvents(self): return Bool(self._node.at("sendSoundAreaEvents"))
    @sendSoundAreaEvents.setter
    def sendSoundAreaEvents(self, val): self.sendSoundAreaEvents.set(val)
    @property
    def waterDeepAltitude(self): return Float(self._node.at("waterDeepAltitude"))
    @waterDeepAltitude.setter
    def waterDeepAltitude(self, val): self.waterDeepAltitude.set(val)
    @property
    def waterPuddleAltitude(self): return Float(self._node.at("waterPuddleAltitude"))
    @waterPuddleAltitude.setter
    def waterPuddleAltitude(self, val): self.waterPuddleAltitude.set(val)
    pass




