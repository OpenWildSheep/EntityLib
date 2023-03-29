# automatically generated by the FlatBuffers compiler, do not modify

# namespace: WBIN

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class BiomePatch(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAs(cls, buf, offset=0):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = BiomePatch()
        x.Init(buf, n + offset)
        return x

    @classmethod
    def GetRootAsBiomePatch(cls, buf, offset=0):
        """This method is deprecated. Please switch to GetRootAs."""
        return cls.GetRootAs(buf, offset)
    # BiomePatch
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # BiomePatch
    def Aabb(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            x = o + self._tab.Pos
            from WBIN.AABB import AABB
            obj = AABB()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # BiomePatch
    def Position(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        if o != 0:
            x = self._tab.Indirect(o + self._tab.Pos)
            from WBIN.Float3Channel import Float3Channel
            obj = Float3Channel()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # BiomePatch
    def SourceFileInf(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(8))
        if o != 0:
            x = self._tab.Indirect(o + self._tab.Pos)
            from WBIN.SourceFileInf import SourceFileInf
            obj = SourceFileInf()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # BiomePatch
    def EdgeVisibility(self, j):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(10))
        if o != 0:
            x = self._tab.Vector(o)
            x += flatbuffers.number_types.UOffsetTFlags.py_type(j) * 3
            from WBIN.Bool3 import Bool3
            obj = Bool3()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # BiomePatch
    def EdgeVisibilityLength(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(10))
        if o != 0:
            return self._tab.VectorLen(o)
        return 0

    # BiomePatch
    def EdgeVisibilityIsNone(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(10))
        return o == 0

def Start(builder): builder.StartObject(4)
def BiomePatchStart(builder):
    """This method is deprecated. Please switch to Start."""
    return Start(builder)
def AddAabb(builder, aabb): builder.PrependStructSlot(0, flatbuffers.number_types.UOffsetTFlags.py_type(aabb), 0)
def BiomePatchAddAabb(builder, aabb):
    """This method is deprecated. Please switch to AddAabb."""
    return AddAabb(builder, aabb)
def AddPosition(builder, position): builder.PrependUOffsetTRelativeSlot(1, flatbuffers.number_types.UOffsetTFlags.py_type(position), 0)
def BiomePatchAddPosition(builder, position):
    """This method is deprecated. Please switch to AddPosition."""
    return AddPosition(builder, position)
def AddSourceFileInf(builder, sourceFileInf): builder.PrependUOffsetTRelativeSlot(2, flatbuffers.number_types.UOffsetTFlags.py_type(sourceFileInf), 0)
def BiomePatchAddSourceFileInf(builder, sourceFileInf):
    """This method is deprecated. Please switch to AddSourceFileInf."""
    return AddSourceFileInf(builder, sourceFileInf)
def AddEdgeVisibility(builder, edgeVisibility): builder.PrependUOffsetTRelativeSlot(3, flatbuffers.number_types.UOffsetTFlags.py_type(edgeVisibility), 0)
def BiomePatchAddEdgeVisibility(builder, edgeVisibility):
    """This method is deprecated. Please switch to AddEdgeVisibility."""
    return AddEdgeVisibility(builder, edgeVisibility)
def StartEdgeVisibilityVector(builder, numElems): return builder.StartVector(3, numElems, 1)
def BiomePatchStartEdgeVisibilityVector(builder, numElems):
    """This method is deprecated. Please switch to Start."""
    return StartEdgeVisibilityVector(builder, numElems)
def End(builder): return builder.EndObject()
def BiomePatchEnd(builder):
    """This method is deprecated. Please switch to End."""
    return End(builder)
import WBIN.AABB
import WBIN.Bool3
import WBIN.Float3Channel
import WBIN.SourceFileInf
try:
    from typing import List, Optional
except:
    pass

class BiomePatchT(object):

    # BiomePatchT
    def __init__(self):
        self.aabb = None  # type: Optional[WBIN.AABB.AABBT]
        self.position = None  # type: Optional[WBIN.Float3Channel.Float3ChannelT]
        self.sourceFileInf = None  # type: Optional[WBIN.SourceFileInf.SourceFileInfT]
        self.edgeVisibility = None  # type: List[WBIN.Bool3.Bool3T]

    @classmethod
    def InitFromBuf(cls, buf, pos):
        biomePatch = BiomePatch()
        biomePatch.Init(buf, pos)
        return cls.InitFromObj(biomePatch)

    @classmethod
    def InitFromObj(cls, biomePatch):
        x = BiomePatchT()
        x._UnPack(biomePatch)
        return x

    # BiomePatchT
    def _UnPack(self, biomePatch):
        if biomePatch is None:
            return
        if biomePatch.Aabb() is not None:
            self.aabb = WBIN.AABB.AABBT.InitFromObj(biomePatch.Aabb())
        if biomePatch.Position() is not None:
            self.position = WBIN.Float3Channel.Float3ChannelT.InitFromObj(biomePatch.Position())
        if biomePatch.SourceFileInf() is not None:
            self.sourceFileInf = WBIN.SourceFileInf.SourceFileInfT.InitFromObj(biomePatch.SourceFileInf())
        if not biomePatch.EdgeVisibilityIsNone():
            self.edgeVisibility = []
            for i in range(biomePatch.EdgeVisibilityLength()):
                if biomePatch.EdgeVisibility(i) is None:
                    self.edgeVisibility.append(None)
                else:
                    bool3_ = WBIN.Bool3.Bool3T.InitFromObj(biomePatch.EdgeVisibility(i))
                    self.edgeVisibility.append(bool3_)

    # BiomePatchT
    def Pack(self, builder):
        if self.position is not None:
            position = self.position.Pack(builder)
        if self.sourceFileInf is not None:
            sourceFileInf = self.sourceFileInf.Pack(builder)
        if self.edgeVisibility is not None:
            StartEdgeVisibilityVector(builder, len(self.edgeVisibility))
            for i in reversed(range(len(self.edgeVisibility))):
                self.edgeVisibility[i].Pack(builder)
            edgeVisibility = builder.EndVector()
        Start(builder)
        if self.aabb is not None:
            aabb = self.aabb.Pack(builder)
            AddAabb(builder, aabb)
        if self.position is not None:
            AddPosition(builder, position)
        if self.sourceFileInf is not None:
            AddSourceFileInf(builder, sourceFileInf)
        if self.edgeVisibility is not None:
            AddEdgeVisibility(builder, edgeVisibility)
        biomePatch = End(builder)
        return biomePatch
