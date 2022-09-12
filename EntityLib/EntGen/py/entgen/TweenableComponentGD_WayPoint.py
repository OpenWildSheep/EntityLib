
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.Scale import *
from entgen.SimpleCurve1D import *
from entgen.TweenableComponentGD_WayPoint_Orientation import *
from entgen.TweenableComponentGD_WayPoint_Position import *

from EntityLibPy import Node

class TweenableComponentGD_WayPoint(HelperObject):
    schema_name = "TweenableComponentGD::WayPoint"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TweenableComponentGD_WayPoint
        return TweenableComponentGD_WayPoint(entlib.load_node_file(sourcefile, entlib.get_schema(TweenableComponentGD_WayPoint.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TweenableComponentGD_WayPoint
        return TweenableComponentGD_WayPoint(entlib.make_node(TweenableComponentGD_WayPoint.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Easing(self):  # type: ()->SimpleCurve1D
        return SimpleCurve1D(self._node.at("Easing"))
    @property
    def Orientation(self):  # type: ()->TweenableComponentGD_WayPoint_Orientation
        return TweenableComponentGD_WayPoint_Orientation(self._node.at("Orientation"))
    @property
    def Position(self):  # type: ()->TweenableComponentGD_WayPoint_Position
        return TweenableComponentGD_WayPoint_Position(self._node.at("Position"))
    @property
    def Scale(self):  # type: ()->Scale
        return Scale(self._node.at("Scale"))
    @property
    def TimeScale(self):  # type: ()->Float
        return Float(self._node.at("TimeScale"))
    @TimeScale.setter
    def TimeScale(self, val): self.TimeScale.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




