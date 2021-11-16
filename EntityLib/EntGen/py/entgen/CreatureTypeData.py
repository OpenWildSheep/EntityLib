
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class CreatureTypeData(HelperObject):
    schema_name = "CreatureTypeData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CreatureTypeData
        return CreatureTypeData(entlib.load_node_file(sourcefile, entlib.get_schema(CreatureTypeData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CreatureTypeData
        return CreatureTypeData(entlib.make_node(CreatureTypeData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def name(self):  # type: ()->String
        return String(self._node.at("name"))
    @name.setter
    def name(self, val): self.name.set(val)
    @property
    def value(self):  # type: ()->Float
        return Float(self._node.at("value"))
    @value.setter
    def value(self, val): self.value.set(val)
    pass




