
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *

from EntityLibPy import Node

class SceneConverter_NavmeshOptions(HelperObject):
    schema_name = "SceneConverter::NavmeshOptions"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SceneConverter_NavmeshOptions
        return SceneConverter_NavmeshOptions(entlib.load_node_file(sourcefile, entlib.get_schema(SceneConverter_NavmeshOptions.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SceneConverter_NavmeshOptions
        return SceneConverter_NavmeshOptions(entlib.make_node(SceneConverter_NavmeshOptions.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def KeepStaticObjectsNavMeshStampersOutOfTerrains(self):  # type: ()->Bool
        return Bool(self._node.at("KeepStaticObjectsNavMeshStampersOutOfTerrains"))
    @KeepStaticObjectsNavMeshStampersOutOfTerrains.setter
    def KeepStaticObjectsNavMeshStampersOutOfTerrains(self, val): self.KeepStaticObjectsNavMeshStampersOutOfTerrains.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




