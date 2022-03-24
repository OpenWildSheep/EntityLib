
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentInputBase import *
from entgen.Enabled import *

from EntityLibPy import Node

class ComponentInput(HelperObject):
    schema_name = "ComponentInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ComponentInput
        return ComponentInput(entlib.load_node_file(sourcefile, entlib.get_schema(ComponentInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ComponentInput
        return ComponentInput(entlib.make_node(ComponentInput.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Enabled(self):  # type: ()->Enabled
        return Enabled(self._node.at("Enabled"))
    @property
    def Super(self):  # type: ()->ComponentInputBase
        return ComponentInputBase(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




