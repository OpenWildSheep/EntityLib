
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class PrimitiveData(HelperObject):

    @property
    def Height(self):  # type: ()->Float
        return Float(self._node.at("Height"))
    @Height.setter
    def Height(self, val): self.Height.set(val)
    @property
    def Length(self):  # type: ()->Float
        return Float(self._node.at("Length"))
    @Length.setter
    def Length(self, val): self.Length.set(val)
    @property
    def Radius(self):  # type: ()->Float
        return Float(self._node.at("Radius"))
    @Radius.setter
    def Radius(self, val): self.Radius.set(val)
    @property
    def Width(self):  # type: ()->Float
        return Float(self._node.at("Width"))
    @Width.setter
    def Width(self, val): self.Width.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




