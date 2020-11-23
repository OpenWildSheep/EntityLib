# automatically generated by the FlatBuffers compiler, do not modify

# namespace: WildRPC

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class UInt3(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAsUInt3(cls, buf, offset):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = UInt3()
        x.Init(buf, n + offset)
        return x

    # UInt3
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # UInt3
    def X(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            return self._tab.Get(flatbuffers.number_types.Uint32Flags, o + self._tab.Pos)
        return 0

    # UInt3
    def Y(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        if o != 0:
            return self._tab.Get(flatbuffers.number_types.Uint32Flags, o + self._tab.Pos)
        return 0

    # UInt3
    def Z(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(8))
        if o != 0:
            return self._tab.Get(flatbuffers.number_types.Uint32Flags, o + self._tab.Pos)
        return 0

def UInt3Start(builder): builder.StartObject(3)
def UInt3AddX(builder, x): builder.PrependUint32Slot(0, x, 0)
def UInt3AddY(builder, y): builder.PrependUint32Slot(1, y, 0)
def UInt3AddZ(builder, z): builder.PrependUint32Slot(2, z, 0)
def UInt3End(builder): return builder.EndObject()