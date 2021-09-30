
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.ScaleConverter import *
from entgen.Vector3 import *


class HeadCollisionBehaviorData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/HeadCollisionBehaviorData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(HeadCollisionBehaviorData.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def disableDuration(self): return Float(self._node.at("disableDuration"))
    @disableDuration.setter
    def disableDuration(self, val): self.disableDuration.set(val)
    @property
    def enableDuration(self): return Float(self._node.at("enableDuration"))
    @enableDuration.setter
    def enableDuration(self, val): self.enableDuration.set(val)
    @property
    def headOffset(self): return Vector3(self._node.at("headOffset"))
    @headOffset.setter
    def headOffset(self, val): self.headOffset.set(val)
    @property
    def isEnabled(self): return Bool(self._node.at("isEnabled"))
    @isEnabled.setter
    def isEnabled(self, val): self.isEnabled.set(val)
    @property
    def radiusCoeff(self): return Float(self._node.at("radiusCoeff"))
    @radiusCoeff.setter
    def radiusCoeff(self, val): self.radiusCoeff.set(val)
    @property
    def slopeInfluence(self): return ScaleConverter(self._node.at("slopeInfluence"))
    @property
    def softCollisionRigidbodyCoeff(self): return Float(self._node.at("softCollisionRigidbodyCoeff"))
    @softCollisionRigidbodyCoeff.setter
    def softCollisionRigidbodyCoeff(self, val): self.softCollisionRigidbodyCoeff.set(val)
    @property
    def softCollisionVisualCoeff(self): return Float(self._node.at("softCollisionVisualCoeff"))
    @softCollisionVisualCoeff.setter
    def softCollisionVisualCoeff(self, val): self.softCollisionVisualCoeff.set(val)
    @property
    def speedInfluence(self): return ScaleConverter(self._node.at("speedInfluence"))
    @property
    def visualSmoothOut(self): return ScaleConverter(self._node.at("visualSmoothOut"))
    pass




