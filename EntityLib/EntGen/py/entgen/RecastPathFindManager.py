
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Manager import *

from EntityLibPy import Node

class RecastPathFindManager(HelperObject):
    schema_name = "RecastPathFindManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RecastPathFindManager
        return RecastPathFindManager(entlib.load_node_file(sourcefile, entlib.get_schema(RecastPathFindManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RecastPathFindManager
        return RecastPathFindManager(entlib.make_node(RecastPathFindManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AStarSearchMaxIteration(self):  # type: ()->Int
        return Int(self._node.at("AStarSearchMaxIteration"))
    @AStarSearchMaxIteration.setter
    def AStarSearchMaxIteration(self, val): self.AStarSearchMaxIteration.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




