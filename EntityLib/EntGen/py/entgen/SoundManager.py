
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Bool import *
from entgen.Float import *
from entgen.Manager import *
from entgen.SoundManager_BiomeSoundBank import *
from entgen.String import *
from entgen.String import *
from entgen.Specie import *
from entgen.String import *
from entgen.StyleMode import *
from entgen.String import *
from entgen.String import *
from entgen.Color import *
from entgen.String import *
from entgen.SmallActorSpawnPointData import *
from entgen.String import *
from entgen.CreatureTypeData import *
from entgen.GroundTypeData import *

from EntityLibPy import Node

class SoundManager(HelperObject):
    schema_name = "SoundManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SoundManager
        return SoundManager(entlib.load_node_file(sourcefile, entlib.get_schema(SoundManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SoundManager
        return SoundManager(entlib.make_node(SoundManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AmbienceProbeLayerAttenuation(self):  # type: ()->Float
        return Float(self._node.at("AmbienceProbeLayerAttenuation"))
    @AmbienceProbeLayerAttenuation.setter
    def AmbienceProbeLayerAttenuation(self, val): self.AmbienceProbeLayerAttenuation.set(val)
    @property
    def AmbienceProbeLayerCount(self):  # type: ()->Int
        return Int(self._node.at("AmbienceProbeLayerCount"))
    @AmbienceProbeLayerCount.setter
    def AmbienceProbeLayerCount(self, val): self.AmbienceProbeLayerCount.set(val)
    @property
    def AmbienceProbeLayerSpacing(self):  # type: ()->Float
        return Float(self._node.at("AmbienceProbeLayerSpacing"))
    @AmbienceProbeLayerSpacing.setter
    def AmbienceProbeLayerSpacing(self, val): self.AmbienceProbeLayerSpacing.set(val)
    @property
    def AmbienceProbePerLayerCount(self):  # type: ()->Int
        return Int(self._node.at("AmbienceProbePerLayerCount"))
    @AmbienceProbePerLayerCount.setter
    def AmbienceProbePerLayerCount(self, val): self.AmbienceProbePerLayerCount.set(val)
    @property
    def AmbienceTagMapping(self):  # type: ()->Map[str, String]
        return (lambda n: Map(str, String, n))(self._node.at("AmbienceTagMapping"))
    @property
    def BiomeSoundBank(self):  # type: ()->SoundManager_BiomeSoundBank
        return SoundManager_BiomeSoundBank(self._node.at("BiomeSoundBank"))
    @property
    def CallAnswerDelayMax(self):  # type: ()->Float
        return Float(self._node.at("CallAnswerDelayMax"))
    @CallAnswerDelayMax.setter
    def CallAnswerDelayMax(self, val): self.CallAnswerDelayMax.set(val)
    @property
    def CallAnswerDelayMin(self):  # type: ()->Float
        return Float(self._node.at("CallAnswerDelayMin"))
    @CallAnswerDelayMin.setter
    def CallAnswerDelayMin(self, val): self.CallAnswerDelayMin.set(val)
    @property
    def CallDistance(self):  # type: ()->Float
        return Float(self._node.at("CallDistance"))
    @CallDistance.setter
    def CallDistance(self, val): self.CallDistance.set(val)
    @property
    def ClassStyleToHitActive(self):  # type: ()->Map[StyleModeEnum, String]
        return (lambda n: Map(StyleModeEnum, String, n))(self._node.at("ClassStyleToHitActive"))
    @property
    def CreatureType(self):  # type: ()->Array[CreatureTypeData]
        return (lambda n: Array(CreatureTypeData, n))(self._node.at("CreatureType"))
    @property
    def DefaultAmbiantBank(self):  # type: ()->String
        return String(self._node.at("DefaultAmbiantBank"))
    @DefaultAmbiantBank.setter
    def DefaultAmbiantBank(self, val): self.DefaultAmbiantBank.set(val)
    @property
    def DefaultAmbiantEvent(self):  # type: ()->String
        return String(self._node.at("DefaultAmbiantEvent"))
    @DefaultAmbiantEvent.setter
    def DefaultAmbiantEvent(self, val): self.DefaultAmbiantEvent.set(val)
    @property
    def DisplayListener(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayListener"))
    @DisplayListener.setter
    def DisplayListener(self, val): self.DisplayListener.set(val)
    @property
    def EchoEntityNames(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("EchoEntityNames"))
    @EchoEntityNames.setter
    def EchoEntityNames(self, val): self.EchoEntityNames.set(val)
    @property
    def Enabled(self):  # type: ()->Bool
        return Bool(self._node.at("Enabled"))
    @Enabled.setter
    def Enabled(self, val): self.Enabled.set(val)
    @property
    def GroundSFX(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("GroundSFX"))
    @GroundSFX.setter
    def GroundSFX(self, val): self.GroundSFX.set(val)
    @property
    def GroundTypeWater(self):  # type: ()->String
        return String(self._node.at("GroundTypeWater"))
    @GroundTypeWater.setter
    def GroundTypeWater(self, val): self.GroundTypeWater.set(val)
    @property
    def GroundTypeWaterDeep(self):  # type: ()->String
        return String(self._node.at("GroundTypeWaterDeep"))
    @GroundTypeWaterDeep.setter
    def GroundTypeWaterDeep(self, val): self.GroundTypeWaterDeep.set(val)
    @property
    def GroundTypeWaterPuddle(self):  # type: ()->String
        return String(self._node.at("GroundTypeWaterPuddle"))
    @GroundTypeWaterPuddle.setter
    def GroundTypeWaterPuddle(self, val): self.GroundTypeWaterPuddle.set(val)
    @property
    def GroundTypes(self):  # type: ()->Array[GroundTypeData]
        return (lambda n: Array(GroundTypeData, n))(self._node.at("GroundTypes"))
    @property
    def HitIntensityHigh(self):  # type: ()->Float
        return Float(self._node.at("HitIntensityHigh"))
    @HitIntensityHigh.setter
    def HitIntensityHigh(self, val): self.HitIntensityHigh.set(val)
    @property
    def HitIntensityLow(self):  # type: ()->Float
        return Float(self._node.at("HitIntensityLow"))
    @HitIntensityLow.setter
    def HitIntensityLow(self, val): self.HitIntensityLow.set(val)
    @property
    def InWaterEvent(self):  # type: ()->String
        return String(self._node.at("InWaterEvent"))
    @InWaterEvent.setter
    def InWaterEvent(self, val): self.InWaterEvent.set(val)
    @property
    def ListenerDistanceFromPlayer(self):  # type: ()->Float
        return Float(self._node.at("ListenerDistanceFromPlayer"))
    @ListenerDistanceFromPlayer.setter
    def ListenerDistanceFromPlayer(self, val): self.ListenerDistanceFromPlayer.set(val)
    @property
    def ListenerOnFreeCam(self):  # type: ()->Bool
        return Bool(self._node.at("ListenerOnFreeCam"))
    @ListenerOnFreeCam.setter
    def ListenerOnFreeCam(self, val): self.ListenerOnFreeCam.set(val)
    @property
    def OutWaterEvent(self):  # type: ()->String
        return String(self._node.at("OutWaterEvent"))
    @OutWaterEvent.setter
    def OutWaterEvent(self, val): self.OutWaterEvent.set(val)
    @property
    def RTPC_3DFrontBack(self):  # type: ()->String
        return String(self._node.at("RTPC_3DFrontBack"))
    @RTPC_3DFrontBack.setter
    def RTPC_3DFrontBack(self, val): self.RTPC_3DFrontBack.set(val)
    @property
    def RTPC_3DLeftRight(self):  # type: ()->String
        return String(self._node.at("RTPC_3DLeftRight"))
    @RTPC_3DLeftRight.setter
    def RTPC_3DLeftRight(self, val): self.RTPC_3DLeftRight.set(val)
    @property
    def RTPC_AbsoluteHeight(self):  # type: ()->String
        return String(self._node.at("RTPC_AbsoluteHeight"))
    @RTPC_AbsoluteHeight.setter
    def RTPC_AbsoluteHeight(self, val): self.RTPC_AbsoluteHeight.set(val)
    @property
    def RTPC_AmbientRegenLevel(self):  # type: ()->String
        return String(self._node.at("RTPC_AmbientRegenLevel"))
    @RTPC_AmbientRegenLevel.setter
    def RTPC_AmbientRegenLevel(self, val): self.RTPC_AmbientRegenLevel.set(val)
    @property
    def RTPC_AngleToListener(self):  # type: ()->String
        return String(self._node.at("RTPC_AngleToListener"))
    @RTPC_AngleToListener.setter
    def RTPC_AngleToListener(self, val): self.RTPC_AngleToListener.set(val)
    @property
    def RTPC_BoidLeavesCount(self):  # type: ()->String
        return String(self._node.at("RTPC_BoidLeavesCount"))
    @RTPC_BoidLeavesCount.setter
    def RTPC_BoidLeavesCount(self, val): self.RTPC_BoidLeavesCount.set(val)
    @property
    def RTPC_CreatureType(self):  # type: ()->String
        return String(self._node.at("RTPC_CreatureType"))
    @RTPC_CreatureType.setter
    def RTPC_CreatureType(self, val): self.RTPC_CreatureType.set(val)
    @property
    def RTPC_DayHour(self):  # type: ()->String
        return String(self._node.at("RTPC_DayHour"))
    @RTPC_DayHour.setter
    def RTPC_DayHour(self, val): self.RTPC_DayHour.set(val)
    @property
    def RTPC_Distance(self):  # type: ()->String
        return String(self._node.at("RTPC_Distance"))
    @RTPC_Distance.setter
    def RTPC_Distance(self, val): self.RTPC_Distance.set(val)
    @property
    def RTPC_DreamFireDistance(self):  # type: ()->String
        return String(self._node.at("RTPC_DreamFireDistance"))
    @RTPC_DreamFireDistance.setter
    def RTPC_DreamFireDistance(self, val): self.RTPC_DreamFireDistance.set(val)
    @property
    def RTPC_EntityAttackVolume(self):  # type: ()->String
        return String(self._node.at("RTPC_EntityAttackVolume"))
    @RTPC_EntityAttackVolume.setter
    def RTPC_EntityAttackVolume(self, val): self.RTPC_EntityAttackVolume.set(val)
    @property
    def RTPC_EntityDoppler(self):  # type: ()->String
        return String(self._node.at("RTPC_EntityDoppler"))
    @RTPC_EntityDoppler.setter
    def RTPC_EntityDoppler(self, val): self.RTPC_EntityDoppler.set(val)
    @property
    def RTPC_EntityHitIntensity(self):  # type: ()->String
        return String(self._node.at("RTPC_EntityHitIntensity"))
    @RTPC_EntityHitIntensity.setter
    def RTPC_EntityHitIntensity(self, val): self.RTPC_EntityHitIntensity.set(val)
    @property
    def RTPC_EntityHitVolume(self):  # type: ()->String
        return String(self._node.at("RTPC_EntityHitVolume"))
    @RTPC_EntityHitVolume.setter
    def RTPC_EntityHitVolume(self, val): self.RTPC_EntityHitVolume.set(val)
    @property
    def RTPC_EntityNodeRegen(self):  # type: ()->String
        return String(self._node.at("RTPC_EntityNodeRegen"))
    @RTPC_EntityNodeRegen.setter
    def RTPC_EntityNodeRegen(self, val): self.RTPC_EntityNodeRegen.set(val)
    @property
    def RTPC_EntityPitch(self):  # type: ()->String
        return String(self._node.at("RTPC_EntityPitch"))
    @RTPC_EntityPitch.setter
    def RTPC_EntityPitch(self, val): self.RTPC_EntityPitch.set(val)
    @property
    def RTPC_EntityRunDuration(self):  # type: ()->String
        return String(self._node.at("RTPC_EntityRunDuration"))
    @RTPC_EntityRunDuration.setter
    def RTPC_EntityRunDuration(self, val): self.RTPC_EntityRunDuration.set(val)
    @property
    def RTPC_EntityScale(self):  # type: ()->String
        return String(self._node.at("RTPC_EntityScale"))
    @RTPC_EntityScale.setter
    def RTPC_EntityScale(self, val): self.RTPC_EntityScale.set(val)
    @property
    def RTPC_EntityShamanVisiblity(self):  # type: ()->String
        return String(self._node.at("RTPC_EntityShamanVisiblity"))
    @RTPC_EntityShamanVisiblity.setter
    def RTPC_EntityShamanVisiblity(self, val): self.RTPC_EntityShamanVisiblity.set(val)
    @property
    def RTPC_EntitySpeed(self):  # type: ()->String
        return String(self._node.at("RTPC_EntitySpeed"))
    @RTPC_EntitySpeed.setter
    def RTPC_EntitySpeed(self, val): self.RTPC_EntitySpeed.set(val)
    @property
    def RTPC_FernProximity(self):  # type: ()->String
        return String(self._node.at("RTPC_FernProximity"))
    @RTPC_FernProximity.setter
    def RTPC_FernProximity(self, val): self.RTPC_FernProximity.set(val)
    @property
    def RTPC_FlowersProximity(self):  # type: ()->String
        return String(self._node.at("RTPC_FlowersProximity"))
    @RTPC_FlowersProximity.setter
    def RTPC_FlowersProximity(self, val): self.RTPC_FlowersProximity.set(val)
    @property
    def RTPC_Fx_Speed(self):  # type: ()->String
        return String(self._node.at("RTPC_Fx_Speed"))
    @RTPC_Fx_Speed.setter
    def RTPC_Fx_Speed(self, val): self.RTPC_Fx_Speed.set(val)
    @property
    def RTPC_HunterDistance(self):  # type: ()->String
        return String(self._node.at("RTPC_HunterDistance"))
    @RTPC_HunterDistance.setter
    def RTPC_HunterDistance(self, val): self.RTPC_HunterDistance.set(val)
    @property
    def RTPC_LocateClosestEntity(self):  # type: ()->String
        return String(self._node.at("RTPC_LocateClosestEntity"))
    @RTPC_LocateClosestEntity.setter
    def RTPC_LocateClosestEntity(self, val): self.RTPC_LocateClosestEntity.set(val)
    @property
    def RTPC_LocateEntityPan(self):  # type: ()->String
        return String(self._node.at("RTPC_LocateEntityPan"))
    @RTPC_LocateEntityPan.setter
    def RTPC_LocateEntityPan(self, val): self.RTPC_LocateEntityPan.set(val)
    @property
    def RTPC_OuterToInnerProximityEdges(self):  # type: ()->String
        return String(self._node.at("RTPC_OuterToInnerProximityEdges"))
    @RTPC_OuterToInnerProximityEdges.setter
    def RTPC_OuterToInnerProximityEdges(self, val): self.RTPC_OuterToInnerProximityEdges.set(val)
    @property
    def RTPC_PCEnergy(self):  # type: ()->String
        return String(self._node.at("RTPC_PCEnergy"))
    @RTPC_PCEnergy.setter
    def RTPC_PCEnergy(self, val): self.RTPC_PCEnergy.set(val)
    @property
    def RTPC_PCLife(self):  # type: ()->String
        return String(self._node.at("RTPC_PCLife"))
    @RTPC_PCLife.setter
    def RTPC_PCLife(self, val): self.RTPC_PCLife.set(val)
    @property
    def RTPC_PCScale(self):  # type: ()->String
        return String(self._node.at("RTPC_PCScale"))
    @RTPC_PCScale.setter
    def RTPC_PCScale(self, val): self.RTPC_PCScale.set(val)
    @property
    def RTPC_PCSpeed(self):  # type: ()->String
        return String(self._node.at("RTPC_PCSpeed"))
    @RTPC_PCSpeed.setter
    def RTPC_PCSpeed(self, val): self.RTPC_PCSpeed.set(val)
    @property
    def RTPC_PcNPC(self):  # type: ()->String
        return String(self._node.at("RTPC_PcNPC"))
    @RTPC_PcNPC.setter
    def RTPC_PcNPC(self, val): self.RTPC_PcNPC.set(val)
    @property
    def RTPC_PlayerAbsoluteHeight(self):  # type: ()->String
        return String(self._node.at("RTPC_PlayerAbsoluteHeight"))
    @RTPC_PlayerAbsoluteHeight.setter
    def RTPC_PlayerAbsoluteHeight(self, val): self.RTPC_PlayerAbsoluteHeight.set(val)
    @property
    def RTPC_PlayerAcceleration(self):  # type: ()->String
        return String(self._node.at("RTPC_PlayerAcceleration"))
    @RTPC_PlayerAcceleration.setter
    def RTPC_PlayerAcceleration(self, val): self.RTPC_PlayerAcceleration.set(val)
    @property
    def RTPC_PlayerRelativeHeight(self):  # type: ()->String
        return String(self._node.at("RTPC_PlayerRelativeHeight"))
    @RTPC_PlayerRelativeHeight.setter
    def RTPC_PlayerRelativeHeight(self, val): self.RTPC_PlayerRelativeHeight.set(val)
    @property
    def RTPC_Progress(self):  # type: ()->String
        return String(self._node.at("RTPC_Progress"))
    @RTPC_Progress.setter
    def RTPC_Progress(self, val): self.RTPC_Progress.set(val)
    @property
    def RTPC_RainIntensity(self):  # type: ()->String
        return String(self._node.at("RTPC_RainIntensity"))
    @RTPC_RainIntensity.setter
    def RTPC_RainIntensity(self, val): self.RTPC_RainIntensity.set(val)
    @property
    def RTPC_RelativeHeight(self):  # type: ()->String
        return String(self._node.at("RTPC_RelativeHeight"))
    @RTPC_RelativeHeight.setter
    def RTPC_RelativeHeight(self, val): self.RTPC_RelativeHeight.set(val)
    @property
    def RTPC_StormDistance(self):  # type: ()->String
        return String(self._node.at("RTPC_StormDistance"))
    @RTPC_StormDistance.setter
    def RTPC_StormDistance(self, val): self.RTPC_StormDistance.set(val)
    @property
    def RTPC_StormIntensity(self):  # type: ()->String
        return String(self._node.at("RTPC_StormIntensity"))
    @RTPC_StormIntensity.setter
    def RTPC_StormIntensity(self, val): self.RTPC_StormIntensity.set(val)
    @property
    def RTPC_SwampProximity(self):  # type: ()->String
        return String(self._node.at("RTPC_SwampProximity"))
    @RTPC_SwampProximity.setter
    def RTPC_SwampProximity(self, val): self.RTPC_SwampProximity.set(val)
    @property
    def RTPC_UnderwaterCameraActivator(self):  # type: ()->String
        return String(self._node.at("RTPC_UnderwaterCameraActivator"))
    @RTPC_UnderwaterCameraActivator.setter
    def RTPC_UnderwaterCameraActivator(self, val): self.RTPC_UnderwaterCameraActivator.set(val)
    @property
    def RTPC_UnderwaterDepth(self):  # type: ()->String
        return String(self._node.at("RTPC_UnderwaterDepth"))
    @RTPC_UnderwaterDepth.setter
    def RTPC_UnderwaterDepth(self, val): self.RTPC_UnderwaterDepth.set(val)
    @property
    def RainLevelStart(self):  # type: ()->Float
        return Float(self._node.at("RainLevelStart"))
    @RainLevelStart.setter
    def RainLevelStart(self, val): self.RainLevelStart.set(val)
    @property
    def SmallActorSpawnRules(self):  # type: ()->Map[str, SmallActorSpawnPointData]
        return (lambda n: Map(str, SmallActorSpawnPointData, n))(self._node.at("SmallActorSpawnRules"))
    @property
    def SoundTagDataFile(self):  # type: ()->String
        return String(self._node.at("SoundTagDataFile"))
    @SoundTagDataFile.setter
    def SoundTagDataFile(self, val): self.SoundTagDataFile.set(val)
    @property
    def Sound_GameEntity_Stop_All(self):  # type: ()->String
        return String(self._node.at("Sound_GameEntity_Stop_All"))
    @Sound_GameEntity_Stop_All.setter
    def Sound_GameEntity_Stop_All(self, val): self.Sound_GameEntity_Stop_All.set(val)
    @property
    def Sound_GameObject_Dial_Stop(self):  # type: ()->String
        return String(self._node.at("Sound_GameObject_Dial_Stop"))
    @Sound_GameObject_Dial_Stop.setter
    def Sound_GameObject_Dial_Stop(self, val): self.Sound_GameObject_Dial_Stop.set(val)
    @property
    def Sound_Game_Pause_All(self):  # type: ()->String
        return String(self._node.at("Sound_Game_Pause_All"))
    @Sound_Game_Pause_All.setter
    def Sound_Game_Pause_All(self, val): self.Sound_Game_Pause_All.set(val)
    @property
    def Sound_Game_Resume_All(self):  # type: ()->String
        return String(self._node.at("Sound_Game_Resume_All"))
    @Sound_Game_Resume_All.setter
    def Sound_Game_Resume_All(self, val): self.Sound_Game_Resume_All.set(val)
    @property
    def SoundbankEventDataFile(self):  # type: ()->String
        return String(self._node.at("SoundbankEventDataFile"))
    @SoundbankEventDataFile.setter
    def SoundbankEventDataFile(self, val): self.SoundbankEventDataFile.set(val)
    @property
    def SpeciesToHitActive(self):  # type: ()->Map[SpecieEnum, String]
        return (lambda n: Map(SpecieEnum, String, n))(self._node.at("SpeciesToHitActive"))
    @property
    def StateId_MainBiomeType(self):  # type: ()->String
        return String(self._node.at("StateId_MainBiomeType"))
    @StateId_MainBiomeType.setter
    def StateId_MainBiomeType(self, val): self.StateId_MainBiomeType.set(val)
    @property
    def StateId_RainLevel(self):  # type: ()->String
        return String(self._node.at("StateId_RainLevel"))
    @StateId_RainLevel.setter
    def StateId_RainLevel(self, val): self.StateId_RainLevel.set(val)
    @property
    def State_NoRain(self):  # type: ()->String
        return String(self._node.at("State_NoRain"))
    @State_NoRain.setter
    def State_NoRain(self, val): self.State_NoRain.set(val)
    @property
    def State_Rain(self):  # type: ()->String
        return String(self._node.at("State_Rain"))
    @State_Rain.setter
    def State_Rain(self, val): self.State_Rain.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def SwitchId_Appeau(self):  # type: ()->String
        return String(self._node.at("SwitchId_Appeau"))
    @SwitchId_Appeau.setter
    def SwitchId_Appeau(self, val): self.SwitchId_Appeau.set(val)
    @property
    def SwitchId_EntityState(self):  # type: ()->String
        return String(self._node.at("SwitchId_EntityState"))
    @SwitchId_EntityState.setter
    def SwitchId_EntityState(self, val): self.SwitchId_EntityState.set(val)
    @property
    def SwitchId_GiveOrder_Tone(self):  # type: ()->String
        return String(self._node.at("SwitchId_GiveOrder_Tone"))
    @SwitchId_GiveOrder_Tone.setter
    def SwitchId_GiveOrder_Tone(self, val): self.SwitchId_GiveOrder_Tone.set(val)
    @property
    def SwitchId_GiveOrder_Type(self):  # type: ()->String
        return String(self._node.at("SwitchId_GiveOrder_Type"))
    @SwitchId_GiveOrder_Type.setter
    def SwitchId_GiveOrder_Type(self, val): self.SwitchId_GiveOrder_Type.set(val)
    @property
    def SwitchId_GroundType(self):  # type: ()->String
        return String(self._node.at("SwitchId_GroundType"))
    @SwitchId_GroundType.setter
    def SwitchId_GroundType(self, val): self.SwitchId_GroundType.set(val)
    @property
    def SwitchId_Hit_Active(self):  # type: ()->String
        return String(self._node.at("SwitchId_Hit_Active"))
    @SwitchId_Hit_Active.setter
    def SwitchId_Hit_Active(self, val): self.SwitchId_Hit_Active.set(val)
    @property
    def SwitchId_Hit_Intensity(self):  # type: ()->String
        return String(self._node.at("SwitchId_Hit_Intensity"))
    @SwitchId_Hit_Intensity.setter
    def SwitchId_Hit_Intensity(self, val): self.SwitchId_Hit_Intensity.set(val)
    @property
    def SwitchId_Hit_Style(self):  # type: ()->String
        return String(self._node.at("SwitchId_Hit_Style"))
    @SwitchId_Hit_Style.setter
    def SwitchId_Hit_Style(self, val): self.SwitchId_Hit_Style.set(val)
    @property
    def SwitchId_Level(self):  # type: ()->String
        return String(self._node.at("SwitchId_Level"))
    @SwitchId_Level.setter
    def SwitchId_Level(self, val): self.SwitchId_Level.set(val)
    @property
    def SwitchId_OutfitInteraction(self):  # type: ()->String
        return String(self._node.at("SwitchId_OutfitInteraction"))
    @SwitchId_OutfitInteraction.setter
    def SwitchId_OutfitInteraction(self, val): self.SwitchId_OutfitInteraction.set(val)
    @property
    def SwitchId_VegetType(self):  # type: ()->String
        return String(self._node.at("SwitchId_VegetType"))
    @SwitchId_VegetType.setter
    def SwitchId_VegetType(self, val): self.SwitchId_VegetType.set(val)
    @property
    def SwitchState_EntityState_Attack(self):  # type: ()->String
        return String(self._node.at("SwitchState_EntityState_Attack"))
    @SwitchState_EntityState_Attack.setter
    def SwitchState_EntityState_Attack(self, val): self.SwitchState_EntityState_Attack.set(val)
    @property
    def SwitchState_EntityState_Cold(self):  # type: ()->String
        return String(self._node.at("SwitchState_EntityState_Cold"))
    @SwitchState_EntityState_Cold.setter
    def SwitchState_EntityState_Cold(self, val): self.SwitchState_EntityState_Cold.set(val)
    @property
    def SwitchState_EntityState_Defend(self):  # type: ()->String
        return String(self._node.at("SwitchState_EntityState_Defend"))
    @SwitchState_EntityState_Defend.setter
    def SwitchState_EntityState_Defend(self, val): self.SwitchState_EntityState_Defend.set(val)
    @property
    def SwitchState_EntityState_Examine(self):  # type: ()->String
        return String(self._node.at("SwitchState_EntityState_Examine"))
    @SwitchState_EntityState_Examine.setter
    def SwitchState_EntityState_Examine(self, val): self.SwitchState_EntityState_Examine.set(val)
    @property
    def SwitchState_EntityState_Flee(self):  # type: ()->String
        return String(self._node.at("SwitchState_EntityState_Flee"))
    @SwitchState_EntityState_Flee.setter
    def SwitchState_EntityState_Flee(self, val): self.SwitchState_EntityState_Flee.set(val)
    @property
    def SwitchState_EntityState_Follow(self):  # type: ()->String
        return String(self._node.at("SwitchState_EntityState_Follow"))
    @SwitchState_EntityState_Follow.setter
    def SwitchState_EntityState_Follow(self, val): self.SwitchState_EntityState_Follow.set(val)
    @property
    def SwitchState_EntityState_Hungry(self):  # type: ()->String
        return String(self._node.at("SwitchState_EntityState_Hungry"))
    @SwitchState_EntityState_Hungry.setter
    def SwitchState_EntityState_Hungry(self, val): self.SwitchState_EntityState_Hungry.set(val)
    @property
    def SwitchState_EntityState_Hunt(self):  # type: ()->String
        return String(self._node.at("SwitchState_EntityState_Hunt"))
    @SwitchState_EntityState_Hunt.setter
    def SwitchState_EntityState_Hunt(self, val): self.SwitchState_EntityState_Hunt.set(val)
    @property
    def SwitchState_EntityState_Idle(self):  # type: ()->String
        return String(self._node.at("SwitchState_EntityState_Idle"))
    @SwitchState_EntityState_Idle.setter
    def SwitchState_EntityState_Idle(self, val): self.SwitchState_EntityState_Idle.set(val)
    @property
    def SwitchState_EntityState_Protect(self):  # type: ()->String
        return String(self._node.at("SwitchState_EntityState_Protect"))
    @SwitchState_EntityState_Protect.setter
    def SwitchState_EntityState_Protect(self, val): self.SwitchState_EntityState_Protect.set(val)
    @property
    def SwitchState_EntityState_Sleep(self):  # type: ()->String
        return String(self._node.at("SwitchState_EntityState_Sleep"))
    @SwitchState_EntityState_Sleep.setter
    def SwitchState_EntityState_Sleep(self, val): self.SwitchState_EntityState_Sleep.set(val)
    @property
    def SwitchState_EntityState_Thirst(self):  # type: ()->String
        return String(self._node.at("SwitchState_EntityState_Thirst"))
    @SwitchState_EntityState_Thirst.setter
    def SwitchState_EntityState_Thirst(self, val): self.SwitchState_EntityState_Thirst.set(val)
    @property
    def SwitchState_EntityState_Threat(self):  # type: ()->String
        return String(self._node.at("SwitchState_EntityState_Threat"))
    @SwitchState_EntityState_Threat.setter
    def SwitchState_EntityState_Threat(self, val): self.SwitchState_EntityState_Threat.set(val)
    @property
    def SwitchState_EntityState_Wait(self):  # type: ()->String
        return String(self._node.at("SwitchState_EntityState_Wait"))
    @SwitchState_EntityState_Wait.setter
    def SwitchState_EntityState_Wait(self, val): self.SwitchState_EntityState_Wait.set(val)
    @property
    def SwitchState_GiveOrder_Follow(self):  # type: ()->String
        return String(self._node.at("SwitchState_GiveOrder_Follow"))
    @SwitchState_GiveOrder_Follow.setter
    def SwitchState_GiveOrder_Follow(self, val): self.SwitchState_GiveOrder_Follow.set(val)
    @property
    def SwitchState_GiveOrder_Insistent(self):  # type: ()->String
        return String(self._node.at("SwitchState_GiveOrder_Insistent"))
    @SwitchState_GiveOrder_Insistent.setter
    def SwitchState_GiveOrder_Insistent(self, val): self.SwitchState_GiveOrder_Insistent.set(val)
    @property
    def SwitchState_GiveOrder_Normal(self):  # type: ()->String
        return String(self._node.at("SwitchState_GiveOrder_Normal"))
    @SwitchState_GiveOrder_Normal.setter
    def SwitchState_GiveOrder_Normal(self, val): self.SwitchState_GiveOrder_Normal.set(val)
    @property
    def SwitchState_GiveOrder_Wait(self):  # type: ()->String
        return String(self._node.at("SwitchState_GiveOrder_Wait"))
    @SwitchState_GiveOrder_Wait.setter
    def SwitchState_GiveOrder_Wait(self, val): self.SwitchState_GiveOrder_Wait.set(val)
    @property
    def SwitchState_Level_High(self):  # type: ()->String
        return String(self._node.at("SwitchState_Level_High"))
    @SwitchState_Level_High.setter
    def SwitchState_Level_High(self, val): self.SwitchState_Level_High.set(val)
    @property
    def SwitchState_Level_Low(self):  # type: ()->String
        return String(self._node.at("SwitchState_Level_Low"))
    @SwitchState_Level_Low.setter
    def SwitchState_Level_Low(self, val): self.SwitchState_Level_Low.set(val)
    @property
    def SwitchState_Level_Medium(self):  # type: ()->String
        return String(self._node.at("SwitchState_Level_Medium"))
    @SwitchState_Level_Medium.setter
    def SwitchState_Level_Medium(self, val): self.SwitchState_Level_Medium.set(val)
    @property
    def SwitchState_Level_VeryHigh(self):  # type: ()->String
        return String(self._node.at("SwitchState_Level_VeryHigh"))
    @SwitchState_Level_VeryHigh.setter
    def SwitchState_Level_VeryHigh(self, val): self.SwitchState_Level_VeryHigh.set(val)
    @property
    def Switch_Ground_Prefix(self):  # type: ()->String
        return String(self._node.at("Switch_Ground_Prefix"))
    @Switch_Ground_Prefix.setter
    def Switch_Ground_Prefix(self, val): self.Switch_Ground_Prefix.set(val)
    @property
    def TagColors(self):  # type: ()->Map[str, Color]
        return (lambda n: Map(str, Color, n))(self._node.at("TagColors"))
    @property
    def UnderWaterBank(self):  # type: ()->String
        return String(self._node.at("UnderWaterBank"))
    @UnderWaterBank.setter
    def UnderWaterBank(self, val): self.UnderWaterBank.set(val)
    @property
    def UnderWaterOnPlayer(self):  # type: ()->Bool
        return Bool(self._node.at("UnderWaterOnPlayer"))
    @UnderWaterOnPlayer.setter
    def UnderWaterOnPlayer(self, val): self.UnderWaterOnPlayer.set(val)
    @property
    def UnderwaterOutZone(self):  # type: ()->Float
        return Float(self._node.at("UnderwaterOutZone"))
    @UnderwaterOutZone.setter
    def UnderwaterOutZone(self, val): self.UnderwaterOutZone.set(val)
    @property
    def VegetationTagMapping(self):  # type: ()->Map[str, String]
        return (lambda n: Map(str, String, n))(self._node.at("VegetationTagMapping"))
    @property
    def VerticalUnderWaterOffset(self):  # type: ()->Float
        return Float(self._node.at("VerticalUnderWaterOffset"))
    @VerticalUnderWaterOffset.setter
    def VerticalUnderWaterOffset(self, val): self.VerticalUnderWaterOffset.set(val)
    @property
    def VolumeRTPCScaleFactor(self):  # type: ()->Float
        return Float(self._node.at("VolumeRTPCScaleFactor"))
    @VolumeRTPCScaleFactor.setter
    def VolumeRTPCScaleFactor(self, val): self.VolumeRTPCScaleFactor.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




