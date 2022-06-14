
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *

from EntityLibPy import Node

class DebugDisplayFlags(HelperObject):
    schema_name = "DebugDisplayFlags"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->DebugDisplayFlags
        return DebugDisplayFlags(entlib.load_node_file(sourcefile, entlib.get_schema(DebugDisplayFlags.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->DebugDisplayFlags
        return DebugDisplayFlags(entlib.make_node(DebugDisplayFlags.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Activate(self):  # type: ()->Bool
        return Bool(self._node.at("Activate"))
    @Activate.setter
    def Activate(self, val): self.Activate.set(val)
    @property
    def ActiveRTPCHunt(self):  # type: ()->Bool
        return Bool(self._node.at("ActiveRTPCHunt"))
    @ActiveRTPCHunt.setter
    def ActiveRTPCHunt(self, val): self.ActiveRTPCHunt.set(val)
    @property
    def ActiveWeatherSystem(self):  # type: ()->Bool
        return Bool(self._node.at("ActiveWeatherSystem"))
    @ActiveWeatherSystem.setter
    def ActiveWeatherSystem(self, val): self.ActiveWeatherSystem.set(val)
    @property
    def AssertOnPestoErrors(self):  # type: ()->Bool
        return Bool(self._node.at("AssertOnPestoErrors"))
    @AssertOnPestoErrors.setter
    def AssertOnPestoErrors(self, val): self.AssertOnPestoErrors.set(val)
    @property
    def DisplayActorStateArbiter(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayActorStateArbiter"))
    @DisplayActorStateArbiter.setter
    def DisplayActorStateArbiter(self, val): self.DisplayActorStateArbiter.set(val)
    @property
    def DisplayAnalytics(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayAnalytics"))
    @DisplayAnalytics.setter
    def DisplayAnalytics(self, val): self.DisplayAnalytics.set(val)
    @property
    def DisplayAutonomousClan(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayAutonomousClan"))
    @DisplayAutonomousClan.setter
    def DisplayAutonomousClan(self, val): self.DisplayAutonomousClan.set(val)
    @property
    def DisplayAutonomousCreatureList(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayAutonomousCreatureList"))
    @DisplayAutonomousCreatureList.setter
    def DisplayAutonomousCreatureList(self, val): self.DisplayAutonomousCreatureList.set(val)
    @property
    def DisplayAutonomousDecision(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayAutonomousDecision"))
    @DisplayAutonomousDecision.setter
    def DisplayAutonomousDecision(self, val): self.DisplayAutonomousDecision.set(val)
    @property
    def DisplayAutonomousEntityList(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayAutonomousEntityList"))
    @DisplayAutonomousEntityList.setter
    def DisplayAutonomousEntityList(self, val): self.DisplayAutonomousEntityList.set(val)
    @property
    def DisplayAutonomousInfo(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayAutonomousInfo"))
    @DisplayAutonomousInfo.setter
    def DisplayAutonomousInfo(self, val): self.DisplayAutonomousInfo.set(val)
    @property
    def DisplayAutonomousListClan(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayAutonomousListClan"))
    @DisplayAutonomousListClan.setter
    def DisplayAutonomousListClan(self, val): self.DisplayAutonomousListClan.set(val)
    @property
    def DisplayAutonomousLogMessage(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayAutonomousLogMessage"))
    @DisplayAutonomousLogMessage.setter
    def DisplayAutonomousLogMessage(self, val): self.DisplayAutonomousLogMessage.set(val)
    @property
    def DisplayAutonomousMaster(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayAutonomousMaster"))
    @DisplayAutonomousMaster.setter
    def DisplayAutonomousMaster(self, val): self.DisplayAutonomousMaster.set(val)
    @property
    def DisplayAutonomousPhysical(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayAutonomousPhysical"))
    @DisplayAutonomousPhysical.setter
    def DisplayAutonomousPhysical(self, val): self.DisplayAutonomousPhysical.set(val)
    @property
    def DisplayAutonomousPosition(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayAutonomousPosition"))
    @DisplayAutonomousPosition.setter
    def DisplayAutonomousPosition(self, val): self.DisplayAutonomousPosition.set(val)
    @property
    def DisplayAutonomousPredator(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayAutonomousPredator"))
    @DisplayAutonomousPredator.setter
    def DisplayAutonomousPredator(self, val): self.DisplayAutonomousPredator.set(val)
    @property
    def DisplayAutonomousPsychological(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayAutonomousPsychological"))
    @DisplayAutonomousPsychological.setter
    def DisplayAutonomousPsychological(self, val): self.DisplayAutonomousPsychological.set(val)
    @property
    def DisplayAutonomousSound(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayAutonomousSound"))
    @DisplayAutonomousSound.setter
    def DisplayAutonomousSound(self, val): self.DisplayAutonomousSound.set(val)
    @property
    def DisplayAutonomousUnlocked(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayAutonomousUnlocked"))
    @DisplayAutonomousUnlocked.setter
    def DisplayAutonomousUnlocked(self, val): self.DisplayAutonomousUnlocked.set(val)
    @property
    def DisplayBehavior(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayBehavior"))
    @DisplayBehavior.setter
    def DisplayBehavior(self, val): self.DisplayBehavior.set(val)
    @property
    def DisplayBlendShapeDebug(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayBlendShapeDebug"))
    @DisplayBlendShapeDebug.setter
    def DisplayBlendShapeDebug(self, val): self.DisplayBlendShapeDebug.set(val)
    @property
    def DisplayBrainMonitor(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayBrainMonitor"))
    @DisplayBrainMonitor.setter
    def DisplayBrainMonitor(self, val): self.DisplayBrainMonitor.set(val)
    @property
    def DisplayCPU(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayCPU"))
    @DisplayCPU.setter
    def DisplayCPU(self, val): self.DisplayCPU.set(val)
    @property
    def DisplayCompass(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayCompass"))
    @DisplayCompass.setter
    def DisplayCompass(self, val): self.DisplayCompass.set(val)
    @property
    def DisplayComponentCacheDebugger(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayComponentCacheDebugger"))
    @DisplayComponentCacheDebugger.setter
    def DisplayComponentCacheDebugger(self, val): self.DisplayComponentCacheDebugger.set(val)
    @property
    def DisplayComponentsDependencies(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayComponentsDependencies"))
    @DisplayComponentsDependencies.setter
    def DisplayComponentsDependencies(self, val): self.DisplayComponentsDependencies.set(val)
    @property
    def DisplayConnectionWarning(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayConnectionWarning"))
    @DisplayConnectionWarning.setter
    def DisplayConnectionWarning(self, val): self.DisplayConnectionWarning.set(val)
    @property
    def DisplayCreatureListAggressive(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayCreatureListAggressive"))
    @DisplayCreatureListAggressive.setter
    def DisplayCreatureListAggressive(self, val): self.DisplayCreatureListAggressive.set(val)
    @property
    def DisplayCreatureListDanger(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayCreatureListDanger"))
    @DisplayCreatureListDanger.setter
    def DisplayCreatureListDanger(self, val): self.DisplayCreatureListDanger.set(val)
    @property
    def DisplayCreatureListDetection(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayCreatureListDetection"))
    @DisplayCreatureListDetection.setter
    def DisplayCreatureListDetection(self, val): self.DisplayCreatureListDetection.set(val)
    @property
    def DisplayCreatureListDistance(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayCreatureListDistance"))
    @DisplayCreatureListDistance.setter
    def DisplayCreatureListDistance(self, val): self.DisplayCreatureListDistance.set(val)
    @property
    def DisplayCreatureListHelp(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayCreatureListHelp"))
    @DisplayCreatureListHelp.setter
    def DisplayCreatureListHelp(self, val): self.DisplayCreatureListHelp.set(val)
    @property
    def DisplayCreatureListPresence(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayCreatureListPresence"))
    @DisplayCreatureListPresence.setter
    def DisplayCreatureListPresence(self, val): self.DisplayCreatureListPresence.set(val)
    @property
    def DisplayCreatureListSpecie(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayCreatureListSpecie"))
    @DisplayCreatureListSpecie.setter
    def DisplayCreatureListSpecie(self, val): self.DisplayCreatureListSpecie.set(val)
    @property
    def DisplayCreatureListState(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayCreatureListState"))
    @DisplayCreatureListState.setter
    def DisplayCreatureListState(self, val): self.DisplayCreatureListState.set(val)
    @property
    def DisplayCreatureListThreat(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayCreatureListThreat"))
    @DisplayCreatureListThreat.setter
    def DisplayCreatureListThreat(self, val): self.DisplayCreatureListThreat.set(val)
    @property
    def DisplayCreatureListTrust(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayCreatureListTrust"))
    @DisplayCreatureListTrust.setter
    def DisplayCreatureListTrust(self, val): self.DisplayCreatureListTrust.set(val)
    @property
    def DisplayCreatureListVisibility(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayCreatureListVisibility"))
    @DisplayCreatureListVisibility.setter
    def DisplayCreatureListVisibility(self, val): self.DisplayCreatureListVisibility.set(val)
    @property
    def DisplayDecalsDebug(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayDecalsDebug"))
    @DisplayDecalsDebug.setter
    def DisplayDecalsDebug(self, val): self.DisplayDecalsDebug.set(val)
    @property
    def DisplayDistanceTool(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayDistanceTool"))
    @DisplayDistanceTool.setter
    def DisplayDistanceTool(self, val): self.DisplayDistanceTool.set(val)
    @property
    def DisplayDrawDebugFromLastSteppedFrame(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayDrawDebugFromLastSteppedFrame"))
    @DisplayDrawDebugFromLastSteppedFrame.setter
    def DisplayDrawDebugFromLastSteppedFrame(self, val): self.DisplayDrawDebugFromLastSteppedFrame.set(val)
    @property
    def DisplayEnergyPools(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayEnergyPools"))
    @DisplayEnergyPools.setter
    def DisplayEnergyPools(self, val): self.DisplayEnergyPools.set(val)
    @property
    def DisplayEntities(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayEntities"))
    @DisplayEntities.setter
    def DisplayEntities(self, val): self.DisplayEntities.set(val)
    @property
    def DisplayEntitiesWithErrors(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayEntitiesWithErrors"))
    @DisplayEntitiesWithErrors.setter
    def DisplayEntitiesWithErrors(self, val): self.DisplayEntitiesWithErrors.set(val)
    @property
    def DisplayEntityClan(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayEntityClan"))
    @DisplayEntityClan.setter
    def DisplayEntityClan(self, val): self.DisplayEntityClan.set(val)
    @property
    def DisplayEntityDistanceMax(self):  # type: ()->Float
        return Float(self._node.at("DisplayEntityDistanceMax"))
    @DisplayEntityDistanceMax.setter
    def DisplayEntityDistanceMax(self, val): self.DisplayEntityDistanceMax.set(val)
    @property
    def DisplayFPS(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayFPS"))
    @DisplayFPS.setter
    def DisplayFPS(self, val): self.DisplayFPS.set(val)
    @property
    def DisplayGameMaster(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayGameMaster"))
    @DisplayGameMaster.setter
    def DisplayGameMaster(self, val): self.DisplayGameMaster.set(val)
    @property
    def DisplayGamepadStateViewer(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayGamepadStateViewer"))
    @DisplayGamepadStateViewer.setter
    def DisplayGamepadStateViewer(self, val): self.DisplayGamepadStateViewer.set(val)
    @property
    def DisplayGestureMenu(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayGestureMenu"))
    @DisplayGestureMenu.setter
    def DisplayGestureMenu(self, val): self.DisplayGestureMenu.set(val)
    @property
    def DisplayGoToPosition(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayGoToPosition"))
    @DisplayGoToPosition.setter
    def DisplayGoToPosition(self, val): self.DisplayGoToPosition.set(val)
    @property
    def DisplayHeightProbe(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayHeightProbe"))
    @DisplayHeightProbe.setter
    def DisplayHeightProbe(self, val): self.DisplayHeightProbe.set(val)
    @property
    def DisplayHitDebugger(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayHitDebugger"))
    @DisplayHitDebugger.setter
    def DisplayHitDebugger(self, val): self.DisplayHitDebugger.set(val)
    @property
    def DisplayHotSpot(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayHotSpot"))
    @DisplayHotSpot.setter
    def DisplayHotSpot(self, val): self.DisplayHotSpot.set(val)
    @property
    def DisplayHotspotDistanceMax(self):  # type: ()->Float
        return Float(self._node.at("DisplayHotspotDistanceMax"))
    @DisplayHotspotDistanceMax.setter
    def DisplayHotspotDistanceMax(self, val): self.DisplayHotspotDistanceMax.set(val)
    @property
    def DisplayManagersInfos(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayManagersInfos"))
    @DisplayManagersInfos.setter
    def DisplayManagersInfos(self, val): self.DisplayManagersInfos.set(val)
    @property
    def DisplayMaterialBank(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayMaterialBank"))
    @DisplayMaterialBank.setter
    def DisplayMaterialBank(self, val): self.DisplayMaterialBank.set(val)
    @property
    def DisplayMeshRasterizerInfos(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayMeshRasterizerInfos"))
    @DisplayMeshRasterizerInfos.setter
    def DisplayMeshRasterizerInfos(self, val): self.DisplayMeshRasterizerInfos.set(val)
    @property
    def DisplayObjectFilterHistory(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayObjectFilterHistory"))
    @DisplayObjectFilterHistory.setter
    def DisplayObjectFilterHistory(self, val): self.DisplayObjectFilterHistory.set(val)
    @property
    def DisplayOrder(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayOrder"))
    @DisplayOrder.setter
    def DisplayOrder(self, val): self.DisplayOrder.set(val)
    @property
    def DisplayPadEmulator(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayPadEmulator"))
    @DisplayPadEmulator.setter
    def DisplayPadEmulator(self, val): self.DisplayPadEmulator.set(val)
    @property
    def DisplayParticleTool(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayParticleTool"))
    @DisplayParticleTool.setter
    def DisplayParticleTool(self, val): self.DisplayParticleTool.set(val)
    @property
    def DisplayPathSystem(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayPathSystem"))
    @DisplayPathSystem.setter
    def DisplayPathSystem(self, val): self.DisplayPathSystem.set(val)
    @property
    def DisplayPesto(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayPesto"))
    @DisplayPesto.setter
    def DisplayPesto(self, val): self.DisplayPesto.set(val)
    @property
    def DisplayPestoCPUMarkers(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayPestoCPUMarkers"))
    @DisplayPestoCPUMarkers.setter
    def DisplayPestoCPUMarkers(self, val): self.DisplayPestoCPUMarkers.set(val)
    @property
    def DisplayPhysicsPicker(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayPhysicsPicker"))
    @DisplayPhysicsPicker.setter
    def DisplayPhysicsPicker(self, val): self.DisplayPhysicsPicker.set(val)
    @property
    def DisplayPivot(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayPivot"))
    @DisplayPivot.setter
    def DisplayPivot(self, val): self.DisplayPivot.set(val)
    @property
    def DisplayPlayerInteraction(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayPlayerInteraction"))
    @DisplayPlayerInteraction.setter
    def DisplayPlayerInteraction(self, val): self.DisplayPlayerInteraction.set(val)
    @property
    def DisplayPositionPicker(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayPositionPicker"))
    @DisplayPositionPicker.setter
    def DisplayPositionPicker(self, val): self.DisplayPositionPicker.set(val)
    @property
    def DisplayProjectileThrower(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayProjectileThrower"))
    @DisplayProjectileThrower.setter
    def DisplayProjectileThrower(self, val): self.DisplayProjectileThrower.set(val)
    @property
    def DisplayPseudos(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayPseudos"))
    @DisplayPseudos.setter
    def DisplayPseudos(self, val): self.DisplayPseudos.set(val)
    @property
    def DisplayQualityManager(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayQualityManager"))
    @DisplayQualityManager.setter
    def DisplayQualityManager(self, val): self.DisplayQualityManager.set(val)
    @property
    def DisplayRPCCalls(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayRPCCalls"))
    @DisplayRPCCalls.setter
    def DisplayRPCCalls(self, val): self.DisplayRPCCalls.set(val)
    @property
    def DisplayReloadNotifications(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayReloadNotifications"))
    @DisplayReloadNotifications.setter
    def DisplayReloadNotifications(self, val): self.DisplayReloadNotifications.set(val)
    @property
    def DisplaySelectedPestoEntity(self):  # type: ()->Bool
        return Bool(self._node.at("DisplaySelectedPestoEntity"))
    @DisplaySelectedPestoEntity.setter
    def DisplaySelectedPestoEntity(self, val): self.DisplaySelectedPestoEntity.set(val)
    @property
    def DisplayStringHashTranslator(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayStringHashTranslator"))
    @DisplayStringHashTranslator.setter
    def DisplayStringHashTranslator(self, val): self.DisplayStringHashTranslator.set(val)
    @property
    def DisplayTimer(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayTimer"))
    @DisplayTimer.setter
    def DisplayTimer(self, val): self.DisplayTimer.set(val)
    @property
    def DisplayTreesStates(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayTreesStates"))
    @DisplayTreesStates.setter
    def DisplayTreesStates(self, val): self.DisplayTreesStates.set(val)
    @property
    def EditorGuiAllowsComponentsSplitView(self):  # type: ()->Bool
        return Bool(self._node.at("EditorGuiAllowsComponentsSplitView"))
    @EditorGuiAllowsComponentsSplitView.setter
    def EditorGuiAllowsComponentsSplitView(self, val): self.EditorGuiAllowsComponentsSplitView.set(val)
    @property
    def EditorGuiListenGamepad(self):  # type: ()->Bool
        return Bool(self._node.at("EditorGuiListenGamepad"))
    @EditorGuiListenGamepad.setter
    def EditorGuiListenGamepad(self, val): self.EditorGuiListenGamepad.set(val)
    @property
    def EditorGuiListenKeyboard(self):  # type: ()->Bool
        return Bool(self._node.at("EditorGuiListenKeyboard"))
    @EditorGuiListenKeyboard.setter
    def EditorGuiListenKeyboard(self, val): self.EditorGuiListenKeyboard.set(val)
    @property
    def OpenEntityWindows(self):  # type: ()->Bool
        return Bool(self._node.at("OpenEntityWindows"))
    @OpenEntityWindows.setter
    def OpenEntityWindows(self, val): self.OpenEntityWindows.set(val)
    @property
    def UseTransformEditor(self):  # type: ()->Bool
        return Bool(self._node.at("UseTransformEditor"))
    @UseTransformEditor.setter
    def UseTransformEditor(self, val): self.UseTransformEditor.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




