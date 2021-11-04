
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.String import *

from EntityLibPy import Node

class AnimationPlaylistGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimationPlaylistGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationPlaylistGD
        return AnimationPlaylistGD(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationPlaylistGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationPlaylistGD
        return AnimationPlaylistGD(entlib.make_node(AnimationPlaylistGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def PlayAnim(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("PlayAnim"))
    @PlayAnim.setter
    def PlayAnim(self, val): self.PlayAnim.set(val)
    @property
    def PlayAnimInputID(self):  # type: ()->Int
        return Int(self._node.at("PlayAnimInputID"))
    @PlayAnimInputID.setter
    def PlayAnimInputID(self, val): self.PlayAnimInputID.set(val)
    @property
    def RandomizeStartTime(self):  # type: ()->Bool
        return Bool(self._node.at("RandomizeStartTime"))
    @RandomizeStartTime.setter
    def RandomizeStartTime(self, val): self.RandomizeStartTime.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




