
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.Vector3 import *


class CameraShakeData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CameraShakeData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(CameraShakeData.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def shakeDuration(self): return Float(self._node.at("shakeDuration"))
    @shakeDuration.setter
    def shakeDuration(self, val): self.shakeDuration.set(val)
    @property
    def shakeFrequency(self): return Float(self._node.at("shakeFrequency"))
    @shakeFrequency.setter
    def shakeFrequency(self, val): self.shakeFrequency.set(val)
    @property
    def shakeIntensity(self): return Float(self._node.at("shakeIntensity"))
    @shakeIntensity.setter
    def shakeIntensity(self, val): self.shakeIntensity.set(val)
    @property
    def shakeRotation(self): return Vector3(self._node.at("shakeRotation"))
    @shakeRotation.setter
    def shakeRotation(self, val): self.shakeRotation.set(val)
    pass




