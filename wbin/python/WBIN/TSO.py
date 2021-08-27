# automatically generated by the FlatBuffers compiler, do not modify

# namespace: WBIN

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class TSO(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAs(cls, buf, offset=0):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = TSO()
        x.Init(buf, n + offset)
        return x

    @classmethod
    def GetRootAsTSO(cls, buf, offset=0):
        """This method is deprecated. Please switch to GetRootAs."""
        return cls.GetRootAs(buf, offset)
    # TSO
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # TSO
    def Position(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            x = self._tab.Indirect(o + self._tab.Pos)
            from WBIN.Float3Channel import Float3Channel
            obj = Float3Channel()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

def Start(builder): builder.StartObject(1)
def TSOStart(builder):
    """This method is deprecated. Please switch to Start."""
    return Start(builder)
def AddPosition(builder, position): builder.PrependUOffsetTRelativeSlot(0, flatbuffers.number_types.UOffsetTFlags.py_type(position), 0)
def TSOAddPosition(builder, position):
    """This method is deprecated. Please switch to AddPosition."""
    return AddPosition(builder, position)
def End(builder): return builder.EndObject()
def TSOEnd(builder):
    """This method is deprecated. Please switch to End."""
    return End(builder)
import WBIN.Float3Channel
try:
    from typing import Optional
except:
    pass

class TSOT(object):

    # TSOT
    def __init__(self):
        self.position = None  # type: Optional[WBIN.Float3Channel.Float3ChannelT]

    @classmethod
    def InitFromBuf(cls, buf, pos):
        tSO = TSO()
        tSO.Init(buf, pos)
        return cls.InitFromObj(tSO)

    @classmethod
    def InitFromObj(cls, tSO):
        x = TSOT()
        x._UnPack(tSO)
        return x

    # TSOT
    def _UnPack(self, tSO):
        if tSO is None:
            return
        if tSO.Position() is not None:
            self.position = WBIN.Float3Channel.Float3ChannelT.InitFromObj(tSO.Position())

    # TSOT
    def Pack(self, builder):
        if self.position is not None:
            position = self.position.Pack(builder)
        Start(builder)
        if self.position is not None:
            AddPosition(builder, position)
        tSO = End(builder)
        return tSO