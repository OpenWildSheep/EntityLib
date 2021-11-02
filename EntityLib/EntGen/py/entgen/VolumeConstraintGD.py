
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.VolumeConstraintDataGD import *

from EntityLibPy import Node

class VolumeConstraintGD(HelperObject):
    schema_name = "VolumeConstraintGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->VolumeConstraintGD
        return VolumeConstraintGD(entlib.load_node_file(sourcefile, entlib.get_schema(VolumeConstraintGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->VolumeConstraintGD
        return VolumeConstraintGD(entlib.make_node(VolumeConstraintGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Constraints(self):  # type: ()->Array[VolumeConstraintDataGD]
        return (lambda n: Array(VolumeConstraintDataGD, n))(self._node.at("Constraints"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




