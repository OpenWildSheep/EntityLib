
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *

from EntityLibPy import Node

class TravelParams(HelperObject):
    schema_name = "TravelParams"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TravelParams
        return TravelParams(entlib.load_node_file(sourcefile, entlib.get_schema(TravelParams.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TravelParams
        return TravelParams(entlib.make_node(TravelParams.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Acceleration(self):  # type: ()->Float
        return Float(self._node.at("Acceleration"))
    @Acceleration.setter
    def Acceleration(self, val): self.Acceleration.set(val)
    @property
    def AccelerationZ(self):  # type: ()->Float
        return Float(self._node.at("AccelerationZ"))
    @AccelerationZ.setter
    def AccelerationZ(self, val): self.AccelerationZ.set(val)
    @property
    def Deceleration(self):  # type: ()->Float
        return Float(self._node.at("Deceleration"))
    @Deceleration.setter
    def Deceleration(self, val): self.Deceleration.set(val)
    @property
    def HeightOffset(self):  # type: ()->Float
        return Float(self._node.at("HeightOffset"))
    @HeightOffset.setter
    def HeightOffset(self, val): self.HeightOffset.set(val)
    @property
    def MoveBlend(self):  # type: ()->Float
        return Float(self._node.at("MoveBlend"))
    @MoveBlend.setter
    def MoveBlend(self, val): self.MoveBlend.set(val)
    @property
    def TravelSpeed(self):  # type: ()->Float
        return Float(self._node.at("TravelSpeed"))
    @TravelSpeed.setter
    def TravelSpeed(self, val): self.TravelSpeed.set(val)
    @property
    def UseFlyingNavMesh(self):  # type: ()->Bool
        return Bool(self._node.at("UseFlyingNavMesh"))
    @UseFlyingNavMesh.setter
    def UseFlyingNavMesh(self, val): self.UseFlyingNavMesh.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




