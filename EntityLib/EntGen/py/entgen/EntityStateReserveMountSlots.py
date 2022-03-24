
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.MountableData import *

from EntityLibPy import Node

class EntityStateReserveMountSlots(HelperObject):
    schema_name = "EntityStateReserveMountSlots"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateReserveMountSlots
        return EntityStateReserveMountSlots(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateReserveMountSlots.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateReserveMountSlots
        return EntityStateReserveMountSlots(entlib.make_node(EntityStateReserveMountSlots.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def MountableDataTo(self):  # type: ()->MountableData
        return MountableData(self._node.at("MountableDataTo"))
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




