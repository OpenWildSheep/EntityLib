
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class InputCollisionBehaviorData(HelperObject):
    schema_name = "InputCollisionBehaviorData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->InputCollisionBehaviorData
        return InputCollisionBehaviorData(entlib.load_node_file(sourcefile, entlib.get_schema(InputCollisionBehaviorData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->InputCollisionBehaviorData
        return InputCollisionBehaviorData(entlib.make_node(InputCollisionBehaviorData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AltitudeMax(self):  # type: ()->Float
        return Float(self._node.at("AltitudeMax"))
    @AltitudeMax.setter
    def AltitudeMax(self, val): self.AltitudeMax.set(val)
    @property
    def DepthMax(self):  # type: ()->Float
        return Float(self._node.at("DepthMax"))
    @DepthMax.setter
    def DepthMax(self, val): self.DepthMax.set(val)
    @property
    def FrontAngle(self):  # type: ()->Float
        return Float(self._node.at("FrontAngle"))
    @FrontAngle.setter
    def FrontAngle(self, val): self.FrontAngle.set(val)
    @property
    def RadiusCoeff(self):  # type: ()->Float
        return Float(self._node.at("RadiusCoeff"))
    @RadiusCoeff.setter
    def RadiusCoeff(self, val): self.RadiusCoeff.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




