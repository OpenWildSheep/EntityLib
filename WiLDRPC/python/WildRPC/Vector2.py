# automatically generated by the FlatBuffers compiler, do not modify

# namespace: WildRPC

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class Vector2(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAs(cls, buf, offset=0):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = Vector2()
        x.Init(buf, n + offset)
        return x

    @classmethod
    def GetRootAsVector2(cls, buf, offset=0):
        """This method is deprecated. Please switch to GetRootAs."""
        return cls.GetRootAs(buf, offset)
    # Vector2
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # Vector2
    def X(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            return self._tab.Get(flatbuffers.number_types.Float32Flags, o + self._tab.Pos)
        return 0.0

    # Vector2
    def Y(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        if o != 0:
            return self._tab.Get(flatbuffers.number_types.Float32Flags, o + self._tab.Pos)
        return 0.0

def Start(builder): builder.StartObject(2)
def Vector2Start(builder):
    """This method is deprecated. Please switch to Start."""
    return Start(builder)
def AddX(builder, x): builder.PrependFloat32Slot(0, x, 0.0)
def Vector2AddX(builder, x):
    """This method is deprecated. Please switch to AddX."""
    return AddX(builder, x)
def AddY(builder, y): builder.PrependFloat32Slot(1, y, 0.0)
def Vector2AddY(builder, y):
    """This method is deprecated. Please switch to AddY."""
    return AddY(builder, y)
def End(builder): return builder.EndObject()
def Vector2End(builder):
    """This method is deprecated. Please switch to End."""
    return End(builder)