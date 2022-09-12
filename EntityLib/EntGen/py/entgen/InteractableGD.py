
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.GPEType import *
from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.FocusInteractableEntityState import *
from entgen.FocusInteractorEntityState import *
from entgen.InteractionInteractableEntityState import *
from entgen.InteractionInteractorEntityState import *

from EntityLibPy import Node

class InteractableGD(HelperObject):
    schema_name = "InteractableGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->InteractableGD
        return InteractableGD(entlib.load_node_file(sourcefile, entlib.get_schema(InteractableGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->InteractableGD
        return InteractableGD(entlib.make_node(InteractableGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def FocusInteractableEntityState(self):  # type: ()->FocusInteractableEntityState
        return FocusInteractableEntityState(self._node.at("FocusInteractableEntityState"))
    @property
    def FocusInteractorEntityState(self):  # type: ()->FocusInteractorEntityState
        return FocusInteractorEntityState(self._node.at("FocusInteractorEntityState"))
    @property
    def GPEType(self):  # type: ()->GPEType
        return GPEType(self._node.at("GPEType"))
    @GPEType.setter
    def GPEType(self, val): self.GPEType.set(val)
    @property
    def HotspotName(self):  # type: ()->String
        return String(self._node.at("HotspotName"))
    @HotspotName.setter
    def HotspotName(self, val): self.HotspotName.set(val)
    @property
    def InteractMaxDistance(self):  # type: ()->Float
        return Float(self._node.at("InteractMaxDistance"))
    @InteractMaxDistance.setter
    def InteractMaxDistance(self, val): self.InteractMaxDistance.set(val)
    @property
    def InteractMaxDistanceHysteresis(self):  # type: ()->Float
        return Float(self._node.at("InteractMaxDistanceHysteresis"))
    @InteractMaxDistanceHysteresis.setter
    def InteractMaxDistanceHysteresis(self, val): self.InteractMaxDistanceHysteresis.set(val)
    @property
    def InteractionInteractableEntityState(self):  # type: ()->InteractionInteractableEntityState
        return InteractionInteractableEntityState(self._node.at("InteractionInteractableEntityState"))
    @property
    def InteractionInteractorEntityState(self):  # type: ()->InteractionInteractorEntityState
        return InteractionInteractorEntityState(self._node.at("InteractionInteractorEntityState"))
    @property
    def InteractionPriority(self):  # type: ()->Float
        return Float(self._node.at("InteractionPriority"))
    @InteractionPriority.setter
    def InteractionPriority(self, val): self.InteractionPriority.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




