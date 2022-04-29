
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Bool import *
from entgen.CameraShakeData import *
from entgen.ConstrainedInputData import *
from entgen.Float import *
from entgen.FreezeData import *
from entgen.GameAttackData import *
from entgen.GameBeamSnapData import *
from entgen.GameBiteData import *
from entgen.GameDeathData import *
from entgen.GameFallData import *
from entgen.GameFeetCatchUpData import *
from entgen.GameFluidData import *
from entgen.GameFlyData import *
from entgen.GameImmersionData import *
from entgen.GameLODData import *
from entgen.GamePadNavigationData import *
from entgen.GamePadSpeedBehaviorData import *
from entgen.GameParryData import *
from entgen.GamePropelData import *
from entgen.GameRespawnData import *
from entgen.GameReviveData import *
from entgen.GameShamanVisionData import *
from entgen.GameSlopeData import *
from entgen.GameSnapData import *
from entgen.Manager import *
from entgen.ScaleConverter import *
from entgen.Float import *
from entgen.Size import *
from entgen.Float import *
from entgen.String import *
from entgen.GameImmersionData import *

from EntityLibPy import Node

class GameManager(HelperObject):
    schema_name = "GameManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameManager
        return GameManager(entlib.load_node_file(sourcefile, entlib.get_schema(GameManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameManager
        return GameManager(entlib.make_node(GameManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ActionAttackValidityTime(self):  # type: ()->Float
        return Float(self._node.at("ActionAttackValidityTime"))
    @ActionAttackValidityTime.setter
    def ActionAttackValidityTime(self, val): self.ActionAttackValidityTime.set(val)
    @property
    def AttackData(self):  # type: ()->GameAttackData
        return GameAttackData(self._node.at("AttackData"))
    @property
    def BeamFreezeData(self):  # type: ()->FreezeData
        return FreezeData(self._node.at("BeamFreezeData"))
    @property
    def BeamSnapData(self):  # type: ()->GameBeamSnapData
        return GameBeamSnapData(self._node.at("BeamSnapData"))
    @property
    def BiteData(self):  # type: ()->GameBiteData
        return GameBiteData(self._node.at("BiteData"))
    @property
    def CameraParamsSmoothData(self):  # type: ()->Map[str, Float]
        return (lambda n: Map(str, Float, n))(self._node.at("CameraParamsSmoothData"))
    @property
    def ConstrainedInputData(self):  # type: ()->ConstrainedInputData
        return ConstrainedInputData(self._node.at("ConstrainedInputData"))
    @property
    def DeathData(self):  # type: ()->GameDeathData
        return GameDeathData(self._node.at("DeathData"))
    @property
    def DefaultCameraParamsSmoothValue(self):  # type: ()->Float
        return Float(self._node.at("DefaultCameraParamsSmoothValue"))
    @DefaultCameraParamsSmoothValue.setter
    def DefaultCameraParamsSmoothValue(self, val): self.DefaultCameraParamsSmoothValue.set(val)
    @property
    def DefaultGamePadID(self):  # type: ()->Int
        return Int(self._node.at("DefaultGamePadID"))
    @DefaultGamePadID.setter
    def DefaultGamePadID(self, val): self.DefaultGamePadID.set(val)
    @property
    def EnableSplashScreen(self):  # type: ()->Bool
        return Bool(self._node.at("EnableSplashScreen"))
    @EnableSplashScreen.setter
    def EnableSplashScreen(self, val): self.EnableSplashScreen.set(val)
    @property
    def FallData(self):  # type: ()->GameFallData
        return GameFallData(self._node.at("FallData"))
    @property
    def FeetCatchUpData(self):  # type: ()->GameFeetCatchUpData
        return GameFeetCatchUpData(self._node.at("FeetCatchUpData"))
    @property
    def FluidData(self):  # type: ()->GameFluidData
        return GameFluidData(self._node.at("FluidData"))
    @property
    def FlyData(self):  # type: ()->GameFlyData
        return GameFlyData(self._node.at("FlyData"))
    @property
    def GamePadAimHysteresis(self):  # type: ()->Float
        return Float(self._node.at("GamePadAimHysteresis"))
    @GamePadAimHysteresis.setter
    def GamePadAimHysteresis(self, val): self.GamePadAimHysteresis.set(val)
    @property
    def GamePadAimThreshold(self):  # type: ()->Float
        return Float(self._node.at("GamePadAimThreshold"))
    @GamePadAimThreshold.setter
    def GamePadAimThreshold(self, val): self.GamePadAimThreshold.set(val)
    @property
    def GamePadNavigationData(self):  # type: ()->GamePadNavigationData
        return GamePadNavigationData(self._node.at("GamePadNavigationData"))
    @property
    def GamePadRumbleScale(self):  # type: ()->Float
        return Float(self._node.at("GamePadRumbleScale"))
    @GamePadRumbleScale.setter
    def GamePadRumbleScale(self, val): self.GamePadRumbleScale.set(val)
    @property
    def GamePadSpeedBehaviorData(self):  # type: ()->GamePadSpeedBehaviorData
        return GamePadSpeedBehaviorData(self._node.at("GamePadSpeedBehaviorData"))
    @property
    def GameSpawnFadeInDelay(self):  # type: ()->Float
        return Float(self._node.at("GameSpawnFadeInDelay"))
    @GameSpawnFadeInDelay.setter
    def GameSpawnFadeInDelay(self, val): self.GameSpawnFadeInDelay.set(val)
    @property
    def GameSpawnFadeInDuration(self):  # type: ()->Float
        return Float(self._node.at("GameSpawnFadeInDuration"))
    @GameSpawnFadeInDuration.setter
    def GameSpawnFadeInDuration(self, val): self.GameSpawnFadeInDuration.set(val)
    @property
    def HitShakeData(self):  # type: ()->CameraShakeData
        return CameraShakeData(self._node.at("HitShakeData"))
    @property
    def ImmersionData(self):  # type: ()->Array[GameImmersionData]
        return (lambda n: Array(GameImmersionData, n))(self._node.at("ImmersionData"))
    @property
    def InputCollisionAnticipationLength(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("InputCollisionAnticipationLength"))
    @property
    def InteractionDisplayHysteresis(self):  # type: ()->Float
        return Float(self._node.at("InteractionDisplayHysteresis"))
    @InteractionDisplayHysteresis.setter
    def InteractionDisplayHysteresis(self, val): self.InteractionDisplayHysteresis.set(val)
    @property
    def InteractionPressDuration(self):  # type: ()->Float
        return Float(self._node.at("InteractionPressDuration"))
    @InteractionPressDuration.setter
    def InteractionPressDuration(self, val): self.InteractionPressDuration.set(val)
    @property
    def InteractionScreenViewDistance(self):  # type: ()->Float
        return Float(self._node.at("InteractionScreenViewDistance"))
    @InteractionScreenViewDistance.setter
    def InteractionScreenViewDistance(self, val): self.InteractionScreenViewDistance.set(val)
    @property
    def IntroVideo(self):  # type: ()->String
        return String(self._node.at("IntroVideo"))
    @IntroVideo.setter
    def IntroVideo(self, val): self.IntroVideo.set(val)
    @property
    def LODData(self):  # type: ()->GameLODData
        return GameLODData(self._node.at("LODData"))
    @property
    def LavaImmersionData(self):  # type: ()->GameImmersionData
        return GameImmersionData(self._node.at("LavaImmersionData"))
    @property
    def LockTargetMaxDistance(self):  # type: ()->Float
        return Float(self._node.at("LockTargetMaxDistance"))
    @LockTargetMaxDistance.setter
    def LockTargetMaxDistance(self, val): self.LockTargetMaxDistance.set(val)
    @property
    def LockTargetScreenViewDistance(self):  # type: ()->Float
        return Float(self._node.at("LockTargetScreenViewDistance"))
    @LockTargetScreenViewDistance.setter
    def LockTargetScreenViewDistance(self, val): self.LockTargetScreenViewDistance.set(val)
    @property
    def Long_Press_Duration(self):  # type: ()->Float
        return Float(self._node.at("Long Press Duration"))
    @Long_Press_Duration.setter
    def Long_Press_Duration(self, val): self.Long_Press_Duration.set(val)
    @property
    def MountOnlyOnFollower(self):  # type: ()->Bool
        return Bool(self._node.at("MountOnlyOnFollower"))
    @MountOnlyOnFollower.setter
    def MountOnlyOnFollower(self, val): self.MountOnlyOnFollower.set(val)
    @property
    def ParryData(self):  # type: ()->GameParryData
        return GameParryData(self._node.at("ParryData"))
    @property
    def PropelData(self):  # type: ()->GamePropelData
        return GamePropelData(self._node.at("PropelData"))
    @property
    def RespawnData(self):  # type: ()->GameRespawnData
        return GameRespawnData(self._node.at("RespawnData"))
    @property
    def ReviveData(self):  # type: ()->GameReviveData
        return GameReviveData(self._node.at("ReviveData"))
    @property
    def ShamanVisionData(self):  # type: ()->GameShamanVisionData
        return GameShamanVisionData(self._node.at("ShamanVisionData"))
    @property
    def SlopeData(self):  # type: ()->GameSlopeData
        return GameSlopeData(self._node.at("SlopeData"))
    @property
    def SnapData(self):  # type: ()->GameSnapData
        return GameSnapData(self._node.at("SnapData"))
    @property
    def Sound_TopView_Start(self):  # type: ()->String
        return String(self._node.at("Sound_TopView_Start"))
    @Sound_TopView_Start.setter
    def Sound_TopView_Start(self, val): self.Sound_TopView_Start.set(val)
    @property
    def Sound_TopView_Stop(self):  # type: ()->String
        return String(self._node.at("Sound_TopView_Stop"))
    @Sound_TopView_Stop.setter
    def Sound_TopView_Stop(self, val): self.Sound_TopView_Stop.set(val)
    @property
    def SpeedMaxInUndergroundCavity(self):  # type: ()->Map[SizeEnum, Float]
        return (lambda n: Map(SizeEnum, Float, n))(self._node.at("SpeedMaxInUndergroundCavity"))
    @property
    def SplashScreenSoundStart(self):  # type: ()->String
        return String(self._node.at("SplashScreenSoundStart"))
    @SplashScreenSoundStart.setter
    def SplashScreenSoundStart(self, val): self.SplashScreenSoundStart.set(val)
    @property
    def SplashScreenSoundStop(self):  # type: ()->String
        return String(self._node.at("SplashScreenSoundStop"))
    @SplashScreenSoundStop.setter
    def SplashScreenSoundStop(self, val): self.SplashScreenSoundStop.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def WaterImmersionData(self):  # type: ()->GameImmersionData
        return GameImmersionData(self._node.at("WaterImmersionData"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




