
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.MeshesItem import *

from EntityLibPy import Node

class RUNTIME_LODsItem(HelperObject):

    @property
    def Meshes(self):  # type: ()->Array[MeshesItem]
        return (lambda n: Array(MeshesItem, n))(self._node.at("Meshes"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




