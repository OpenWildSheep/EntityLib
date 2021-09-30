
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *


class WildObject(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/WildObject"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(WildObject.schema_name))
    @property
    def GdPath(self): return String(self._node.at("GdPath"))
    @GdPath.setter
    def GdPath(self, val): self.GdPath.set(val)
    @property
    def ObjectType(self): return String(self._node.at("ObjectType"))
    @ObjectType.setter
    def ObjectType(self, val): self.ObjectType.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




