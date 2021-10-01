
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Vector3 import *

from EntityLibPy import Node

class sPhysicsShapeBox(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sPhysicsShapeBox"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sPhysicsShapeBox
        return sPhysicsShapeBox(entlib.load_node_file(sourcefile, entlib.get_schema(sPhysicsShapeBox.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sPhysicsShapeBox
        return sPhysicsShapeBox(entlib.make_node(sPhysicsShapeBox.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def size(self):  # type: ()->Vector3
        return Vector3(self._node.at("size"))
    @size.setter
    def size(self, val): self.size.set(val)
    pass




