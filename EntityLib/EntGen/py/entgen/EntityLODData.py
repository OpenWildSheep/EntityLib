
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.EntityRef import *
from entgen.Float import *

from EntityLibPy import Node

class EntityLODData(HelperObject):
    schema_name = "EntityLODData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityLODData
        return EntityLODData(entlib.load_node_file(sourcefile, entlib.get_schema(EntityLODData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityLODData
        return EntityLODData(entlib.make_node(EntityLODData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("EntityRef"))
    @EntityRef.setter
    def EntityRef(self, val): self.EntityRef.set(val)
    @property
    def MaxDist(self):  # type: ()->Float
        return Float(self._node.at("MaxDist"))
    @MaxDist.setter
    def MaxDist(self, val): self.MaxDist.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




