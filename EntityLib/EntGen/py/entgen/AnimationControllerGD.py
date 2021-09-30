
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.AnimMirroringData import *
from entgen.ComponentGD import *
from entgen.Float import *


class AnimationControllerGD(HelperObject):
    schema_name = "./MergedComponents.json#/definitions/AnimationControllerGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(AnimationControllerGD.schema_name))
    @property
    def EDITOR_skeleton(self): return String(self._node.at("EDITOR_skeleton"))
    @EDITOR_skeleton.setter
    def EDITOR_skeleton(self, val): self.EDITOR_skeleton.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def animDatabase(self): return String(self._node.at("animDatabase"))
    @animDatabase.setter
    def animDatabase(self, val): self.animDatabase.set(val)
    @property
    def mirroringData(self): return AnimMirroringData(self._node.at("mirroringData"))
    @property
    def romLookAtInfluence(self): return Float(self._node.at("romLookAtInfluence"))
    @romLookAtInfluence.setter
    def romLookAtInfluence(self, val): self.romLookAtInfluence.set(val)
    @property
    def skeleton(self): return String(self._node.at("skeleton"))
    @skeleton.setter
    def skeleton(self, val): self.skeleton.set(val)
    @property
    def syncDataName(self): return String(self._node.at("syncDataName"))
    @syncDataName.setter
    def syncDataName(self, val): self.syncDataName.set(val)
    pass




