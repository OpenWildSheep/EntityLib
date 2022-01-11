
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.Manager import *

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
    def GridMargin(self):  # type: ()->Float
        return Float(self._node.at("GridMargin"))
    @GridMargin.setter
    def GridMargin(self, val): self.GridMargin.set(val)
    @property
    def GridSize(self):  # type: ()->Float
        return Float(self._node.at("GridSize"))
    @GridSize.setter
    def GridSize(self, val): self.GridSize.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




