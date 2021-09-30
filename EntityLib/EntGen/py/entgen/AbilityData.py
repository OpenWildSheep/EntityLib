
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorAbility import *


class AbilityData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AbilityData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(AbilityData.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def abilities(self): return (lambda n: PrimArray(ActorAbility, n))(self._node.at("abilities"))
    @abilities.setter
    def abilities(self, val): self.abilities.set(val)
    pass




