
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class EntityStateReadyToGiveOrder(HelperObject):
    schema_name = "EntityStateReadyToGiveOrder"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateReadyToGiveOrder
        return EntityStateReadyToGiveOrder(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateReadyToGiveOrder.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateReadyToGiveOrder
        return EntityStateReadyToGiveOrder(entlib.make_node(EntityStateReadyToGiveOrder.schema_name))
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




