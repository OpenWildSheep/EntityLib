
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_ import *
from entgen.UnionObjectArrayItem import *
from entgen.variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_ import *


class TestUnion(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/TestUnion"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(TestUnion.schema_name))
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def Union(self): return variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_(self._node.at("Union"))
    @property
    def UnionArray(self): return (lambda n: Array(variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_, n))(self._node.at("UnionArray"))
    @property
    def UnionObjectArray(self): return (lambda n: Array(UnionObjectArrayItem, n))(self._node.at("UnionObjectArray"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




