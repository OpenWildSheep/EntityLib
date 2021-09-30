
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.BeamStaffMode import *
from entgen.HotSpotType import *
from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Float import *


class BeamTargetGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/BeamTargetGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(BeamTargetGD.schema_name))
    @property
    def CheckHotspotOrientation(self): return Bool(self._node.at("CheckHotspotOrientation"))
    @CheckHotspotOrientation.setter
    def CheckHotspotOrientation(self, val): self.CheckHotspotOrientation.set(val)
    @property
    def EventTriggered(self): return String(self._node.at("EventTriggered"))
    @EventTriggered.setter
    def EventTriggered(self, val): self.EventTriggered.set(val)
    @property
    def HotspotType(self): return HotSpotType(self._node.at("HotspotType"))
    @HotspotType.setter
    def HotspotType(self, val): self.HotspotType.set(val)
    @property
    def IsCollectable(self): return Bool(self._node.at("IsCollectable"))
    @IsCollectable.setter
    def IsCollectable(self, val): self.IsCollectable.set(val)
    @property
    def Levitate(self): return Bool(self._node.at("Levitate"))
    @Levitate.setter
    def Levitate(self, val): self.Levitate.set(val)
    @property
    def MaxTargetableDistance(self): return Float(self._node.at("MaxTargetableDistance"))
    @MaxTargetableDistance.setter
    def MaxTargetableDistance(self, val): self.MaxTargetableDistance.set(val)
    @property
    def Mode(self): return BeamStaffMode(self._node.at("Mode"))
    @Mode.setter
    def Mode(self, val): self.Mode.set(val)
    @property
    def SpendEnergy(self): return Bool(self._node.at("SpendEnergy"))
    @SpendEnergy.setter
    def SpendEnergy(self, val): self.SpendEnergy.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




