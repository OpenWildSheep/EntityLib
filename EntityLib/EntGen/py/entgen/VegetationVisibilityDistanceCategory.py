
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class VegetationVisibilityDistanceCategory(HelperObject):
    schema_name = "VegetationVisibilityDistanceCategory"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->VegetationVisibilityDistanceCategory
        return VegetationVisibilityDistanceCategory(entlib.load_node_file(sourcefile, entlib.get_schema(VegetationVisibilityDistanceCategory.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->VegetationVisibilityDistanceCategory
        return VegetationVisibilityDistanceCategory(entlib.make_node(VegetationVisibilityDistanceCategory.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Name(self):  # type: ()->String
        return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def VisibilityDistance(self):  # type: ()->Float
        return Float(self._node.at("VisibilityDistance"))
    @VisibilityDistance.setter
    def VisibilityDistance(self, val): self.VisibilityDistance.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




