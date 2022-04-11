
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class TerrainSurfaceObject(HelperObject):
    schema_name = "TerrainSurfaceObject"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TerrainSurfaceObject
        return TerrainSurfaceObject(entlib.load_node_file(sourcefile, entlib.get_schema(TerrainSurfaceObject.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TerrainSurfaceObject
        return TerrainSurfaceObject(entlib.make_node(TerrainSurfaceObject.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EDITOR_tso(self):  # type: ()->String
        return String(self._node.at("EDITOR_tso"))
    @EDITOR_tso.setter
    def EDITOR_tso(self, val): self.EDITOR_tso.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




