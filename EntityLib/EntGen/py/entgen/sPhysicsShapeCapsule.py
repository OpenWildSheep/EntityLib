
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *


class sPhysicsShapeCapsule(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sPhysicsShapeCapsule"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(sPhysicsShapeCapsule.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def length(self): return Float(self._node.at("length"))
    @length.setter
    def length(self, val): self.length.set(val)
    @property
    def radius(self): return Float(self._node.at("radius"))
    @radius.setter
    def radius(self, val): self.radius.set(val)
    pass




