
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.TweenableComponentGD_WayPoint import *

from EntityLibPy import Node

class TweenableComponentGD(HelperObject):
    schema_name = "TweenableComponentGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TweenableComponentGD
        return TweenableComponentGD(entlib.load_node_file(sourcefile, entlib.get_schema(TweenableComponentGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TweenableComponentGD
        return TweenableComponentGD(entlib.make_node(TweenableComponentGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Local(self):  # type: ()->Bool
        return Bool(self._node.at("Local"))
    @Local.setter
    def Local(self, val): self.Local.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def WayPoints(self):  # type: ()->Array[TweenableComponentGD_WayPoint]
        return (lambda n: Array(TweenableComponentGD_WayPoint, n))(self._node.at("WayPoints"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




