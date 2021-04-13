# automatically generated by the FlatBuffers compiler, do not modify

# namespace: WBIN

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class Bool3(object):
    __slots__ = ['_tab']

    @classmethod
    def SizeOf(cls):
        return 3

    # Bool3
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # Bool3
    def X(self): return self._tab.Get(flatbuffers.number_types.BoolFlags, self._tab.Pos + flatbuffers.number_types.UOffsetTFlags.py_type(0))
    # Bool3
    def Y(self): return self._tab.Get(flatbuffers.number_types.BoolFlags, self._tab.Pos + flatbuffers.number_types.UOffsetTFlags.py_type(1))
    # Bool3
    def Z(self): return self._tab.Get(flatbuffers.number_types.BoolFlags, self._tab.Pos + flatbuffers.number_types.UOffsetTFlags.py_type(2))

def CreateBool3(builder, x, y, z):
    builder.Prep(1, 3)
    builder.PrependBool(z)
    builder.PrependBool(y)
    builder.PrependBool(x)
    return builder.Offset()


class Bool3T(object):

    # Bool3T
    def __init__(self):
        self.x = False  # type: bool
        self.y = False  # type: bool
        self.z = False  # type: bool

    @classmethod
    def InitFromBuf(cls, buf, pos):
        bool3 = Bool3()
        bool3.Init(buf, pos)
        return cls.InitFromObj(bool3)

    @classmethod
    def InitFromObj(cls, bool3):
        x = Bool3T()
        x._UnPack(bool3)
        return x

    # Bool3T
    def _UnPack(self, bool3):
        if bool3 is None:
            return
        self.x = bool3.X()
        self.y = bool3.Y()
        self.z = bool3.Z()

    # Bool3T
    def Pack(self, builder):
        return CreateBool3(builder, self.x, self.y, self.z)
