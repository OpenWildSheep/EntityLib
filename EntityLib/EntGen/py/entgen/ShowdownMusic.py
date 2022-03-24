
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.SyncTempoMode import *
from entgen.String import *
from entgen.Int import *
from entgen.Float import *
from entgen.ShowdownLayerData import *
from entgen.ShowdownSpeciesAudioData import *

from EntityLibPy import Node

class ShowdownMusic(HelperObject):
    schema_name = "ShowdownMusic"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ShowdownMusic
        return ShowdownMusic(entlib.load_node_file(sourcefile, entlib.get_schema(ShowdownMusic.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ShowdownMusic
        return ShowdownMusic(entlib.make_node(ShowdownMusic.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AfterEpicCoolDown(self):  # type: ()->Float
        return Float(self._node.at("AfterEpicCoolDown"))
    @AfterEpicCoolDown.setter
    def AfterEpicCoolDown(self, val): self.AfterEpicCoolDown.set(val)
    @property
    def CloseRange(self):  # type: ()->Float
        return Float(self._node.at("CloseRange"))
    @CloseRange.setter
    def CloseRange(self, val): self.CloseRange.set(val)
    @property
    def CoolDownBeforeStop(self):  # type: ()->Float
        return Float(self._node.at("CoolDownBeforeStop"))
    @CoolDownBeforeStop.setter
    def CoolDownBeforeStop(self, val): self.CoolDownBeforeStop.set(val)
    @property
    def EventsPrefix(self):  # type: ()->String
        return String(self._node.at("EventsPrefix"))
    @EventsPrefix.setter
    def EventsPrefix(self, val): self.EventsPrefix.set(val)
    @property
    def IntensityCountMax(self):  # type: ()->Int
        return Int(self._node.at("IntensityCountMax"))
    @IntensityCountMax.setter
    def IntensityCountMax(self, val): self.IntensityCountMax.set(val)
    @property
    def IntensityCountRatio(self):  # type: ()->Float
        return Float(self._node.at("IntensityCountRatio"))
    @IntensityCountRatio.setter
    def IntensityCountRatio(self, val): self.IntensityCountRatio.set(val)
    @property
    def IntensityDistanceRatio(self):  # type: ()->Float
        return Float(self._node.at("IntensityDistanceRatio"))
    @IntensityDistanceRatio.setter
    def IntensityDistanceRatio(self, val): self.IntensityDistanceRatio.set(val)
    @property
    def IntensityRTPC(self):  # type: ()->String
        return String(self._node.at("IntensityRTPC"))
    @IntensityRTPC.setter
    def IntensityRTPC(self, val): self.IntensityRTPC.set(val)
    @property
    def Layers(self):  # type: ()->ShowdownLayerData
        return ShowdownLayerData(self._node.at("Layers"))
    @property
    def MostSignificantCreatureDistanceRTPC(self):  # type: ()->String
        return String(self._node.at("MostSignificantCreatureDistanceRTPC"))
    @MostSignificantCreatureDistanceRTPC.setter
    def MostSignificantCreatureDistanceRTPC(self, val): self.MostSignificantCreatureDistanceRTPC.set(val)
    @property
    def MusicSourceAnchorRadius(self):  # type: ()->Float
        return Float(self._node.at("MusicSourceAnchorRadius"))
    @MusicSourceAnchorRadius.setter
    def MusicSourceAnchorRadius(self, val): self.MusicSourceAnchorRadius.set(val)
    @property
    def MusicSourceDamping(self):  # type: ()->Float
        return Float(self._node.at("MusicSourceDamping"))
    @MusicSourceDamping.setter
    def MusicSourceDamping(self, val): self.MusicSourceDamping.set(val)
    @property
    def PlayerInvolvedScoreFactor(self):  # type: ()->Float
        return Float(self._node.at("PlayerInvolvedScoreFactor"))
    @PlayerInvolvedScoreFactor.setter
    def PlayerInvolvedScoreFactor(self, val): self.PlayerInvolvedScoreFactor.set(val)
    @property
    def PlayerUninvolvedDistanceFactor(self):  # type: ()->Float
        return Float(self._node.at("PlayerUninvolvedDistanceFactor"))
    @PlayerUninvolvedDistanceFactor.setter
    def PlayerUninvolvedDistanceFactor(self, val): self.PlayerUninvolvedDistanceFactor.set(val)
    @property
    def RTPC_2D3D(self):  # type: ()->String
        return String(self._node.at("RTPC_2D3D"))
    @RTPC_2D3D.setter
    def RTPC_2D3D(self, val): self.RTPC_2D3D.set(val)
    @property
    def RTPC_PlayersInFight(self):  # type: ()->String
        return String(self._node.at("RTPC_PlayersInFight"))
    @RTPC_PlayersInFight.setter
    def RTPC_PlayersInFight(self, val): self.RTPC_PlayersInFight.set(val)
    @property
    def ShowdownBlueSideState(self):  # type: ()->String
        return String(self._node.at("ShowdownBlueSideState"))
    @ShowdownBlueSideState.setter
    def ShowdownBlueSideState(self, val): self.ShowdownBlueSideState.set(val)
    @property
    def ShowdownMusBank(self):  # type: ()->String
        return String(self._node.at("ShowdownMusBank"))
    @ShowdownMusBank.setter
    def ShowdownMusBank(self, val): self.ShowdownMusBank.set(val)
    @property
    def ShowdownMusState(self):  # type: ()->String
        return String(self._node.at("ShowdownMusState"))
    @ShowdownMusState.setter
    def ShowdownMusState(self, val): self.ShowdownMusState.set(val)
    @property
    def ShowdownNeutralSideState(self):  # type: ()->String
        return String(self._node.at("ShowdownNeutralSideState"))
    @ShowdownNeutralSideState.setter
    def ShowdownNeutralSideState(self, val): self.ShowdownNeutralSideState.set(val)
    @property
    def ShowdownRedSideState(self):  # type: ()->String
        return String(self._node.at("ShowdownRedSideState"))
    @ShowdownRedSideState.setter
    def ShowdownRedSideState(self, val): self.ShowdownRedSideState.set(val)
    @property
    def ShowdownSideState(self):  # type: ()->String
        return String(self._node.at("ShowdownSideState"))
    @ShowdownSideState.setter
    def ShowdownSideState(self, val): self.ShowdownSideState.set(val)
    @property
    def ShowdownTypeState(self):  # type: ()->String
        return String(self._node.at("ShowdownTypeState"))
    @ShowdownTypeState.setter
    def ShowdownTypeState(self, val): self.ShowdownTypeState.set(val)
    @property
    def SmoothDistanceRTPCs(self):  # type: ()->Float
        return Float(self._node.at("SmoothDistanceRTPCs"))
    @SmoothDistanceRTPCs.setter
    def SmoothDistanceRTPCs(self, val): self.SmoothDistanceRTPCs.set(val)
    @property
    def SmoothTime(self):  # type: ()->Float
        return Float(self._node.at("SmoothTime"))
    @SmoothTime.setter
    def SmoothTime(self, val): self.SmoothTime.set(val)
    @property
    def SpeciesToAudioCategory(self):  # type: ()->Array[ShowdownSpeciesAudioData]
        return (lambda n: Array(ShowdownSpeciesAudioData, n))(self._node.at("SpeciesToAudioCategory"))
    @property
    def SynchronizationMode(self):  # type: ()->SyncTempoMode
        return SyncTempoMode(self._node.at("SynchronizationMode"))
    @SynchronizationMode.setter
    def SynchronizationMode(self, val): self.SynchronizationMode.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




