
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *

from EntityLibPy import Node

class sPhysicsShapeMesh(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sPhysicsShapeMesh"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sPhysicsShapeMesh
        return sPhysicsShapeMesh(entlib.load_node_file(sourcefile, entlib.get_schema(sPhysicsShapeMesh.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sPhysicsShapeMesh
        return sPhysicsShapeMesh(entlib.make_node(sPhysicsShapeMesh.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def path(self):  # type: ()->String
        return String(self._node.at("path"))
    @path.setter
    def path(self, val): self.path.set(val)
    pass




