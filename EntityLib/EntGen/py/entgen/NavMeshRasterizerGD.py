
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *

from EntityLibPy import Node

class NavMeshRasterizerGD(HelperObject):
    schema_name = "NavMeshRasterizerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->NavMeshRasterizerGD
        return NavMeshRasterizerGD(entlib.load_node_file(sourcefile, entlib.get_schema(NavMeshRasterizerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->NavMeshRasterizerGD
        return NavMeshRasterizerGD(entlib.make_node(NavMeshRasterizerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def GridSize(self):  # type: ()->Float
        return Float(self._node.at("GridSize"))
    @GridSize.setter
    def GridSize(self, val): self.GridSize.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




