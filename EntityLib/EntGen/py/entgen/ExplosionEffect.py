
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.CameraShakeData import *
from entgen.Float import *
from entgen.GameEffect import *

from EntityLibPy import Node

class ExplosionEffect(HelperObject):
    schema_name = "ExplosionEffect"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ExplosionEffect
        return ExplosionEffect(entlib.load_node_file(sourcefile, entlib.get_schema(ExplosionEffect.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ExplosionEffect
        return ExplosionEffect(entlib.make_node(ExplosionEffect.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ControllerVibrationCoef(self):  # type: ()->Float
        return Float(self._node.at("ControllerVibrationCoef"))
    @ControllerVibrationCoef.setter
    def ControllerVibrationCoef(self, val): self.ControllerVibrationCoef.set(val)
    @property
    def DistanceReductionStep(self):  # type: ()->Float
        return Float(self._node.at("DistanceReductionStep"))
    @DistanceReductionStep.setter
    def DistanceReductionStep(self, val): self.DistanceReductionStep.set(val)
    @property
    def Force(self):  # type: ()->Float
        return Float(self._node.at("Force"))
    @Force.setter
    def Force(self, val): self.Force.set(val)
    @property
    def ForceReductionByStep(self):  # type: ()->Float
        return Float(self._node.at("ForceReductionByStep"))
    @ForceReductionByStep.setter
    def ForceReductionByStep(self, val): self.ForceReductionByStep.set(val)
    @property
    def ShakeAttenuationRadius(self):  # type: ()->Float
        return Float(self._node.at("ShakeAttenuationRadius"))
    @ShakeAttenuationRadius.setter
    def ShakeAttenuationRadius(self, val): self.ShakeAttenuationRadius.set(val)
    @property
    def ShakeData(self):  # type: ()->CameraShakeData
        return CameraShakeData(self._node.at("ShakeData"))
    @property
    def ShakeRadius(self):  # type: ()->Float
        return Float(self._node.at("ShakeRadius"))
    @ShakeRadius.setter
    def ShakeRadius(self, val): self.ShakeRadius.set(val)
    @property
    def Super(self):  # type: ()->GameEffect
        return GameEffect(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




