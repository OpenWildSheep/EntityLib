
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *

from EntityLibPy import Node

class MeshShape(HelperObject):
    schema_name = "MeshShape"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MeshShape
        return MeshShape(entlib.load_node_file(sourcefile, entlib.get_schema(MeshShape.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MeshShape
        return MeshShape(entlib.make_node(MeshShape.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Path(self):  # type: ()->String
        return String(self._node.at("Path"))
    @Path.setter
    def Path(self, val): self.Path.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




