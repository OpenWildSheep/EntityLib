
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.GPEType import *
from entgen.String import *
from entgen.ComponentGD import *


class PossessableGPEGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PossessableGPEGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(PossessableGPEGD.schema_name))
    @property
    def GPEActorStateName(self): return String(self._node.at("GPEActorStateName"))
    @GPEActorStateName.setter
    def GPEActorStateName(self, val): self.GPEActorStateName.set(val)
    @property
    def GPEType(self): return GPEType(self._node.at("GPEType"))
    @GPEType.setter
    def GPEType(self, val): self.GPEType.set(val)
    @property
    def HotspotName(self): return String(self._node.at("HotspotName"))
    @HotspotName.setter
    def HotspotName(self, val): self.HotspotName.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




