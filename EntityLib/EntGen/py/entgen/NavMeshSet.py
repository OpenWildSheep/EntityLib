
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.HeightGrid import *
from entgen.NavMesh import *

from EntityLibPy import Node

class NavMeshSet(HelperObject):
    schema_name = "NavMeshSet"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->NavMeshSet
        return NavMeshSet(entlib.load_node_file(sourcefile, entlib.get_schema(NavMeshSet.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->NavMeshSet
        return NavMeshSet(entlib.make_node(NavMeshSet.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def HeightGrid(self):  # type: ()->HeightGrid
        return HeightGrid(self._node.at("HeightGrid"))
    @property
    def NavMeshes(self):  # type: ()->Array[NavMesh]
        return (lambda n: Array(NavMesh, n))(self._node.at("NavMeshes"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




