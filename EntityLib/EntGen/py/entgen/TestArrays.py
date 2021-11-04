
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_ import *
from entgen.Float import *

from EntityLibPy import Node

class TestArrays(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/TestArrays"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TestArrays
        return TestArrays(entlib.load_node_file(sourcefile, entlib.get_schema(TestArrays.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TestArrays
        return TestArrays(entlib.make_node(TestArrays.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DefaultValue(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("DefaultValue"))
    @DefaultValue.setter
    def DefaultValue(self, val): self.DefaultValue.set(val)
    @property
    def OverridedDefaultValue(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("OverridedDefaultValue"))
    @OverridedDefaultValue.setter
    def OverridedDefaultValue(self, val): self.OverridedDefaultValue.set(val)
    @property
    def OverridedPrefabValue(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("OverridedPrefabValue"))
    @OverridedPrefabValue.setter
    def OverridedPrefabValue(self, val): self.OverridedPrefabValue.set(val)
    @property
    def PrefabValue(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("PrefabValue"))
    @PrefabValue.setter
    def PrefabValue(self, val): self.PrefabValue.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def Variant(self):  # type: ()->variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_
        return variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_(self._node.at("Variant"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




