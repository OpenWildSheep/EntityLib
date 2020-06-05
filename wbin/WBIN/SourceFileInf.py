# automatically generated by the FlatBuffers compiler, do not modify

# namespace: WBIN

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class SourceFileInf(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAsSourceFileInf(cls, buf, offset):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = SourceFileInf()
        x.Init(buf, n + offset)
        return x

    # SourceFileInf
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # SourceFileInf
    def SourceFilePath(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            return self._tab.String(o + self._tab.Pos)
        return None

def SourceFileInfStart(builder): builder.StartObject(1)
def SourceFileInfAddSourceFilePath(builder, sourceFilePath): builder.PrependUOffsetTRelativeSlot(0, flatbuffers.number_types.UOffsetTFlags.py_type(sourceFilePath), 0)
def SourceFileInfEnd(builder): return builder.EndObject()


class SourceFileInfT(object):

    # SourceFileInfT
    def __init__(self):
        self.sourceFilePath = None  # type: str

    @classmethod
    def InitFromBuf(cls, buf, pos):
        sourceFileInf = SourceFileInf()
        sourceFileInf.Init(buf, pos)
        return cls.InitFromObj(sourceFileInf)

    @classmethod
    def InitFromObj(cls, sourceFileInf):
        x = SourceFileInfT()
        x._UnPack(sourceFileInf)
        return x

    # SourceFileInfT
    def _UnPack(self, sourceFileInf):
        if sourceFileInf is None:
            return
        self.sourceFilePath = sourceFileInf.SourceFilePath()

    # SourceFileInfT
    def Pack(self, builder):
        if self.sourceFilePath is not None:
            sourceFilePath = builder.CreateString(self.sourceFilePath)
        SourceFileInfStart(builder)
        if self.sourceFilePath is not None:
            SourceFileInfAddSourceFilePath(builder, sourceFilePath)
        sourceFileInf = SourceFileInfEnd(builder)
        return sourceFileInf
