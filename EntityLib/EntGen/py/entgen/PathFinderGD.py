
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.Size import *
from entgen.String import *
from entgen.AreaNavigation import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class PathFinderGD(HelperObject):
    schema_name = "PathFinderGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PathFinderGD
        return PathFinderGD(entlib.load_node_file(sourcefile, entlib.get_schema(PathFinderGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PathFinderGD
        return PathFinderGD(entlib.make_node(PathFinderGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AreaNavigation(self):  # type: ()->AreaNavigation
        return AreaNavigation(self._node.at("AreaNavigation"))
    @property
    def Size(self):  # type: ()->Size
        return Size(self._node.at("Size"))
    @Size.setter
    def Size(self, val): self.Size.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




