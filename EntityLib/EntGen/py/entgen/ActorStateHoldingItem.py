
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.EntityRef import *

from EntityLibPy import Node

class ActorStateHoldingItem(HelperObject):
    schema_name = "ActorStateHoldingItem"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateHoldingItem
        return ActorStateHoldingItem(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateHoldingItem.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateHoldingItem
        return ActorStateHoldingItem(entlib.make_node(ActorStateHoldingItem.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def InventoryEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("InventoryEntityRef"))
    @InventoryEntityRef.setter
    def InventoryEntityRef(self, val): self.InventoryEntityRef.set(val)
    @property
    def ItemEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("ItemEntityRef"))
    @ItemEntityRef.setter
    def ItemEntityRef(self, val): self.ItemEntityRef.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




