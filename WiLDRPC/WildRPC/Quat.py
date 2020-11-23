# automatically generated by the FlatBuffers compiler, do not modify

# namespace: WildRPC

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class Quat(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAsQuat(cls, buf, offset):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = Quat()
        x.Init(buf, n + offset)
        return x

    # Quat
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # Quat
    def X(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            return self._tab.Get(flatbuffers.number_types.Float32Flags, o + self._tab.Pos)
        return 0.0

    # Quat
    def Y(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        if o != 0:
            return self._tab.Get(flatbuffers.number_types.Float32Flags, o + self._tab.Pos)
        return 0.0

    # Quat
    def Z(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(8))
        if o != 0:
            return self._tab.Get(flatbuffers.number_types.Float32Flags, o + self._tab.Pos)
        return 0.0

    # Quat
    def W(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(10))
        if o != 0:
            return self._tab.Get(flatbuffers.number_types.Float32Flags, o + self._tab.Pos)
        return 0.0

def QuatStart(builder): builder.StartObject(4)
def QuatAddX(builder, x): builder.PrependFloat32Slot(0, x, 0.0)
def QuatAddY(builder, y): builder.PrependFloat32Slot(1, y, 0.0)
def QuatAddZ(builder, z): builder.PrependFloat32Slot(2, z, 0.0)
def QuatAddW(builder, w): builder.PrependFloat32Slot(3, w, 0.0)
def QuatEnd(builder): return builder.EndObject()