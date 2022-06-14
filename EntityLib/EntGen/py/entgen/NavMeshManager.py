
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.Manager import *
from entgen.RecastNavmeshGenerationParameters import *
from entgen.String import *

from EntityLibPy import Node

class NavMeshManager(HelperObject):
    schema_name = "NavMeshManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->NavMeshManager
        return NavMeshManager(entlib.load_node_file(sourcefile, entlib.get_schema(NavMeshManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->NavMeshManager
        return NavMeshManager(entlib.make_node(NavMeshManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def NavMeshMaxHeight(self):  # type: ()->Float
        return Float(self._node.at("NavMeshMaxHeight"))
    @NavMeshMaxHeight.setter
    def NavMeshMaxHeight(self, val): self.NavMeshMaxHeight.set(val)
    @property
    def NavMeshMaxSize(self):  # type: ()->Float
        return Float(self._node.at("NavMeshMaxSize"))
    @NavMeshMaxSize.setter
    def NavMeshMaxSize(self, val): self.NavMeshMaxSize.set(val)
    @property
    def RecastParameters(self):  # type: ()->Map[str, RecastNavmeshGenerationParameters]
        return (lambda n: Map(str, RecastNavmeshGenerationParameters, n))(self._node.at("RecastParameters"))
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def TileMargin(self):  # type: ()->Float
        return Float(self._node.at("TileMargin"))
    @TileMargin.setter
    def TileMargin(self, val): self.TileMargin.set(val)
    @property
    def TileSize(self):  # type: ()->Float
        return Float(self._node.at("TileSize"))
    @TileSize.setter
    def TileSize(self, val): self.TileSize.set(val)
    @property
    def VerticalTolerance(self):  # type: ()->Float
        return Float(self._node.at("VerticalTolerance"))
    @VerticalTolerance.setter
    def VerticalTolerance(self, val): self.VerticalTolerance.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




