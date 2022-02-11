
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.Specie import *
from entgen.String import *
from entgen.Bool import *
from entgen.GameEffect import *

from EntityLibPy import Node

class FollowerCallEffect(HelperObject):
    schema_name = "FollowerCallEffect"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FollowerCallEffect
        return FollowerCallEffect(entlib.load_node_file(sourcefile, entlib.get_schema(FollowerCallEffect.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FollowerCallEffect
        return FollowerCallEffect(entlib.make_node(FollowerCallEffect.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AttackOrder(self):  # type: ()->Bool
        return Bool(self._node.at("AttackOrder"))
    @AttackOrder.setter
    def AttackOrder(self, val): self.AttackOrder.set(val)
    @property
    def CallType(self):  # type: ()->String
        return String(self._node.at("CallType"))
    @CallType.setter
    def CallType(self, val): self.CallType.set(val)
    @property
    def Specie(self):  # type: ()->Specie
        return Specie(self._node.at("Specie"))
    @Specie.setter
    def Specie(self, val): self.Specie.set(val)
    @property
    def Super(self):  # type: ()->GameEffect
        return GameEffect(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




