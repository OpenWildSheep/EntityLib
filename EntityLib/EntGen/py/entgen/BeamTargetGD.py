
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.BeamStaffMode import *
from entgen.HotSpotType import *
from entgen.String import *
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
    def InteractMaxDistance(self):  # type: ()->Float
        return Float(self._node.at("InteractMaxDistance"))
    @InteractMaxDistance.setter
    def InteractMaxDistance(self, val): self.InteractMaxDistance.set(val)
    @property
    def InteractionRadius(self):  # type: ()->Float
        return Float(self._node.at("InteractionRadius"))
    @InteractionRadius.setter
    def InteractionRadius(self, val): self.InteractionRadius.set(val)
    @property
    def Mode(self):  # type: ()->BeamStaffMode
        return BeamStaffMode(self._node.at("Mode"))
    @Mode.setter
    def Mode(self, val): self.Mode.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




