
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class GroundTypeSamplerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/GroundTypeSamplerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GroundTypeSamplerGD
        return GroundTypeSamplerGD(entlib.load_node_file(sourcefile, entlib.get_schema(GroundTypeSamplerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GroundTypeSamplerGD
        return GroundTypeSamplerGD(entlib.make_node(GroundTypeSamplerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def GroundTypeMapPath(self):  # type: ()->String
        return String(self._node.at("GroundTypeMapPath"))
    @GroundTypeMapPath.setter
    def GroundTypeMapPath(self, val): self.GroundTypeMapPath.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass



