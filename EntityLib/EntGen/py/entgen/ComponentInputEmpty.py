
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentInputBase import *

from EntityLibPy import Node

class ComponentInputEmpty(HelperObject):
    schema_name = "ComponentInputEmpty"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ComponentInputEmpty
        return ComponentInputEmpty(entlib.load_node_file(sourcefile, entlib.get_schema(ComponentInputEmpty.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ComponentInputEmpty
        return ComponentInputEmpty(entlib.make_node(ComponentInputEmpty.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentInputBase
        return ComponentInputBase(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




