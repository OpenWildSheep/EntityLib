
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

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
    def Dependencies(self):  # type: ()->Array[TupleNode[Type[String], Type[String]]]
        return (lambda n: Array(TupleNode, n))(self._node.at("Dependencies"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




