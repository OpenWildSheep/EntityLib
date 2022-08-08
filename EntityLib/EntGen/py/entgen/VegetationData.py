
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.String import *

from EntityLibPy import Node

class VegetationData(HelperObject):
    schema_name = "VegetationData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->VegetationData
        return VegetationData(entlib.load_node_file(sourcefile, entlib.get_schema(VegetationData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->VegetationData
        return VegetationData(entlib.make_node(VegetationData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def GRCPath(self):  # type: ()->String
        return String(self._node.at("GRCPath"))
    @GRCPath.setter
    def GRCPath(self, val): self.GRCPath.set(val)
    @property
    def Name(self):  # type: ()->String
        return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def Tags(self):  # type: ()->PrimitiveSet[str]
        return (lambda n: PrimitiveSet(str, n))(self._node.at("Tags"))
    @property
    def VisibilityDistanceCategory(self):  # type: ()->String
        return String(self._node.at("VisibilityDistanceCategory"))
    @VisibilityDistanceCategory.setter
    def VisibilityDistanceCategory(self, val): self.VisibilityDistanceCategory.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass



