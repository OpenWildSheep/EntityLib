
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.EntityRef import *


class ShapeshiftStatueGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ShapeshiftStatueGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(ShapeshiftStatueGD.schema_name))
    @property
    def AssociatedEntityRef(self): return EntityRef(self._node.at("AssociatedEntityRef"))
    @AssociatedEntityRef.setter
    def AssociatedEntityRef(self, val): self.AssociatedEntityRef.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




