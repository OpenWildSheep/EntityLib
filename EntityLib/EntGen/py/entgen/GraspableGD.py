
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.GraspableInteractionData import *
from entgen.GraspType import *

from EntityLibPy import Node

class GraspableGD(HelperObject):
    schema_name = "GraspableGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GraspableGD
        return GraspableGD(entlib.load_node_file(sourcefile, entlib.get_schema(GraspableGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GraspableGD
        return GraspableGD(entlib.make_node(GraspableGD.schema_name))
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
    @property
    def interactionDatas(self):  # type: ()->Map[GraspTypeEnum, GraspableInteractionData]
        return (lambda n: Map(GraspTypeEnum, GraspableInteractionData, n))(self._node.at("interactionDatas"))
    pass




