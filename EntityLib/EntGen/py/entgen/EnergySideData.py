
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.EntityRef import *

from EntityLibPy import Node

class EnergySideData(HelperObject):
    schema_name = "EnergySideData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EnergySideData
        return EnergySideData(entlib.load_node_file(sourcefile, entlib.get_schema(EnergySideData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EnergySideData
        return EnergySideData(entlib.make_node(EnergySideData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("EntityRef"))
    @EntityRef.setter
    def EntityRef(self, val): self.EntityRef.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




