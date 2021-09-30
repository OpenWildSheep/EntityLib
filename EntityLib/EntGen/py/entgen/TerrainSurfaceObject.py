
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *


class TerrainSurfaceObject(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/TerrainSurfaceObject"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(TerrainSurfaceObject.schema_name))
    @property
    def EDITOR_tso(self): return String(self._node.at("EDITOR_tso"))
    @EDITOR_tso.setter
    def EDITOR_tso(self, val): self.EDITOR_tso.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




