
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Manager import *

from EntityLibPy import Node

class FightManager(HelperObject):
    schema_name = "FightManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FightManager
        return FightManager(entlib.load_node_file(sourcefile, entlib.get_schema(FightManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FightManager
        return FightManager(entlib.make_node(FightManager.schema_name))
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




