
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.ScaleConverter import *
from entgen.Vector3 import *

from EntityLibPy import Node

class HeadCollisionBehaviorData(HelperObject):
    schema_name = "HeadCollisionBehaviorData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->HeadCollisionBehaviorData
        return HeadCollisionBehaviorData(entlib.load_node_file(sourcefile, entlib.get_schema(HeadCollisionBehaviorData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->HeadCollisionBehaviorData
        return HeadCollisionBehaviorData(entlib.make_node(HeadCollisionBehaviorData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def disableDuration(self):  # type: ()->Float
        return Float(self._node.at("disableDuration"))
    @disableDuration.setter
    def disableDuration(self, val): self.disableDuration.set(val)
    @property
    def enableDuration(self):  # type: ()->Float
        return Float(self._node.at("enableDuration"))
    @enableDuration.setter
    def enableDuration(self, val): self.enableDuration.set(val)
    @property
    def headOffset(self):  # type: ()->Vector3
        return Vector3(self._node.at("headOffset"))
    @headOffset.setter
    def headOffset(self, val): self.headOffset.set(val)
    @property
    def isEnabled(self):  # type: ()->Bool
        return Bool(self._node.at("isEnabled"))
    @isEnabled.setter
    def isEnabled(self, val): self.isEnabled.set(val)
    @property
    def radiusCoeff(self):  # type: ()->Float
        return Float(self._node.at("radiusCoeff"))
    @radiusCoeff.setter
    def radiusCoeff(self, val): self.radiusCoeff.set(val)
    @property
    def slopeInfluence(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("slopeInfluence"))
    @property
    def softCollisionRigidbodyCoeff(self):  # type: ()->Float
        return Float(self._node.at("softCollisionRigidbodyCoeff"))
    @softCollisionRigidbodyCoeff.setter
    def softCollisionRigidbodyCoeff(self, val): self.softCollisionRigidbodyCoeff.set(val)
    @property
    def softCollisionVisualCoeff(self):  # type: ()->Float
        return Float(self._node.at("softCollisionVisualCoeff"))
    @softCollisionVisualCoeff.setter
    def softCollisionVisualCoeff(self, val): self.softCollisionVisualCoeff.set(val)
    @property
    def speedInfluence(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("speedInfluence"))
    @property
    def visualSmoothOut(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("visualSmoothOut"))
    pass




