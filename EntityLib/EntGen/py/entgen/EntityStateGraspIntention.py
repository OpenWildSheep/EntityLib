
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class EntityStateGraspIntention(HelperObject):
    schema_name = "EntityStateGraspIntention"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateGraspIntention
        return EntityStateGraspIntention(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateGraspIntention.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateGraspIntention
        return EntityStateGraspIntention(entlib.make_node(EntityStateGraspIntention.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




