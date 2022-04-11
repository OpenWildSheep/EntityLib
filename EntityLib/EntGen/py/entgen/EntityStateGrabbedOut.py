
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class EntityStateGrabbedOut(HelperObject):
    schema_name = "EntityStateGrabbedOut"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateGrabbedOut
        return EntityStateGrabbedOut(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateGrabbedOut.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateGrabbedOut
        return EntityStateGrabbedOut(entlib.make_node(EntityStateGrabbedOut.schema_name))
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




