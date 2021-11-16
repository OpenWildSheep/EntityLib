
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class Mesh(HelperObject):
    schema_name = "Mesh"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Mesh
        return Mesh(entlib.load_node_file(sourcefile, entlib.get_schema(Mesh.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Mesh
        return Mesh(entlib.make_node(Mesh.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def File(self):  # type: ()->String
        return String(self._node.at("File"))
    @File.setter
    def File(self, val): self.File.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




