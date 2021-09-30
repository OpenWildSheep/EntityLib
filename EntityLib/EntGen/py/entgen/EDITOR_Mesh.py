
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *


class EDITOR_Mesh(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/EDITOR_Mesh"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(EDITOR_Mesh.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def id(self): return Int(self._node.at("id"))
    @id.setter
    def id(self, val): self.id.set(val)
    @property
    def path(self): return String(self._node.at("path"))
    @path.setter
    def path(self, val): self.path.set(val)
    pass




