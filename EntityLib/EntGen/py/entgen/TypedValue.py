
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_ import *


class TypedValue(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/TypedValue"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(TypedValue.schema_name))
    @property
    def Alias(self): return String(self._node.at("Alias"))
    @Alias.setter
    def Alias(self, val): self.Alias.set(val)
    @property
    def Reference(self): return String(self._node.at("Reference"))
    @Reference.setter
    def Reference(self, val): self.Reference.set(val)
    @property
    def Value(self): return variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_(self._node.at("Value"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




