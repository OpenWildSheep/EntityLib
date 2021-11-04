
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorAbility import *

from EntityLibPy import Node

class AbilityData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AbilityData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AbilityData
        return AbilityData(entlib.load_node_file(sourcefile, entlib.get_schema(AbilityData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AbilityData
        return AbilityData(entlib.make_node(AbilityData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def abilities(self):  # type: ()->PrimArray[ActorAbility]
        return (lambda n: PrimArray(ActorAbility, n))(self._node.at("abilities"))
    @abilities.setter
    def abilities(self, val): self.abilities.set(val)
    pass




