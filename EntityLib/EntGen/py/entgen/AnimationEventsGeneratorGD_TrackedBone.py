
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *


class AnimationEventsGeneratorGD_TrackedBone(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimationEventsGeneratorGD::TrackedBone"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(AnimationEventsGeneratorGD_TrackedBone.schema_name))
    @property
    def Name(self): return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def OffsetFrameCountStart(self): return Int(self._node.at("OffsetFrameCountStart"))
    @OffsetFrameCountStart.setter
    def OffsetFrameCountStart(self, val): self.OffsetFrameCountStart.set(val)
    @property
    def OffsetFrameCountStop(self): return Int(self._node.at("OffsetFrameCountStop"))
    @OffsetFrameCountStop.setter
    def OffsetFrameCountStop(self, val): self.OffsetFrameCountStop.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




