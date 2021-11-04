
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.TagsList import *

from EntityLibPy import Node

class PathNodeGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PathNodeGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PathNodeGD
        return PathNodeGD(entlib.load_node_file(sourcefile, entlib.get_schema(PathNodeGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PathNodeGD
        return PathNodeGD(entlib.make_node(PathNodeGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Radius(self):  # type: ()->Float
        return Float(self._node.at("Radius"))
    @Radius.setter
    def Radius(self, val): self.Radius.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def Tags(self):  # type: ()->TagsList
        return TagsList(self._node.at("Tags"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




