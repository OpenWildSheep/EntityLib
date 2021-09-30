
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *


class MeshesItem(HelperObject):

    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def mesh(self): return String(self._node.at("mesh"))
    @mesh.setter
    def mesh(self, val): self.mesh.set(val)
    pass




