
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.GPEType import *
from entgen.String import *
from entgen.ComponentGD import *
from entgen.ResponsiblePointer_ActorState_ import *

from EntityLibPy import Node

class InteractableGPEGD(HelperObject):
    schema_name = "InteractableGPEGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->InteractableGPEGD
        return InteractableGPEGD(entlib.load_node_file(sourcefile, entlib.get_schema(InteractableGPEGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->InteractableGPEGD
        return InteractableGPEGD(entlib.make_node(InteractableGPEGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def GPEActorState(self):  # type: ()->ResponsiblePointer_ActorState_
        return ResponsiblePointer_ActorState_(self._node.at("GPEActorState"))
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
    def InteractionModeActorState(self):  # type: ()->ResponsiblePointer_ActorState_
        return ResponsiblePointer_ActorState_(self._node.at("InteractionModeActorState"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




