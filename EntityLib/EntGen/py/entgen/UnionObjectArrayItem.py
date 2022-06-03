
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_ import *

from EntityLibPy import Node

class UnionObjectArrayItem(HelperObject):

    @property
    def Union(self):  # type: ()->variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_
        return variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_(self._node.at("Union"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




