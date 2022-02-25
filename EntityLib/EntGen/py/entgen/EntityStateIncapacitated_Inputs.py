
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class EntityStateIncapacitated_Inputs(HelperObject):
    schema_name = "EntityStateIncapacitated::Inputs"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateIncapacitated_Inputs
        return EntityStateIncapacitated_Inputs(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateIncapacitated_Inputs.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateIncapacitated_Inputs
        return EntityStateIncapacitated_Inputs(entlib.make_node(EntityStateIncapacitated_Inputs.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Time(self):  # type: ()->Float
        return Float(self._node.at("Time"))
    @Time.setter
    def Time(self, val): self.Time.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




