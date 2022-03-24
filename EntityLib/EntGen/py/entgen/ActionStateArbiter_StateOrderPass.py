
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.String import *

from EntityLibPy import Node

class ActionStateArbiter_StateOrderPass(HelperObject):
    schema_name = "ActionStateArbiter::StateOrderPass"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionStateArbiter_StateOrderPass
        return ActionStateArbiter_StateOrderPass(entlib.load_node_file(sourcefile, entlib.get_schema(ActionStateArbiter_StateOrderPass.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionStateArbiter_StateOrderPass
        return ActionStateArbiter_StateOrderPass(entlib.make_node(ActionStateArbiter_StateOrderPass.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Order(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("Order"))
    @Order.setter
    def Order(self, val): self.Order.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




