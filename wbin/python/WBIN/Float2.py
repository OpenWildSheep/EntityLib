# automatically generated by the FlatBuffers compiler, do not modify

# namespace: WBIN

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class Float2(object):
    __slots__ = ['_tab']

    @classmethod
    def SizeOf(cls):
        return 8

    # Float2
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # Float2
    def X(self): return self._tab.Get(flatbuffers.number_types.Float32Flags, self._tab.Pos + flatbuffers.number_types.UOffsetTFlags.py_type(0))
    # Float2
    def Y(self): return self._tab.Get(flatbuffers.number_types.Float32Flags, self._tab.Pos + flatbuffers.number_types.UOffsetTFlags.py_type(4))

def CreateFloat2(builder, x, y):
    builder.Prep(4, 8)
    builder.PrependFloat32(y)
    builder.PrependFloat32(x)
    return builder.Offset()


class Float2T(object):

    # Float2T
    def __init__(self):
        self.x = 0.0  # type: float
        self.y = 0.0  # type: float

    @classmethod
    def InitFromBuf(cls, buf, pos):
        float2 = Float2()
        float2.Init(buf, pos)
        return cls.InitFromObj(float2)

    @classmethod
    def InitFromObj(cls, float2):
        x = Float2T()
        x._UnPack(float2)
        return x

    # Float2T
    def _UnPack(self, float2):
        if float2 is None:
            return
        self.x = float2.X()
        self.y = float2.Y()

    # Float2T
    def Pack(self, builder):
        return CreateFloat2(builder, self.x, self.y)
