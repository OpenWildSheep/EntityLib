
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.variant_string_bool_s32_float_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_Vector2Vec_Vector3Vec_PositionVec_ import *

from EntityLibPy import Node

class BehaviorTypedValue(HelperObject):
    schema_name = "BehaviorTypedValue"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BehaviorTypedValue
        return BehaviorTypedValue(entlib.load_node_file(sourcefile, entlib.get_schema(BehaviorTypedValue.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BehaviorTypedValue
        return BehaviorTypedValue(entlib.make_node(BehaviorTypedValue.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Value(self):  # type: ()->variant_string_bool_s32_float_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_Vector2Vec_Vector3Vec_PositionVec_
        return variant_string_bool_s32_float_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_Vector2Vec_Vector3Vec_PositionVec_(self._node.at("Value"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




