
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.String import *


class AnimationPlaylistGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimationPlaylistGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(AnimationPlaylistGD.schema_name))
    @property
    def PlayAnim(self): return (lambda n: PrimArray(String, n))(self._node.at("PlayAnim"))
    @PlayAnim.setter
    def PlayAnim(self, val): self.PlayAnim.set(val)
    @property
    def PlayAnimInputID(self): return Int(self._node.at("PlayAnimInputID"))
    @PlayAnimInputID.setter
    def PlayAnimInputID(self, val): self.PlayAnimInputID.set(val)
    @property
    def RandomizeStartTime(self): return Bool(self._node.at("RandomizeStartTime"))
    @RandomizeStartTime.setter
    def RandomizeStartTime(self, val): self.RandomizeStartTime.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




