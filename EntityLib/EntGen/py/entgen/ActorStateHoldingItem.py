
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.EntityRef import *


class ActorStateHoldingItem(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ActorStateHoldingItem"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateHoldingItem.schema_name))
    @property
    def InventoryEntityRef(self): return EntityRef(self._node.at("InventoryEntityRef"))
    @InventoryEntityRef.setter
    def InventoryEntityRef(self, val): self.InventoryEntityRef.set(val)
    @property
    def ItemEntityRef(self): return EntityRef(self._node.at("ItemEntityRef"))
    @ItemEntityRef.setter
    def ItemEntityRef(self, val): self.ItemEntityRef.set(val)
    @property
    def Super(self): return ActorState(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




