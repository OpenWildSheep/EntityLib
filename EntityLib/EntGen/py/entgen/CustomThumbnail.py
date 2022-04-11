
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.ThumbPath import *

from EntityLibPy import Node

class CustomThumbnail(HelperObject):
    schema_name = "CustomThumbnail"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CustomThumbnail
        return CustomThumbnail(entlib.load_node_file(sourcefile, entlib.get_schema(CustomThumbnail.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CustomThumbnail
        return CustomThumbnail(entlib.make_node(CustomThumbnail.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def Thumbnail(self):  # type: ()->ThumbPath
        return ThumbPath(self._node.at("Thumbnail"))
    @Thumbnail.setter
    def Thumbnail(self, val): self.Thumbnail.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




