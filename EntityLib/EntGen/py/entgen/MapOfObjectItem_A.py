
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *

from EntityLibPy import Node

class MapOfObjectItem_A(HelperObject):

    @property
    def Value(self):  # type: ()->String
        return String(self._node.at("Value"))
    @Value.setter
    def Value(self, val): self.Value.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




