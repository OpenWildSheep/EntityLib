
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *

from EntityLibPy import Node

class EDITOR_Mesh(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/EDITOR_Mesh"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EDITOR_Mesh
        return EDITOR_Mesh(entlib.load_node_file(sourcefile, entlib.get_schema(EDITOR_Mesh.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EDITOR_Mesh
        return EDITOR_Mesh(entlib.make_node(EDITOR_Mesh.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def id(self):  # type: ()->Int
        return Int(self._node.at("id"))
    @id.setter
    def id(self, val): self.id.set(val)
    @property
    def path(self):  # type: ()->String
        return String(self._node.at("path"))
    @path.setter
    def path(self, val): self.path.set(val)
    pass




