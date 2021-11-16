
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class PathMotionControllerGD(HelperObject):
    schema_name = "PathMotionControllerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PathMotionControllerGD
        return PathMotionControllerGD(entlib.load_node_file(sourcefile, entlib.get_schema(PathMotionControllerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PathMotionControllerGD
        return PathMotionControllerGD(entlib.make_node(PathMotionControllerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




