
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class WildObject(HelperObject):
    schema_name = "WildObject"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->WildObject
        return WildObject(entlib.load_node_file(sourcefile, entlib.get_schema(WildObject.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->WildObject
        return WildObject(entlib.make_node(WildObject.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def GdPath(self):  # type: ()->String
        return String(self._node.at("GdPath"))
    @GdPath.setter
    def GdPath(self, val): self.GdPath.set(val)
    @property
    def ObjectType(self):  # type: ()->String
        return String(self._node.at("ObjectType"))
    @ObjectType.setter
    def ObjectType(self, val): self.ObjectType.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




