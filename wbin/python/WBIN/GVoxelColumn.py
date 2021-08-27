# automatically generated by the FlatBuffers compiler, do not modify

# namespace: WBIN

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class GVoxelColumn(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAs(cls, buf, offset=0):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = GVoxelColumn()
        x.Init(buf, n + offset)
        return x

    @classmethod
    def GetRootAsGVoxelColumn(cls, buf, offset=0):
        """This method is deprecated. Please switch to GetRootAs."""
        return cls.GetRootAs(buf, offset)
    # GVoxelColumn
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # GVoxelColumn
    def Piles(self, j):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            x = self._tab.Vector(o)
            x += flatbuffers.number_types.UOffsetTFlags.py_type(j) * 4
            x = self._tab.Indirect(x)
            from WBIN.GVoxelPile import GVoxelPile
            obj = GVoxelPile()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # GVoxelColumn
    def PilesLength(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            return self._tab.VectorLen(o)
        return 0

    # GVoxelColumn
    def PilesIsNone(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        return o == 0

def Start(builder): builder.StartObject(1)
def GVoxelColumnStart(builder):
    """This method is deprecated. Please switch to Start."""
    return Start(builder)
def AddPiles(builder, piles): builder.PrependUOffsetTRelativeSlot(0, flatbuffers.number_types.UOffsetTFlags.py_type(piles), 0)
def GVoxelColumnAddPiles(builder, piles):
    """This method is deprecated. Please switch to AddPiles."""
    return AddPiles(builder, piles)
def StartPilesVector(builder, numElems): return builder.StartVector(4, numElems, 4)
def GVoxelColumnStartPilesVector(builder, numElems):
    """This method is deprecated. Please switch to Start."""
    return StartPilesVector(builder, numElems)
def End(builder): return builder.EndObject()
def GVoxelColumnEnd(builder):
    """This method is deprecated. Please switch to End."""
    return End(builder)
import WBIN.GVoxelPile
try:
    from typing import List
except:
    pass

class GVoxelColumnT(object):

    # GVoxelColumnT
    def __init__(self):
        self.piles = None  # type: List[WBIN.GVoxelPile.GVoxelPileT]

    @classmethod
    def InitFromBuf(cls, buf, pos):
        gVoxelColumn = GVoxelColumn()
        gVoxelColumn.Init(buf, pos)
        return cls.InitFromObj(gVoxelColumn)

    @classmethod
    def InitFromObj(cls, gVoxelColumn):
        x = GVoxelColumnT()
        x._UnPack(gVoxelColumn)
        return x

    # GVoxelColumnT
    def _UnPack(self, gVoxelColumn):
        if gVoxelColumn is None:
            return
        if not gVoxelColumn.PilesIsNone():
            self.piles = []
            for i in range(gVoxelColumn.PilesLength()):
                if gVoxelColumn.Piles(i) is None:
                    self.piles.append(None)
                else:
                    gVoxelPile_ = WBIN.GVoxelPile.GVoxelPileT.InitFromObj(gVoxelColumn.Piles(i))
                    self.piles.append(gVoxelPile_)

    # GVoxelColumnT
    def Pack(self, builder):
        if self.piles is not None:
            pileslist = []
            for i in range(len(self.piles)):
                pileslist.append(self.piles[i].Pack(builder))
            StartPilesVector(builder, len(self.piles))
            for i in reversed(range(len(self.piles))):
                builder.PrependUOffsetTRelative(pileslist[i])
            piles = builder.EndVector()
        Start(builder)
        if self.piles is not None:
            AddPiles(builder, piles)
        gVoxelColumn = End(builder)
        return gVoxelColumn