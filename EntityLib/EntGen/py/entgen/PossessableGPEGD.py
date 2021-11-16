
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.GPEType import *
from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class PossessableGPEGD(HelperObject):
    schema_name = "PossessableGPEGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PossessableGPEGD
        return PossessableGPEGD(entlib.load_node_file(sourcefile, entlib.get_schema(PossessableGPEGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PossessableGPEGD
        return PossessableGPEGD(entlib.make_node(PossessableGPEGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def GPEActorStateName(self):  # type: ()->String
        return String(self._node.at("GPEActorStateName"))
    @GPEActorStateName.setter
    def GPEActorStateName(self, val): self.GPEActorStateName.set(val)
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
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




