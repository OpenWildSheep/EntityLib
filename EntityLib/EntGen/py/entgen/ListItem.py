
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.EntityRef import *

from EntityLibPy import Node

class ListItem(HelperObject):

    @property
    def EntityPath(self):  # type: ()->String
        return String(self._node.at("EntityPath"))
    @EntityPath.setter
    def EntityPath(self, val): self.EntityPath.set(val)
    @property
    def EntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("EntityRef"))
    @EntityRef.setter
    def EntityRef(self, val): self.EntityRef.set(val)
    @property
    def Tag(self):  # type: ()->String
        return String(self._node.at("Tag"))
    @Tag.setter
    def Tag(self, val): self.Tag.set(val)
    @property
    def Thumbnail(self):  # type: ()->String
        return String(self._node.at("Thumbnail"))
    @Thumbnail.setter
    def Thumbnail(self, val): self.Thumbnail.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




