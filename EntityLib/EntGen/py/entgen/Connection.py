
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentMethodRef import *
from entgen.ComponentSignalRef import *

from EntityLibPy import Node

class Connection(HelperObject):
    schema_name = "Connection"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Connection
        return Connection(entlib.load_node_file(sourcefile, entlib.get_schema(Connection.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Connection
        return Connection(entlib.make_node(Connection.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def receiver(self):  # type: ()->ComponentMethodRef
        return ComponentMethodRef(self._node.at("receiver"))
    @property
    def sender(self):  # type: ()->ComponentSignalRef
        return ComponentSignalRef(self._node.at("sender"))
    pass




