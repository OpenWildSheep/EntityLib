
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.ActionMode import *
from entgen.BoidGoalMode import *
from entgen.LocomotionMode import *
from entgen.SpeedMode import *
from entgen.StyleMode import *
from entgen.String import *
from entgen.Int import *
from entgen.Bool import *
from entgen.Color import *
from entgen.Float import *
from entgen.BoidSpeedMaxData import *

from EntityLibPy import Node

class BoidParams(HelperObject):
    schema_name = "BoidParams"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BoidParams
        return BoidParams(entlib.load_node_file(sourcefile, entlib.get_schema(BoidParams.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BoidParams
        return BoidParams(entlib.make_node(BoidParams.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Acceleration(self):  # type: ()->Float
        return Float(self._node.at("Acceleration"))
    @Acceleration.setter
    def Acceleration(self, val): self.Acceleration.set(val)
    @property
    def Action(self):  # type: ()->ActionMode
        return ActionMode(self._node.at("Action"))
    @Action.setter
    def Action(self, val): self.Action.set(val)
    @property
    def ActionSecondary(self):  # type: ()->ActionMode
        return ActionMode(self._node.at("ActionSecondary"))
    @ActionSecondary.setter
    def ActionSecondary(self, val): self.ActionSecondary.set(val)
    @property
    def AlignmentDistance(self):  # type: ()->Float
        return Float(self._node.at("AlignmentDistance"))
    @AlignmentDistance.setter
    def AlignmentDistance(self, val): self.AlignmentDistance.set(val)
    @property
    def AlignmentStrength(self):  # type: ()->Float
        return Float(self._node.at("AlignmentStrength"))
    @AlignmentStrength.setter
    def AlignmentStrength(self, val): self.AlignmentStrength.set(val)
    @property
    def AllowMerge(self):  # type: ()->Bool
        return Bool(self._node.at("AllowMerge"))
    @AllowMerge.setter
    def AllowMerge(self, val): self.AllowMerge.set(val)
    @property
    def AngularSlerpCoeff(self):  # type: ()->Float
        return Float(self._node.at("AngularSlerpCoeff"))
    @AngularSlerpCoeff.setter
    def AngularSlerpCoeff(self, val): self.AngularSlerpCoeff.set(val)
    @property
    def AngularSpeedMax(self):  # type: ()->Float
        return Float(self._node.at("AngularSpeedMax"))
    @AngularSpeedMax.setter
    def AngularSpeedMax(self, val): self.AngularSpeedMax.set(val)
    @property
    def AnimFromStart(self):  # type: ()->Bool
        return Bool(self._node.at("AnimFromStart"))
    @AnimFromStart.setter
    def AnimFromStart(self, val): self.AnimFromStart.set(val)
    @property
    def BlockProcess(self):  # type: ()->Bool
        return Bool(self._node.at("BlockProcess"))
    @BlockProcess.setter
    def BlockProcess(self, val): self.BlockProcess.set(val)
    @property
    def ClampVerticalAngle(self):  # type: ()->Bool
        return Bool(self._node.at("ClampVerticalAngle"))
    @ClampVerticalAngle.setter
    def ClampVerticalAngle(self, val): self.ClampVerticalAngle.set(val)
    @property
    def CohesionStrength(self):  # type: ()->Float
        return Float(self._node.at("CohesionStrength"))
    @CohesionStrength.setter
    def CohesionStrength(self, val): self.CohesionStrength.set(val)
    @property
    def DragForce(self):  # type: ()->Float
        return Float(self._node.at("DragForce"))
    @DragForce.setter
    def DragForce(self, val): self.DragForce.set(val)
    @property
    def EntityDistance(self):  # type: ()->Float
        return Float(self._node.at("EntityDistance"))
    @EntityDistance.setter
    def EntityDistance(self, val): self.EntityDistance.set(val)
    @property
    def FlapBehavior(self):  # type: ()->Bool
        return Bool(self._node.at("FlapBehavior"))
    @FlapBehavior.setter
    def FlapBehavior(self, val): self.FlapBehavior.set(val)
    @property
    def FlattenZFactorLeaves(self):  # type: ()->Float
        return Float(self._node.at("FlattenZFactorLeaves"))
    @FlattenZFactorLeaves.setter
    def FlattenZFactorLeaves(self, val): self.FlattenZFactorLeaves.set(val)
    @property
    def FlattenZFactorRoots(self):  # type: ()->Float
        return Float(self._node.at("FlattenZFactorRoots"))
    @FlattenZFactorRoots.setter
    def FlattenZFactorRoots(self, val): self.FlattenZFactorRoots.set(val)
    @property
    def FollowEmitterStrength(self):  # type: ()->Float
        return Float(self._node.at("FollowEmitterStrength"))
    @FollowEmitterStrength.setter
    def FollowEmitterStrength(self, val): self.FollowEmitterStrength.set(val)
    @property
    def GoalMode(self):  # type: ()->BoidGoalMode
        return BoidGoalMode(self._node.at("GoalMode"))
    @GoalMode.setter
    def GoalMode(self, val): self.GoalMode.set(val)
    @property
    def GroundRepulse(self):  # type: ()->Bool
        return Bool(self._node.at("GroundRepulse"))
    @GroundRepulse.setter
    def GroundRepulse(self, val): self.GroundRepulse.set(val)
    @property
    def GroundRepulseHeight(self):  # type: ()->Float
        return Float(self._node.at("GroundRepulseHeight"))
    @GroundRepulseHeight.setter
    def GroundRepulseHeight(self, val): self.GroundRepulseHeight.set(val)
    @property
    def GroundRepulseStrength(self):  # type: ()->Float
        return Float(self._node.at("GroundRepulseStrength"))
    @GroundRepulseStrength.setter
    def GroundRepulseStrength(self, val): self.GroundRepulseStrength.set(val)
    @property
    def InitialInertiaFactor(self):  # type: ()->Float
        return Float(self._node.at("InitialInertiaFactor"))
    @InitialInertiaFactor.setter
    def InitialInertiaFactor(self, val): self.InitialInertiaFactor.set(val)
    @property
    def InitialInertiaVerticalFactor(self):  # type: ()->Float
        return Float(self._node.at("InitialInertiaVerticalFactor"))
    @InitialInertiaVerticalFactor.setter
    def InitialInertiaVerticalFactor(self, val): self.InitialInertiaVerticalFactor.set(val)
    @property
    def LightBrightness(self):  # type: ()->Float
        return Float(self._node.at("LightBrightness"))
    @LightBrightness.setter
    def LightBrightness(self, val): self.LightBrightness.set(val)
    @property
    def LightColor(self):  # type: ()->Color
        return Color(self._node.at("LightColor"))
    @LightColor.setter
    def LightColor(self, val): self.LightColor.set(val)
    @property
    def Locomotion(self):  # type: ()->LocomotionMode
        return LocomotionMode(self._node.at("Locomotion"))
    @Locomotion.setter
    def Locomotion(self, val): self.Locomotion.set(val)
    @property
    def MaxVerticalAngle(self):  # type: ()->Float
        return Float(self._node.at("MaxVerticalAngle"))
    @MaxVerticalAngle.setter
    def MaxVerticalAngle(self, val): self.MaxVerticalAngle.set(val)
    @property
    def MaxVerticalAngleVariation(self):  # type: ()->Float
        return Float(self._node.at("MaxVerticalAngleVariation"))
    @MaxVerticalAngleVariation.setter
    def MaxVerticalAngleVariation(self, val): self.MaxVerticalAngleVariation.set(val)
    @property
    def NbMaxNewChildren(self):  # type: ()->Int
        return Int(self._node.at("NbMaxNewChildren"))
    @NbMaxNewChildren.setter
    def NbMaxNewChildren(self, val): self.NbMaxNewChildren.set(val)
    @property
    def OnGround(self):  # type: ()->Bool
        return Bool(self._node.at("OnGround"))
    @OnGround.setter
    def OnGround(self, val): self.OnGround.set(val)
    @property
    def RepulsionStrength(self):  # type: ()->Float
        return Float(self._node.at("RepulsionStrength"))
    @RepulsionStrength.setter
    def RepulsionStrength(self, val): self.RepulsionStrength.set(val)
    @property
    def RotateBendFactor(self):  # type: ()->Float
        return Float(self._node.at("RotateBendFactor"))
    @RotateBendFactor.setter
    def RotateBendFactor(self, val): self.RotateBendFactor.set(val)
    @property
    def SightZ(self):  # type: ()->Bool
        return Bool(self._node.at("SightZ"))
    @SightZ.setter
    def SightZ(self, val): self.SightZ.set(val)
    @property
    def SpeedMaxData(self):  # type: ()->Array[BoidSpeedMaxData]
        return (lambda n: Array(BoidSpeedMaxData, n))(self._node.at("SpeedMaxData"))
    @property
    def SpeedMode(self):  # type: ()->SpeedMode
        return SpeedMode(self._node.at("SpeedMode"))
    @SpeedMode.setter
    def SpeedMode(self, val): self.SpeedMode.set(val)
    @property
    def SpeedRandomMultiplier(self):  # type: ()->Float
        return Float(self._node.at("SpeedRandomMultiplier"))
    @SpeedRandomMultiplier.setter
    def SpeedRandomMultiplier(self, val): self.SpeedRandomMultiplier.set(val)
    @property
    def StyleMode(self):  # type: ()->StyleMode
        return StyleMode(self._node.at("StyleMode"))
    @StyleMode.setter
    def StyleMode(self, val): self.StyleMode.set(val)
    @property
    def UpdateForceFactor(self):  # type: ()->Float
        return Float(self._node.at("UpdateForceFactor"))
    @UpdateForceFactor.setter
    def UpdateForceFactor(self, val): self.UpdateForceFactor.set(val)
    @property
    def UpdateInertiaFactor(self):  # type: ()->Float
        return Float(self._node.at("UpdateInertiaFactor"))
    @UpdateInertiaFactor.setter
    def UpdateInertiaFactor(self, val): self.UpdateInertiaFactor.set(val)
    @property
    def VerticalMasterPositionOffset(self):  # type: ()->Float
        return Float(self._node.at("VerticalMasterPositionOffset"))
    @VerticalMasterPositionOffset.setter
    def VerticalMasterPositionOffset(self, val): self.VerticalMasterPositionOffset.set(val)
    @property
    def VisibilityStateFrameDelay(self):  # type: ()->Int
        return Int(self._node.at("VisibilityStateFrameDelay"))
    @VisibilityStateFrameDelay.setter
    def VisibilityStateFrameDelay(self, val): self.VisibilityStateFrameDelay.set(val)
    @property
    def Visible(self):  # type: ()->Bool
        return Bool(self._node.at("Visible"))
    @Visible.setter
    def Visible(self, val): self.Visible.set(val)
    @property
    def VisualScaleMultiplierAtStartup(self):  # type: ()->Float
        return Float(self._node.at("VisualScaleMultiplierAtStartup"))
    @VisualScaleMultiplierAtStartup.setter
    def VisualScaleMultiplierAtStartup(self, val): self.VisualScaleMultiplierAtStartup.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def _name(self):  # type: ()->String
        return String(self._node.at("_name"))
    @_name.setter
    def _name(self, val): self._name.set(val)
    pass




