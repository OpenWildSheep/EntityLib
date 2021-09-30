
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *


class StaticObjectGD(HelperObject):
    schema_name = "./MergedComponents.json#/definitions/StaticObjectGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(StaticObjectGD.schema_name))
    @property
    def EDITOR_IsCave(self): return Bool(self._node.at("EDITOR_IsCave"))
    @EDITOR_IsCave.setter
    def EDITOR_IsCave(self, val): self.EDITOR_IsCave.set(val)
    @property
    def EDITOR_UsedInMultiLayerHeightmap(self): return Bool(self._node.at("EDITOR_UsedInMultiLayerHeightmap"))
    @EDITOR_UsedInMultiLayerHeightmap.setter
    def EDITOR_UsedInMultiLayerHeightmap(self, val): self.EDITOR_UsedInMultiLayerHeightmap.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def Visual(self): return Bool(self._node.at("Visual"))
    @Visual.setter
    def Visual(self, val): self.Visual.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




