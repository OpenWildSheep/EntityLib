
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class sPhysicsShapeCapsule(HelperObject):
    schema_name = "sPhysicsShapeCapsule"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sPhysicsShapeCapsule
        return sPhysicsShapeCapsule(entlib.load_node_file(sourcefile, entlib.get_schema(sPhysicsShapeCapsule.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sPhysicsShapeCapsule
        return sPhysicsShapeCapsule(entlib.make_node(sPhysicsShapeCapsule.schema_name))
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




