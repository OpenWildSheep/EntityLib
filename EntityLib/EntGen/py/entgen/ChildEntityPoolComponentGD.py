
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.EntityRef import *


class ChildEntityPoolComponentGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ChildEntityPoolComponentGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(ChildEntityPoolComponentGD.schema_name))
    @property
    def EntityRefs(self): return (lambda n: PrimArray(EntityRef, n))(self._node.at("EntityRefs"))
    @EntityRefs.setter
    def EntityRefs(self, val): self.EntityRefs.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




