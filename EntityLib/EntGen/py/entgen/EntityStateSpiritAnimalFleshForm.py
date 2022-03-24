
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class EntityStateSpiritAnimalFleshForm(HelperObject):
    schema_name = "EntityStateSpiritAnimalFleshForm"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateSpiritAnimalFleshForm
        return EntityStateSpiritAnimalFleshForm(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateSpiritAnimalFleshForm.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateSpiritAnimalFleshForm
        return EntityStateSpiritAnimalFleshForm(entlib.make_node(EntityStateSpiritAnimalFleshForm.schema_name))
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




