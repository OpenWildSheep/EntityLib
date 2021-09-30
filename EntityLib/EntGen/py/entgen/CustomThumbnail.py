
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.ThumbPath import *


class CustomThumbnail(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/CustomThumbnail"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(CustomThumbnail.schema_name))
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def Thumbnail(self): return ThumbPath(self._node.at("Thumbnail"))
    @Thumbnail.setter
    def Thumbnail(self, val): self.Thumbnail.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




