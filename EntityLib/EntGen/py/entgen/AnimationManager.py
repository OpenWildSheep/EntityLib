
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.Manager import *
from entgen.String import *
from entgen.DirectionSyncData import *

from EntityLibPy import Node

class AnimationManager(HelperObject):
    schema_name = "AnimationManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationManager
        return AnimationManager(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationManager
        return AnimationManager(entlib.make_node(AnimationManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AnimationVariantDelayMax(self):  # type: ()->Float
        return Float(self._node.at("AnimationVariantDelayMax"))
    @AnimationVariantDelayMax.setter
    def AnimationVariantDelayMax(self, val): self.AnimationVariantDelayMax.set(val)
    @property
    def AnimationVariantDelayMin(self):  # type: ()->Float
        return Float(self._node.at("AnimationVariantDelayMin"))
    @AnimationVariantDelayMin.setter
    def AnimationVariantDelayMin(self, val): self.AnimationVariantDelayMin.set(val)
    @property
    def LookAtSlopeCoeff(self):  # type: ()->Float
        return Float(self._node.at("LookAtSlopeCoeff"))
    @LookAtSlopeCoeff.setter
    def LookAtSlopeCoeff(self, val): self.LookAtSlopeCoeff.set(val)
    @property
    def PlayRatioMax(self):  # type: ()->Float
        return Float(self._node.at("PlayRatioMax"))
    @PlayRatioMax.setter
    def PlayRatioMax(self, val): self.PlayRatioMax.set(val)
    @property
    def PlayRatioMin(self):  # type: ()->Float
        return Float(self._node.at("PlayRatioMin"))
    @PlayRatioMin.setter
    def PlayRatioMin(self, val): self.PlayRatioMin.set(val)
    @property
    def RejectedMetadataStatus(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("RejectedMetadataStatus"))
    @RejectedMetadataStatus.setter
    def RejectedMetadataStatus(self, val): self.RejectedMetadataStatus.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def SyncDatas(self):  # type: ()->Array[DirectionSyncData]
        return (lambda n: Array(DirectionSyncData, n))(self._node.at("SyncDatas"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def canDetachFromGroundAction(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("canDetachFromGroundAction"))
    @canDetachFromGroundAction.setter
    def canDetachFromGroundAction(self, val): self.canDetachFromGroundAction.set(val)
    pass




