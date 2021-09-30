
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Vector3 import *


class sPhysicsShapeBox(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sPhysicsShapeBox"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(sPhysicsShapeBox.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def size(self): return Vector3(self._node.at("size"))
    @size.setter
    def size(self, val): self.size.set(val)
    pass




