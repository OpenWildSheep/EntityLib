
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.EntityRef import *
from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class ShapeshiftStatueGD(HelperObject):
    schema_name = "ShapeshiftStatueGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ShapeshiftStatueGD
        return ShapeshiftStatueGD(entlib.load_node_file(sourcefile, entlib.get_schema(ShapeshiftStatueGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ShapeshiftStatueGD
        return ShapeshiftStatueGD(entlib.make_node(ShapeshiftStatueGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AssociatedEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("AssociatedEntityRef"))
    @AssociatedEntityRef.setter
    def AssociatedEntityRef(self, val): self.AssociatedEntityRef.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




