
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *


class GroundTypeSamplerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/GroundTypeSamplerGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(GroundTypeSamplerGD.schema_name))
    @property
    def GroundTypeMapPath(self): return String(self._node.at("GroundTypeMapPath"))
    @GroundTypeMapPath.setter
    def GroundTypeMapPath(self, val): self.GroundTypeMapPath.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




