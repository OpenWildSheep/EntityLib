# automatically generated by the FlatBuffers compiler, do not modify

# namespace: WildRPC

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class Vector3(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAsVector3(cls, buf, offset):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = Vector3()
        x.Init(buf, n + offset)
        return x

    # Vector3
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # Vector3
    def X(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            return self._tab.Get(flatbuffers.number_types.Float32Flags, o + self._tab.Pos)
        return 0.0

    # Vector3
    def Y(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        if o != 0:
            return self._tab.Get(flatbuffers.number_types.Float32Flags, o + self._tab.Pos)
        return 0.0

    # Vector3
    def Z(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(8))
        if o != 0:
            return self._tab.Get(flatbuffers.number_types.Float32Flags, o + self._tab.Pos)
        return 0.0

def Vector3Start(builder): builder.StartObject(3)
def Vector3AddX(builder, x): builder.PrependFloat32Slot(0, x, 0.0)
def Vector3AddY(builder, y): builder.PrependFloat32Slot(1, y, 0.0)
def Vector3AddZ(builder, z): builder.PrependFloat32Slot(2, z, 0.0)
def Vector3End(builder): return builder.EndObject()