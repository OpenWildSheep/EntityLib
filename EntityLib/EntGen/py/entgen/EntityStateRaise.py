
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.EnergySide import *
from entgen.String import *
from entgen.ActorState import *
from entgen.Float import *

from EntityLibPy import Node

class EntityStateRaise(HelperObject):
    schema_name = "EntityStateRaise"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateRaise
        return EntityStateRaise(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateRaise.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateRaise
        return EntityStateRaise(entlib.make_node(EntityStateRaise.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Damages(self):  # type: ()->Float
        return Float(self._node.at("Damages"))
    @Damages.setter
    def Damages(self, val): self.Damages.set(val)
    @property
    def EnergySide(self):  # type: ()->EnergySide
        return EnergySide(self._node.at("EnergySide"))
    @EnergySide.setter
    def EnergySide(self, val): self.EnergySide.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




