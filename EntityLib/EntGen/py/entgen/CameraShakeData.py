
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.Vector3 import *

from EntityLibPy import Node

class CameraShakeData(HelperObject):
    schema_name = "CameraShakeData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CameraShakeData
        return CameraShakeData(entlib.load_node_file(sourcefile, entlib.get_schema(CameraShakeData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CameraShakeData
        return CameraShakeData(entlib.make_node(CameraShakeData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def shakeDuration(self):  # type: ()->Float
        return Float(self._node.at("shakeDuration"))
    @shakeDuration.setter
    def shakeDuration(self, val): self.shakeDuration.set(val)
    @property
    def shakeFrequency(self):  # type: ()->Float
        return Float(self._node.at("shakeFrequency"))
    @shakeFrequency.setter
    def shakeFrequency(self, val): self.shakeFrequency.set(val)
    @property
    def shakeIntensity(self):  # type: ()->Float
        return Float(self._node.at("shakeIntensity"))
    @shakeIntensity.setter
    def shakeIntensity(self, val): self.shakeIntensity.set(val)
    @property
    def shakeRotation(self):  # type: ()->Vector3
        return Vector3(self._node.at("shakeRotation"))
    @shakeRotation.setter
    def shakeRotation(self, val): self.shakeRotation.set(val)
    pass




