
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.BeamStaffMode import *
from entgen.HotSpotType import *
from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Float import *

from EntityLibPy import Node

class BeamTargetGD(HelperObject):
    schema_name = "BeamTargetGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BeamTargetGD
        return BeamTargetGD(entlib.load_node_file(sourcefile, entlib.get_schema(BeamTargetGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BeamTargetGD
        return BeamTargetGD(entlib.make_node(BeamTargetGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CheckHotspotOrientation(self):  # type: ()->Bool
        return Bool(self._node.at("CheckHotspotOrientation"))
    @CheckHotspotOrientation.setter
    def CheckHotspotOrientation(self, val): self.CheckHotspotOrientation.set(val)
    @property
    def EventTriggered(self):  # type: ()->String
        return String(self._node.at("EventTriggered"))
    @EventTriggered.setter
    def EventTriggered(self, val): self.EventTriggered.set(val)
    @property
    def HotspotType(self):  # type: ()->HotSpotType
        return HotSpotType(self._node.at("HotspotType"))
    @HotspotType.setter
    def HotspotType(self, val): self.HotspotType.set(val)
    @property
    def IsCollectable(self):  # type: ()->Bool
        return Bool(self._node.at("IsCollectable"))
    @IsCollectable.setter
    def IsCollectable(self, val): self.IsCollectable.set(val)
    @property
    def Levitate(self):  # type: ()->Bool
        return Bool(self._node.at("Levitate"))
    @Levitate.setter
    def Levitate(self, val): self.Levitate.set(val)
    @property
    def MaxTargetableDistance(self):  # type: ()->Float
        return Float(self._node.at("MaxTargetableDistance"))
    @MaxTargetableDistance.setter
    def MaxTargetableDistance(self, val): self.MaxTargetableDistance.set(val)
    @property
    def Mode(self):  # type: ()->BeamStaffMode
        return BeamStaffMode(self._node.at("Mode"))
    @Mode.setter
    def Mode(self, val): self.Mode.set(val)
    @property
    def SpendEnergy(self):  # type: ()->Bool
        return Bool(self._node.at("SpendEnergy"))
    @SpendEnergy.setter
    def SpendEnergy(self, val): self.SpendEnergy.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




