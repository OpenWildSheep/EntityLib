
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class sPhysicsShapeSphere(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sPhysicsShapeSphere"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sPhysicsShapeSphere
        return sPhysicsShapeSphere(entlib.load_node_file(sourcefile, entlib.get_schema(sPhysicsShapeSphere.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sPhysicsShapeSphere
        return sPhysicsShapeSphere(entlib.make_node(sPhysicsShapeSphere.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def radius(self):  # type: ()->Float
        return Float(self._node.at("radius"))
    @radius.setter
    def radius(self, val): self.radius.set(val)
    pass




