
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class SamplesPerAudioFrameEnum(Enum):
    _256 = "256"
    _512 = "512"
    _1024 = "1024"
    _2048 = "2048"


class SamplesPerAudioFrame(Primitive[SamplesPerAudioFrameEnum]):  # Enum
    def __init__(self, node):
        super(SamplesPerAudioFrame, self).__init__(SamplesPerAudioFrameEnum, node)
    schema_name = "SamplesPerAudioFrame"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> SamplesPerAudioFrame
        return SamplesPerAudioFrame(node)
    def set(self, val):  # type: (SamplesPerAudioFrameEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




