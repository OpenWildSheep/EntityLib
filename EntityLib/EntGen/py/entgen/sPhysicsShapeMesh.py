
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *


class sPhysicsShapeMesh(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sPhysicsShapeMesh"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(sPhysicsShapeMesh.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def path(self): return String(self._node.at("path"))
    @path.setter
    def path(self, val): self.path.set(val)
    pass




