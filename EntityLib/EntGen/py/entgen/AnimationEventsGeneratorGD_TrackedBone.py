
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *

from EntityLibPy import Node

class AnimationEventsGeneratorGD_TrackedBone(HelperObject):
    schema_name = "AnimationEventsGeneratorGD::TrackedBone"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationEventsGeneratorGD_TrackedBone
        return AnimationEventsGeneratorGD_TrackedBone(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationEventsGeneratorGD_TrackedBone.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationEventsGeneratorGD_TrackedBone
        return AnimationEventsGeneratorGD_TrackedBone(entlib.make_node(AnimationEventsGeneratorGD_TrackedBone.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Name(self):  # type: ()->String
        return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def OffsetFrameCountStart(self):  # type: ()->Int
        return Int(self._node.at("OffsetFrameCountStart"))
    @OffsetFrameCountStart.setter
    def OffsetFrameCountStart(self, val): self.OffsetFrameCountStart.set(val)
    @property
    def OffsetFrameCountStop(self):  # type: ()->Int
        return Int(self._node.at("OffsetFrameCountStop"))
    @OffsetFrameCountStop.setter
    def OffsetFrameCountStop(self, val): self.OffsetFrameCountStop.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




