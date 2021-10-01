
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_ import *

from EntityLibPy import Node

class TypedValue(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/TypedValue"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TypedValue
        return TypedValue(entlib.load_node_file(sourcefile, entlib.get_schema(TypedValue.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TypedValue
        return TypedValue(entlib.make_node(TypedValue.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Alias(self):  # type: ()->String
        return String(self._node.at("Alias"))
    @Alias.setter
    def Alias(self, val): self.Alias.set(val)
    @property
    def Reference(self):  # type: ()->String
        return String(self._node.at("Reference"))
    @Reference.setter
    def Reference(self, val): self.Reference.set(val)
    @property
    def Value(self):  # type: ()->variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_
        return variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_(self._node.at("Value"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




