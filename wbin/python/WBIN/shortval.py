# automatically generated by the FlatBuffers compiler, do not modify

# namespace: WBIN

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class shortval(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAs(cls, buf, offset=0):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = shortval()
        x.Init(buf, n + offset)
        return x

    @classmethod
    def GetRootAsshortval(cls, buf, offset=0):
        """This method is deprecated. Please switch to GetRootAs."""
        return cls.GetRootAs(buf, offset)
    # shortval
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # shortval
    def Values(self, j):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            a = self._tab.Vector(o)
            return self._tab.Get(flatbuffers.number_types.Int16Flags, a + flatbuffers.number_types.UOffsetTFlags.py_type(j * 2))
        return 0

    # shortval
    def ValuesAsNumpy(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            return self._tab.GetVectorAsNumpy(flatbuffers.number_types.Int16Flags, o)
        return 0

    # shortval
    def ValuesLength(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            return self._tab.VectorLen(o)
        return 0

    # shortval
    def ValuesIsNone(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        return o == 0

def Start(builder): builder.StartObject(1)
def shortvalStart(builder):
    """This method is deprecated. Please switch to Start."""
    return Start(builder)
def AddValues(builder, values): builder.PrependUOffsetTRelativeSlot(0, flatbuffers.number_types.UOffsetTFlags.py_type(values), 0)
def shortvalAddValues(builder, values):
    """This method is deprecated. Please switch to AddValues."""
    return AddValues(builder, values)
def StartValuesVector(builder, numElems): return builder.StartVector(2, numElems, 2)
def shortvalStartValuesVector(builder, numElems):
    """This method is deprecated. Please switch to Start."""
    return StartValuesVector(builder, numElems)
def End(builder): return builder.EndObject()
def shortvalEnd(builder):
    """This method is deprecated. Please switch to End."""
    return End(builder)
try:
    from typing import List
except:
    pass

class shortvalT(object):

    # shortvalT
    def __init__(self):
        self.values = None  # type: List[int]

    @classmethod
    def InitFromBuf(cls, buf, pos):
        shortval = shortval()
        shortval.Init(buf, pos)
        return cls.InitFromObj(shortval)

    @classmethod
    def InitFromObj(cls, shortval):
        x = shortvalT()
        x._UnPack(shortval)
        return x

    # shortvalT
    def _UnPack(self, shortval):
        if shortval is None:
            return
        if not shortval.ValuesIsNone():
            if np is None:
                self.values = []
                for i in range(shortval.ValuesLength()):
                    self.values.append(shortval.Values(i))
            else:
                self.values = shortval.ValuesAsNumpy()

    # shortvalT
    def Pack(self, builder):
        if self.values is not None:
            if np is not None and type(self.values) is np.ndarray:
                values = builder.CreateNumpyVector(self.values)
            else:
                StartValuesVector(builder, len(self.values))
                for i in reversed(range(len(self.values))):
                    builder.PrependInt16(self.values[i])
                values = builder.EndVector()
        Start(builder)
        if self.values is not None:
            AddValues(builder, values)
        shortval = End(builder)
        return shortval