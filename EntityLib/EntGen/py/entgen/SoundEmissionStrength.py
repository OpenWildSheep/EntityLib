
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.SoundEmissionStrength import *
from entgen.String import *
from entgen.Bool import *

from EntityLibPy import Node

class soundEmissionStrength(HelperObject):

    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def engaged(self):  # type: ()->Bool
        return Bool(self._node.at("engaged"))
    @engaged.setter
    def engaged(self, val): self.engaged.set(val)
    @property
    def val(self):  # type: ()->SoundEmissionStrength
        return SoundEmissionStrength(self._node.at("val"))
    @val.setter
    def val(self, val): self.val.set(val)
    pass




