
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.StrongAttackData import *

from EntityLibPy import Node

class strongAttackData(HelperObject):

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
    def val(self):  # type: ()->StrongAttackData
        return StrongAttackData(self._node.at("val"))
    pass



