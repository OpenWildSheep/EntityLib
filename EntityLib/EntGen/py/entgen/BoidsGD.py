
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Bool import *
from entgen.Color import *
from entgen.ComponentGD import *
from entgen.EntityRef import *
from entgen.Float import *

from EntityLibPy import Node

class BoidsGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/BoidsGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BoidsGD
        return BoidsGD(entlib.load_node_file(sourcefile, entlib.get_schema(BoidsGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BoidsGD
        return BoidsGD(entlib.make_node(BoidsGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AffectedByFluid(self):  # type: ()->Bool
        return Bool(self._node.at("AffectedByFluid"))
    @AffectedByFluid.setter
    def AffectedByFluid(self, val): self.AffectedByFluid.set(val)
    @property
    def AllowMerge(self):  # type: ()->Bool
        return Bool(self._node.at("AllowMerge"))
    @AllowMerge.setter
    def AllowMerge(self, val): self.AllowMerge.set(val)
    @property
    def AutoMoveRoot(self):  # type: ()->Bool
        return Bool(self._node.at("AutoMoveRoot"))
    @AutoMoveRoot.setter
    def AutoMoveRoot(self, val): self.AutoMoveRoot.set(val)
    @property
    def BudEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("BudEntityRef"))
    @BudEntityRef.setter
    def BudEntityRef(self, val): self.BudEntityRef.set(val)
    @property
    def BudVisualScaleMax(self):  # type: ()->Float
        return Float(self._node.at("BudVisualScaleMax"))
    @BudVisualScaleMax.setter
    def BudVisualScaleMax(self, val): self.BudVisualScaleMax.set(val)
    @property
    def BudVisualScaleMin(self):  # type: ()->Float
        return Float(self._node.at("BudVisualScaleMin"))
    @BudVisualScaleMin.setter
    def BudVisualScaleMin(self, val): self.BudVisualScaleMin.set(val)
    @property
    def DisplayMaster(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayMaster"))
    @DisplayMaster.setter
    def DisplayMaster(self, val): self.DisplayMaster.set(val)
    @property
    def FlockingAttackDamages(self):  # type: ()->Float
        return Float(self._node.at("FlockingAttackDamages"))
    @FlockingAttackDamages.setter
    def FlockingAttackDamages(self, val): self.FlockingAttackDamages.set(val)
    @property
    def FluidSurfaceHeightOffset(self):  # type: ()->Float
        return Float(self._node.at("FluidSurfaceHeightOffset"))
    @FluidSurfaceHeightOffset.setter
    def FluidSurfaceHeightOffset(self, val): self.FluidSurfaceHeightOffset.set(val)
    @property
    def ForceOutsideWater(self):  # type: ()->Bool
        return Bool(self._node.at("ForceOutsideWater"))
    @ForceOutsideWater.setter
    def ForceOutsideWater(self, val): self.ForceOutsideWater.set(val)
    @property
    def FullEntityPoolRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("FullEntityPoolRef"))
    @FullEntityPoolRef.setter
    def FullEntityPoolRef(self, val): self.FullEntityPoolRef.set(val)
    @property
    def GetBackToFlockingDuration(self):  # type: ()->Float
        return Float(self._node.at("GetBackToFlockingDuration"))
    @GetBackToFlockingDuration.setter
    def GetBackToFlockingDuration(self, val): self.GetBackToFlockingDuration.set(val)
    @property
    def GhostDuration(self):  # type: ()->Float
        return Float(self._node.at("GhostDuration"))
    @GhostDuration.setter
    def GhostDuration(self, val): self.GhostDuration.set(val)
    @property
    def HierarchyDistanceMultiplier(self):  # type: ()->Float
        return Float(self._node.at("HierarchyDistanceMultiplier"))
    @HierarchyDistanceMultiplier.setter
    def HierarchyDistanceMultiplier(self, val): self.HierarchyDistanceMultiplier.set(val)
    @property
    def InitialRadius(self):  # type: ()->Float
        return Float(self._node.at("InitialRadius"))
    @InitialRadius.setter
    def InitialRadius(self, val): self.InitialRadius.set(val)
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
    def MainTargetHeight(self):  # type: ()->Float
        return Float(self._node.at("MainTargetHeight"))
    @MainTargetHeight.setter
    def MainTargetHeight(self, val): self.MainTargetHeight.set(val)
    @property
    def MainTargetRotateDistance(self):  # type: ()->Float
        return Float(self._node.at("MainTargetRotateDistance"))
    @MainTargetRotateDistance.setter
    def MainTargetRotateDistance(self, val): self.MainTargetRotateDistance.set(val)
    @property
    def MainTargetSpeedMultiplier(self):  # type: ()->Float
        return Float(self._node.at("MainTargetSpeedMultiplier"))
    @MainTargetSpeedMultiplier.setter
    def MainTargetSpeedMultiplier(self, val): self.MainTargetSpeedMultiplier.set(val)
    @property
    def MinRegenToWakeUp(self):  # type: ()->Float
        return Float(self._node.at("MinRegenToWakeUp"))
    @MinRegenToWakeUp.setter
    def MinRegenToWakeUp(self, val): self.MinRegenToWakeUp.set(val)
    @property
    def NbAgents(self):  # type: ()->Int
        return Int(self._node.at("NbAgents"))
    @NbAgents.setter
    def NbAgents(self, val): self.NbAgents.set(val)
    @property
    def NbAgentsPerZone(self):  # type: ()->Int
        return Int(self._node.at("NbAgentsPerZone"))
    @NbAgentsPerZone.setter
    def NbAgentsPerZone(self, val): self.NbAgentsPerZone.set(val)
    @property
    def ParamBlock(self):  # type: ()->String
        return String(self._node.at("ParamBlock"))
    @ParamBlock.setter
    def ParamBlock(self, val): self.ParamBlock.set(val)
    @property
    def ParamBudAppear(self):  # type: ()->String
        return String(self._node.at("ParamBudAppear"))
    @ParamBudAppear.setter
    def ParamBudAppear(self, val): self.ParamBudAppear.set(val)
    @property
    def ParamBudOpen(self):  # type: ()->String
        return String(self._node.at("ParamBudOpen"))
    @ParamBudOpen.setter
    def ParamBudOpen(self, val): self.ParamBudOpen.set(val)
    @property
    def ParamHome(self):  # type: ()->String
        return String(self._node.at("ParamHome"))
    @ParamHome.setter
    def ParamHome(self, val): self.ParamHome.set(val)
    @property
    def ParamMove(self):  # type: ()->String
        return String(self._node.at("ParamMove"))
    @ParamMove.setter
    def ParamMove(self, val): self.ParamMove.set(val)
    @property
    def ParamSwim(self):  # type: ()->String
        return String(self._node.at("ParamSwim"))
    @ParamSwim.setter
    def ParamSwim(self, val): self.ParamSwim.set(val)
    @property
    def ParamWakeUp(self):  # type: ()->String
        return String(self._node.at("ParamWakeUp"))
    @ParamWakeUp.setter
    def ParamWakeUp(self, val): self.ParamWakeUp.set(val)
    @property
    def PointCloudSearchRadius(self):  # type: ()->Float
        return Float(self._node.at("PointCloudSearchRadius"))
    @PointCloudSearchRadius.setter
    def PointCloudSearchRadius(self, val): self.PointCloudSearchRadius.set(val)
    @property
    def PointCloudTag(self):  # type: ()->String
        return String(self._node.at("PointCloudTag"))
    @PointCloudTag.setter
    def PointCloudTag(self, val): self.PointCloudTag.set(val)
    @property
    def PresetName(self):  # type: ()->String
        return String(self._node.at("PresetName"))
    @PresetName.setter
    def PresetName(self, val): self.PresetName.set(val)
    @property
    def PresetNameBud(self):  # type: ()->String
        return String(self._node.at("PresetNameBud"))
    @PresetNameBud.setter
    def PresetNameBud(self, val): self.PresetNameBud.set(val)
    @property
    def RegenMaxThreshold(self):  # type: ()->Float
        return Float(self._node.at("RegenMaxThreshold"))
    @RegenMaxThreshold.setter
    def RegenMaxThreshold(self, val): self.RegenMaxThreshold.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def VisualScaleMax(self):  # type: ()->Float
        return Float(self._node.at("VisualScaleMax"))
    @VisualScaleMax.setter
    def VisualScaleMax(self, val): self.VisualScaleMax.set(val)
    @property
    def VisualScaleMin(self):  # type: ()->Float
        return Float(self._node.at("VisualScaleMin"))
    @VisualScaleMin.setter
    def VisualScaleMin(self, val): self.VisualScaleMin.set(val)
    @property
    def WakeUpDuration(self):  # type: ()->Float
        return Float(self._node.at("WakeUpDuration"))
    @WakeUpDuration.setter
    def WakeUpDuration(self, val): self.WakeUpDuration.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




