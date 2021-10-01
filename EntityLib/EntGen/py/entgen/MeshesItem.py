
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *

from EntityLibPy import Node

class MeshesItem(HelperObject):

    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def mesh(self):  # type: ()->String
        return String(self._node.at("mesh"))
    @mesh.setter
    def mesh(self, val): self.mesh.set(val)
    pass




