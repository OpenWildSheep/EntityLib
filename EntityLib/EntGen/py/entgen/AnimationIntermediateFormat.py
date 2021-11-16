
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Float import *
from entgen.BlendShapeAnimation import *
from entgen.BoneAnimation import *

from EntityLibPy import Node

class AnimationIntermediateFormat(HelperObject):
    schema_name = "AnimationIntermediateFormat"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationIntermediateFormat
        return AnimationIntermediateFormat(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationIntermediateFormat.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationIntermediateFormat
        return AnimationIntermediateFormat(entlib.make_node(AnimationIntermediateFormat.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BlendShapeAnimations(self):  # type: ()->Array[BlendShapeAnimation]
        return (lambda n: Array(BlendShapeAnimation, n))(self._node.at("BlendShapeAnimations"))
    @property
    def BoneAnimations(self):  # type: ()->Array[BoneAnimation]
        return (lambda n: Array(BoneAnimation, n))(self._node.at("BoneAnimations"))
    @property
    def EndFrame(self):  # type: ()->Int
        return Int(self._node.at("EndFrame"))
    @EndFrame.setter
    def EndFrame(self, val): self.EndFrame.set(val)
    @property
    def EndTime(self):  # type: ()->Float
        return Float(self._node.at("EndTime"))
    @EndTime.setter
    def EndTime(self, val): self.EndTime.set(val)
    @property
    def NumFrames(self):  # type: ()->Int
        return Int(self._node.at("NumFrames"))
    @NumFrames.setter
    def NumFrames(self, val): self.NumFrames.set(val)
    @property
    def Period(self):  # type: ()->Float
        return Float(self._node.at("Period"))
    @Period.setter
    def Period(self, val): self.Period.set(val)
    @property
    def StartFrame(self):  # type: ()->Int
        return Int(self._node.at("StartFrame"))
    @StartFrame.setter
    def StartFrame(self, val): self.StartFrame.set(val)
    @property
    def StartTime(self):  # type: ()->Float
        return Float(self._node.at("StartTime"))
    @StartTime.setter
    def StartTime(self, val): self.StartTime.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




