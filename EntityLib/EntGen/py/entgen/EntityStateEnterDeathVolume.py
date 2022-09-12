
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Specie import *

from EntityLibPy import Node

class EntityStateEnterDeathVolume(HelperObject):
    schema_name = "EntityStateEnterDeathVolume"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateEnterDeathVolume
        return EntityStateEnterDeathVolume(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateEnterDeathVolume.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateEnterDeathVolume
        return EntityStateEnterDeathVolume(entlib.make_node(EntityStateEnterDeathVolume.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AutorizedSpecies(self):  # type: ()->PrimArray[Specie]
        return (lambda n: PrimArray(Specie, n))(self._node.at("AutorizedSpecies"))
    @AutorizedSpecies.setter
    def AutorizedSpecies(self, val): self.AutorizedSpecies.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




