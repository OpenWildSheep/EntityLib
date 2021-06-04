# automatically generated by the FlatBuffers compiler, do not modify

# namespace: WildRPC

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class Integer(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAs(cls, buf, offset=0):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = Integer()
        x.Init(buf, n + offset)
        return x

    @classmethod
    def GetRootAsInteger(cls, buf, offset=0):
        """This method is deprecated. Please switch to GetRootAs."""
        return cls.GetRootAs(buf, offset)
    # Integer
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # Integer
    def Value(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            return self._tab.Get(flatbuffers.number_types.Int32Flags, o + self._tab.Pos)
        return 0

def Start(builder): builder.StartObject(1)
def IntegerStart(builder):
    """This method is deprecated. Please switch to Start."""
    return Start(builder)
def AddValue(builder, value): builder.PrependInt32Slot(0, value, 0)
def IntegerAddValue(builder, value):
    """This method is deprecated. Please switch to AddValue."""
    return AddValue(builder, value)
def End(builder): return builder.EndObject()
def IntegerEnd(builder):
    """This method is deprecated. Please switch to End."""
    return End(builder)

class IntegerT(object):

    # IntegerT
    def __init__(self):
        self.value = 0  # type: int

    @classmethod
    def InitFromBuf(cls, buf, pos):
        integer = Integer()
        integer.Init(buf, pos)
        return cls.InitFromObj(integer)

    @classmethod
    def InitFromObj(cls, integer):
        x = IntegerT()
        x._UnPack(integer)
        return x

    # IntegerT
    def _UnPack(self, integer):
        if integer is None:
            return
        self.value = integer.Value()

    # IntegerT
    def Pack(self, builder):
        Start(builder)
        AddValue(builder, self.value)
        integer = End(builder)
        return integer
