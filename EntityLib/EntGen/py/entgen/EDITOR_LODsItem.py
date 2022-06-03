
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.String import *

from EntityLibPy import Node

class EDITOR_LODsItem(HelperObject):

    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def lod(self):  # type: ()->Int
        return Int(self._node.at("lod"))
    @lod.setter
    def lod(self, val): self.lod.set(val)
    @property
    def wvis(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("wvis"))
    @wvis.setter
    def wvis(self, val): self.wvis.set(val)
    pass




