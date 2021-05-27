# automatically generated by the FlatBuffers compiler, do not modify

# namespace: WildRPC

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class Boolean(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAs(cls, buf, offset=0):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = Boolean()
        x.Init(buf, n + offset)
        return x

    @classmethod
    def GetRootAsBoolean(cls, buf, offset=0):
        """This method is deprecated. Please switch to GetRootAs."""
        return cls.GetRootAs(buf, offset)
    # Boolean
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # Boolean
    def Value(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            return bool(self._tab.Get(flatbuffers.number_types.BoolFlags, o + self._tab.Pos))
        return False

def Start(builder): builder.StartObject(1)
def BooleanStart(builder):
    """This method is deprecated. Please switch to Start."""
    return Start(builder)
def AddValue(builder, value): builder.PrependBoolSlot(0, value, 0)
def BooleanAddValue(builder, value):
    """This method is deprecated. Please switch to AddValue."""
    return AddValue(builder, value)
def End(builder): return builder.EndObject()
def BooleanEnd(builder):
    """This method is deprecated. Please switch to End."""
    return End(builder)

class BooleanT(object):

    # BooleanT
    def __init__(self):
        self.value = False  # type: bool

    @classmethod
    def InitFromBuf(cls, buf, pos):
        boolean = Boolean()
        boolean.Init(buf, pos)
        return cls.InitFromObj(boolean)

    @classmethod
    def InitFromObj(cls, boolean):
        x = BooleanT()
        x._UnPack(boolean)
        return x

    # BooleanT
    def _UnPack(self, boolean):
        if boolean is None:
            return
        self.value = boolean.Value()

    # BooleanT
    def Pack(self, builder):
        Start(builder)
        AddValue(builder, self.value)
        boolean = End(builder)
        return boolean
