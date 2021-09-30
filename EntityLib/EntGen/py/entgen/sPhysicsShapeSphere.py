
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *


class sPhysicsShapeSphere(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sPhysicsShapeSphere"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(sPhysicsShapeSphere.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def radius(self): return Float(self._node.at("radius"))
    @radius.setter
    def radius(self, val): self.radius.set(val)
    pass




