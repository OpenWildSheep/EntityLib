
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ClassMemberRef import *

from EntityLibPy import Node

class ComponentSignalRef(HelperObject):
    schema_name = "ComponentSignalRef"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ComponentSignalRef
        return ComponentSignalRef(entlib.load_node_file(sourcefile, entlib.get_schema(ComponentSignalRef.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ComponentSignalRef
        return ComponentSignalRef(entlib.make_node(ComponentSignalRef.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Signal(self):  # type: ()->ClassMemberRef
        return ClassMemberRef(self._node.at("Signal"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




