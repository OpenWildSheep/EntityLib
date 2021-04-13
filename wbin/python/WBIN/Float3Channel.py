# automatically generated by the FlatBuffers compiler, do not modify

# namespace: WBIN

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class Float3Channel(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAs(cls, buf, offset=0):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = Float3Channel()
        x.Init(buf, n + offset)
        return x

    @classmethod
    def GetRootAsFloat3Channel(cls, buf, offset=0):
        """This method is deprecated. Please switch to GetRootAs."""
        return cls.GetRootAs(buf, offset)
    # Float3Channel
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # Float3Channel
    def Triangles(self, j):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            x = self._tab.Vector(o)
            x += flatbuffers.number_types.UOffsetTFlags.py_type(j) * 12
            from WBIN.UInt3 import UInt3
            obj = UInt3()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # Float3Channel
    def TrianglesLength(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            return self._tab.VectorLen(o)
        return 0

    # Float3Channel
    def TrianglesIsNone(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        return o == 0

    # Float3Channel
    def VertexData(self, j):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        if o != 0:
            x = self._tab.Vector(o)
            x += flatbuffers.number_types.UOffsetTFlags.py_type(j) * 12
            from WBIN.Float3 import Float3
            obj = Float3()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # Float3Channel
    def VertexDataLength(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        if o != 0:
            return self._tab.VectorLen(o)
        return 0

    # Float3Channel
    def VertexDataIsNone(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        return o == 0

def Start(builder): builder.StartObject(2)
def Float3ChannelStart(builder):
    """This method is deprecated. Please switch to Start."""
    return Start(builder)
def AddTriangles(builder, triangles): builder.PrependUOffsetTRelativeSlot(0, flatbuffers.number_types.UOffsetTFlags.py_type(triangles), 0)
def Float3ChannelAddTriangles(builder, triangles):
    """This method is deprecated. Please switch to AddTriangles."""
    return AddTriangles(builder, triangles)
def StartTrianglesVector(builder, numElems): return builder.StartVector(12, numElems, 4)
def Float3ChannelStartTrianglesVector(builder, numElems):
    """This method is deprecated. Please switch to Start."""
    return StartTrianglesVector(builder, numElems)
def AddVertexData(builder, vertexData): builder.PrependUOffsetTRelativeSlot(1, flatbuffers.number_types.UOffsetTFlags.py_type(vertexData), 0)
def Float3ChannelAddVertexData(builder, vertexData):
    """This method is deprecated. Please switch to AddVertexData."""
    return AddVertexData(builder, vertexData)
def StartVertexDataVector(builder, numElems): return builder.StartVector(12, numElems, 4)
def Float3ChannelStartVertexDataVector(builder, numElems):
    """This method is deprecated. Please switch to Start."""
    return StartVertexDataVector(builder, numElems)
def End(builder): return builder.EndObject()
def Float3ChannelEnd(builder):
    """This method is deprecated. Please switch to End."""
    return End(builder)
import WBIN.Float3
import WBIN.UInt3
try:
    from typing import List
except:
    pass

class Float3ChannelT(object):

    # Float3ChannelT
    def __init__(self):
        self.triangles = None  # type: List[WBIN.UInt3.UInt3T]
        self.vertexData = None  # type: List[WBIN.Float3.Float3T]

    @classmethod
    def InitFromBuf(cls, buf, pos):
        float3Channel = Float3Channel()
        float3Channel.Init(buf, pos)
        return cls.InitFromObj(float3Channel)

    @classmethod
    def InitFromObj(cls, float3Channel):
        x = Float3ChannelT()
        x._UnPack(float3Channel)
        return x

    # Float3ChannelT
    def _UnPack(self, float3Channel):
        if float3Channel is None:
            return
        if not float3Channel.TrianglesIsNone():
            self.triangles = []
            for i in range(float3Channel.TrianglesLength()):
                if float3Channel.Triangles(i) is None:
                    self.triangles.append(None)
                else:
                    uInt3_ = WBIN.UInt3.UInt3T.InitFromObj(float3Channel.Triangles(i))
                    self.triangles.append(uInt3_)
        if not float3Channel.VertexDataIsNone():
            self.vertexData = []
            for i in range(float3Channel.VertexDataLength()):
                if float3Channel.VertexData(i) is None:
                    self.vertexData.append(None)
                else:
                    float3_ = WBIN.Float3.Float3T.InitFromObj(float3Channel.VertexData(i))
                    self.vertexData.append(float3_)

    # Float3ChannelT
    def Pack(self, builder):
        if self.triangles is not None:
            StartTrianglesVector(builder, len(self.triangles))
            for i in reversed(range(len(self.triangles))):
                self.triangles[i].Pack(builder)
            triangles = builder.EndVector()
        if self.vertexData is not None:
            StartVertexDataVector(builder, len(self.vertexData))
            for i in reversed(range(len(self.vertexData))):
                self.vertexData[i].Pack(builder)
            vertexData = builder.EndVector()
        Start(builder)
        if self.triangles is not None:
            AddTriangles(builder, triangles)
        if self.vertexData is not None:
            AddVertexData(builder, vertexData)
        float3Channel = End(builder)
        return float3Channel
