# automatically generated by the FlatBuffers compiler, do not modify

# namespace: WildRPC

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class Float(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAs(cls, buf, offset=0):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = Float()
        x.Init(buf, n + offset)
        return x

    @classmethod
    def GetRootAsFloat(cls, buf, offset=0):
        """This method is deprecated. Please switch to GetRootAs."""
        return cls.GetRootAs(buf, offset)
    # Float
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # Float
    def Value(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            return self._tab.Get(flatbuffers.number_types.Float32Flags, o + self._tab.Pos)
        return 0.0

def Start(builder): builder.StartObject(1)
def FloatStart(builder):
    """This method is deprecated. Please switch to Start."""
    return Start(builder)
def AddValue(builder, value): builder.PrependFloat32Slot(0, value, 0.0)
def FloatAddValue(builder, value):
    """This method is deprecated. Please switch to AddValue."""
    return AddValue(builder, value)
def End(builder): return builder.EndObject()
def FloatEnd(builder):
    """This method is deprecated. Please switch to End."""
    return End(builder)

class FloatT(object):

    # FloatT
    def __init__(self):
        self.value = 0.0  # type: float

    @classmethod
    def InitFromBuf(cls, buf, pos):
        float = Float()
        float.Init(buf, pos)
        return cls.InitFromObj(float)

    @classmethod
    def InitFromObj(cls, float):
        x = FloatT()
        x._UnPack(float)
        return x

    # FloatT
    def _UnPack(self, float):
        if float is None:
            return
        self.value = float.Value()

    # FloatT
    def Pack(self, builder):
        Start(builder)
        AddValue(builder, self.value)
        float = End(builder)
        return float
