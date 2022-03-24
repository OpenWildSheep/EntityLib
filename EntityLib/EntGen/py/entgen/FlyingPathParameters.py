
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.String import *

from EntityLibPy import Node

class FlyingPathParameters(HelperObject):
    schema_name = "FlyingPathParameters"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FlyingPathParameters
        return FlyingPathParameters(entlib.load_node_file(sourcefile, entlib.get_schema(FlyingPathParameters.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FlyingPathParameters
        return FlyingPathParameters(entlib.make_node(FlyingPathParameters.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def FlyOverOffset(self):  # type: ()->Float
        return Float(self._node.at("FlyOverOffset"))
    @FlyOverOffset.setter
    def FlyOverOffset(self, val): self.FlyOverOffset.set(val)
    @property
    def FlyUpOverCharge(self):  # type: ()->Float
        return Float(self._node.at("FlyUpOverCharge"))
    @FlyUpOverCharge.setter
    def FlyUpOverCharge(self, val): self.FlyUpOverCharge.set(val)
    @property
    def FlyerRadius(self):  # type: ()->Float
        return Float(self._node.at("FlyerRadius"))
    @FlyerRadius.setter
    def FlyerRadius(self, val): self.FlyerRadius.set(val)
    @property
    def PreferredFlyDown(self):  # type: ()->Float
        return Float(self._node.at("PreferredFlyDown"))
    @PreferredFlyDown.setter
    def PreferredFlyDown(self, val): self.PreferredFlyDown.set(val)
    @property
    def PreferredFlyUp(self):  # type: ()->Float
        return Float(self._node.at("PreferredFlyUp"))
    @PreferredFlyUp.setter
    def PreferredFlyUp(self, val): self.PreferredFlyUp.set(val)
    @property
    def SizeLayerMask(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("SizeLayerMask"))
    @SizeLayerMask.setter
    def SizeLayerMask(self, val): self.SizeLayerMask.set(val)
    @property
    def SmoothFinalPhase(self):  # type: ()->Bool
        return Bool(self._node.at("SmoothFinalPhase"))
    @SmoothFinalPhase.setter
    def SmoothFinalPhase(self, val): self.SmoothFinalPhase.set(val)
    @property
    def SmoothHeightChanges(self):  # type: ()->Bool
        return Bool(self._node.at("SmoothHeightChanges"))
    @SmoothHeightChanges.setter
    def SmoothHeightChanges(self, val): self.SmoothHeightChanges.set(val)
    @property
    def SmoothLookahead(self):  # type: ()->Float
        return Float(self._node.at("SmoothLookahead"))
    @SmoothLookahead.setter
    def SmoothLookahead(self, val): self.SmoothLookahead.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




