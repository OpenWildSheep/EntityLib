
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_ import *
from entgen.UnionObjectArrayItem import *
from entgen.variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_ import *

from EntityLibPy import Node

class TestUnion(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/TestUnion"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TestUnion
        return TestUnion(entlib.load_node_file(sourcefile, entlib.get_schema(TestUnion.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TestUnion
        return TestUnion(entlib.make_node(TestUnion.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def Union(self):  # type: ()->variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_
        return variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_(self._node.at("Union"))
    @property
    def UnionArray(self):  # type: ()->Array[variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_]
        return (lambda n: Array(variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_, n))(self._node.at("UnionArray"))
    @property
    def UnionObjectArray(self):  # type: ()->Array[UnionObjectArrayItem]
        return (lambda n: Array(UnionObjectArrayItem, n))(self._node.at("UnionObjectArray"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




