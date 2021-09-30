
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.EntityRef import *
from entgen.Float import *


class EntityLODData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EntityLODData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(EntityLODData.schema_name))
    @property
    def EntityRef(self): return EntityRef(self._node.at("EntityRef"))
    @EntityRef.setter
    def EntityRef(self, val): self.EntityRef.set(val)
    @property
    def MaxDist(self): return Float(self._node.at("MaxDist"))
    @MaxDist.setter
    def MaxDist(self, val): self.MaxDist.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




