
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Float import *

from EntityLibPy import Node

class EntityStateCollectVertebrae(HelperObject):
    schema_name = "EntityStateCollectVertebrae"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateCollectVertebrae
        return EntityStateCollectVertebrae(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateCollectVertebrae.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateCollectVertebrae
        return EntityStateCollectVertebrae(entlib.make_node(EntityStateCollectVertebrae.schema_name))
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
    @property
    def meditationDuration(self):  # type: ()->Float
        return Float(self._node.at("meditationDuration"))
    @meditationDuration.setter
    def meditationDuration(self, val): self.meditationDuration.set(val)
    pass




