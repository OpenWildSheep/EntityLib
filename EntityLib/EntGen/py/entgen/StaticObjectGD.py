
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class StaticObjectGD(HelperObject):
    schema_name = "StaticObjectGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->StaticObjectGD
        return StaticObjectGD(entlib.load_node_file(sourcefile, entlib.get_schema(StaticObjectGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->StaticObjectGD
        return StaticObjectGD(entlib.make_node(StaticObjectGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EDITOR_IsCave(self):  # type: ()->Bool
        return Bool(self._node.at("EDITOR_IsCave"))
    @EDITOR_IsCave.setter
    def EDITOR_IsCave(self, val): self.EDITOR_IsCave.set(val)
    @property
    def EDITOR_MergeInNavMesh(self):  # type: ()->Bool
        return Bool(self._node.at("EDITOR_MergeInNavMesh"))
    @EDITOR_MergeInNavMesh.setter
    def EDITOR_MergeInNavMesh(self, val): self.EDITOR_MergeInNavMesh.set(val)
    @property
    def EDITOR_UsedInMultiLayerHeightmap(self):  # type: ()->Bool
        return Bool(self._node.at("EDITOR_UsedInMultiLayerHeightmap"))
    @EDITOR_UsedInMultiLayerHeightmap.setter
    def EDITOR_UsedInMultiLayerHeightmap(self, val): self.EDITOR_UsedInMultiLayerHeightmap.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def Visual(self):  # type: ()->Bool
        return Bool(self._node.at("Visual"))
    @Visual.setter
    def Visual(self, val): self.Visual.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




