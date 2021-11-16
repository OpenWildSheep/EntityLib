
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Manager import *

from EntityLibPy import Node

class ReloadManager(HelperObject):
    schema_name = "ReloadManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ReloadManager
        return ReloadManager(entlib.load_node_file(sourcefile, entlib.get_schema(ReloadManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ReloadManager
        return ReloadManager(entlib.make_node(ReloadManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




