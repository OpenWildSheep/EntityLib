
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.CheckIsNotInCameraFrustrum import *
from entgen.ComponentInput import *
from entgen.MinDistanceToRespawnPosition import *

from EntityLibPy import Node

class RespawnabilityComponentInput(HelperObject):
    schema_name = "RespawnabilityComponentInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RespawnabilityComponentInput
        return RespawnabilityComponentInput(entlib.load_node_file(sourcefile, entlib.get_schema(RespawnabilityComponentInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RespawnabilityComponentInput
        return RespawnabilityComponentInput(entlib.make_node(RespawnabilityComponentInput.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CheckIsNotInCameraFrustrum(self):  # type: ()->CheckIsNotInCameraFrustrum
        return CheckIsNotInCameraFrustrum(self._node.at("CheckIsNotInCameraFrustrum"))
    @property
    def MinDistanceToRespawnPosition(self):  # type: ()->MinDistanceToRespawnPosition
        return MinDistanceToRespawnPosition(self._node.at("MinDistanceToRespawnPosition"))
    @property
    def Super(self):  # type: ()->ComponentInput
        return ComponentInput(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




