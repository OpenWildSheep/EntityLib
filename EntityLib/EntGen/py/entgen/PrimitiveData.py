
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *


class PrimitiveData(HelperObject):

    @property
    def Height(self): return Float(self._node.at("Height"))
    @Height.setter
    def Height(self, val): self.Height.set(val)
    @property
    def Length(self): return Float(self._node.at("Length"))
    @Length.setter
    def Length(self, val): self.Length.set(val)
    @property
    def Radius(self): return Float(self._node.at("Radius"))
    @Radius.setter
    def Radius(self, val): self.Radius.set(val)
    @property
    def Width(self): return Float(self._node.at("Width"))
    @Width.setter
    def Width(self, val): self.Width.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




