
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class HitWallEnvironmentData(HelperObject):
    schema_name = "HitWallEnvironmentData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->HitWallEnvironmentData
        return HitWallEnvironmentData(entlib.load_node_file(sourcefile, entlib.get_schema(HitWallEnvironmentData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->HitWallEnvironmentData
        return HitWallEnvironmentData(entlib.make_node(HitWallEnvironmentData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def NormalAngleMax(self):  # type: ()->Float
        return Float(self._node.at("NormalAngleMax"))
    @NormalAngleMax.setter
    def NormalAngleMax(self, val): self.NormalAngleMax.set(val)
    @property
    def NormalAngleMin(self):  # type: ()->Float
        return Float(self._node.at("NormalAngleMin"))
    @NormalAngleMin.setter
    def NormalAngleMin(self, val): self.NormalAngleMin.set(val)
    @property
    def RetimingVerticalAngleMax(self):  # type: ()->Float
        return Float(self._node.at("RetimingVerticalAngleMax"))
    @RetimingVerticalAngleMax.setter
    def RetimingVerticalAngleMax(self, val): self.RetimingVerticalAngleMax.set(val)
    @property
    def RetimingVerticalAngleMin(self):  # type: ()->Float
        return Float(self._node.at("RetimingVerticalAngleMin"))
    @RetimingVerticalAngleMin.setter
    def RetimingVerticalAngleMin(self, val): self.RetimingVerticalAngleMin.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




