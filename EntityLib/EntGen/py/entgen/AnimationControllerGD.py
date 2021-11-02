
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.AnimMirroringData import *
from entgen.ComponentGD import *
from entgen.Float import *

from EntityLibPy import Node

class AnimationControllerGD(HelperObject):
    schema_name = "AnimationControllerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationControllerGD
        return AnimationControllerGD(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationControllerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationControllerGD
        return AnimationControllerGD(entlib.make_node(AnimationControllerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EDITOR_skeleton(self):  # type: ()->String
        return String(self._node.at("EDITOR_skeleton"))
    @EDITOR_skeleton.setter
    def EDITOR_skeleton(self, val): self.EDITOR_skeleton.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def animDatabase(self):  # type: ()->String
        return String(self._node.at("animDatabase"))
    @animDatabase.setter
    def animDatabase(self, val): self.animDatabase.set(val)
    @property
    def mirroringData(self):  # type: ()->AnimMirroringData
        return AnimMirroringData(self._node.at("mirroringData"))
    @property
    def romLookAtInfluence(self):  # type: ()->Float
        return Float(self._node.at("romLookAtInfluence"))
    @romLookAtInfluence.setter
    def romLookAtInfluence(self, val): self.romLookAtInfluence.set(val)
    @property
    def skeleton(self):  # type: ()->String
        return String(self._node.at("skeleton"))
    @skeleton.setter
    def skeleton(self, val): self.skeleton.set(val)
    @property
    def syncDataName(self):  # type: ()->String
        return String(self._node.at("syncDataName"))
    @syncDataName.setter
    def syncDataName(self, val): self.syncDataName.set(val)
    pass




