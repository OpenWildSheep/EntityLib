
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Manager import *

from EntityLibPy import Node

class VisualManager(HelperObject):
    schema_name = "VisualManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->VisualManager
        return VisualManager(entlib.load_node_file(sourcefile, entlib.get_schema(VisualManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->VisualManager
        return VisualManager(entlib.make_node(VisualManager.schema_name))
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




