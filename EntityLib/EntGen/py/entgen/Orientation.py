
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Quat import *


class Orientation(HelperObject):

    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def engaged(self): return Bool(self._node.at("engaged"))
    @engaged.setter
    def engaged(self, val): self.engaged.set(val)
    @property
    def val(self): return Quat(self._node.at("val"))
    @val.setter
    def val(self, val): self.val.set(val)
    pass




