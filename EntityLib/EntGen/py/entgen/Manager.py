
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Manager_EntityID import *

from EntityLibPy import Node

class Manager(HelperObject):
    schema_name = "Manager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Manager
        return Manager(entlib.load_node_file(sourcefile, entlib.get_schema(Manager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Manager
        return Manager(entlib.make_node(Manager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EntityID(self):  # type: ()->Manager_EntityID
        return Manager_EntityID(self._node.at("EntityID"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




