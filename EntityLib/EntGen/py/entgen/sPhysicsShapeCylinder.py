
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class sPhysicsShapeCylinder(HelperObject):
    schema_name = "sPhysicsShapeCylinder"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sPhysicsShapeCylinder
        return sPhysicsShapeCylinder(entlib.load_node_file(sourcefile, entlib.get_schema(sPhysicsShapeCylinder.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sPhysicsShapeCylinder
        return sPhysicsShapeCylinder(entlib.make_node(sPhysicsShapeCylinder.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def length(self):  # type: ()->Float
        return Float(self._node.at("length"))
    @length.setter
    def length(self, val): self.length.set(val)
    @property
    def radius(self):  # type: ()->Float
        return Float(self._node.at("radius"))
    @radius.setter
    def radius(self, val): self.radius.set(val)
    pass




