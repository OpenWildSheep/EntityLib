# automatically generated by the FlatBuffers compiler, do not modify

# namespace: WBIN

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class FloatMask(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAsFloatMask(cls, buf, offset):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = FloatMask()
        x.Init(buf, n + offset)
        return x

    # FloatMask
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # FloatMask
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

    # FloatMask
    def TrianglesLength(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            return self._tab.VectorLen(o)
        return 0

    # FloatMask
    def TrianglesIsNone(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        return o == 0

    # FloatMask
    def VertexData(self, j):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        if o != 0:
            a = self._tab.Vector(o)
            return self._tab.Get(flatbuffers.number_types.Float32Flags, a + flatbuffers.number_types.UOffsetTFlags.py_type(j * 4))
        return 0

    # FloatMask
    def VertexDataAsNumpy(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        if o != 0:
            return self._tab.GetVectorAsNumpy(flatbuffers.number_types.Float32Flags, o)
        return 0

    # FloatMask
    def VertexDataLength(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        if o != 0:
            return self._tab.VectorLen(o)
        return 0

    # FloatMask
    def VertexDataIsNone(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        return o == 0

def FloatMaskStart(builder): builder.StartObject(2)
def FloatMaskAddTriangles(builder, triangles): builder.PrependUOffsetTRelativeSlot(0, flatbuffers.number_types.UOffsetTFlags.py_type(triangles), 0)
def FloatMaskStartTrianglesVector(builder, numElems): return builder.StartVector(12, numElems, 4)
def FloatMaskAddVertexData(builder, vertexData): builder.PrependUOffsetTRelativeSlot(1, flatbuffers.number_types.UOffsetTFlags.py_type(vertexData), 0)
def FloatMaskStartVertexDataVector(builder, numElems): return builder.StartVector(4, numElems, 4)
def FloatMaskEnd(builder): return builder.EndObject()

import WBIN.UInt3
try:
    from typing import List
except:
    pass

class FloatMaskT(object):

    # FloatMaskT
    def __init__(self):
        self.triangles = None  # type: List[WBIN.UInt3.UInt3T]
        self.vertexData = None  # type: List[float]

    @classmethod
    def InitFromBuf(cls, buf, pos):
        floatMask = FloatMask()
        floatMask.Init(buf, pos)
        return cls.InitFromObj(floatMask)

    @classmethod
    def InitFromObj(cls, floatMask):
        x = FloatMaskT()
        x._UnPack(floatMask)
        return x

    # FloatMaskT
    def _UnPack(self, floatMask):
        if floatMask is None:
            return
        if not floatMask.TrianglesIsNone():
            self.triangles = []
            for i in range(floatMask.TrianglesLength()):
                if floatMask.Triangles(i) is None:
                    self.triangles.append(None)
                else:
                    uInt3_ = WBIN.UInt3.UInt3T.InitFromObj(floatMask.Triangles(i))
                    self.triangles.append(uInt3_)
        if not floatMask.VertexDataIsNone():
            if np is None:
                self.vertexData = []
                for i in range(floatMask.VertexDataLength()):
                    self.vertexData.append(floatMask.VertexData(i))
            else:
                self.vertexData = floatMask.VertexDataAsNumpy()

    # FloatMaskT
    def Pack(self, builder):
        if self.triangles is not None:
            FloatMaskStartTrianglesVector(builder, len(self.triangles))
            for i in reversed(range(len(self.triangles))):
                self.triangles[i].Pack(builder)
            triangles = builder.EndVector(len(self.triangles))
        if self.vertexData is not None:
            if np is not None and type(self.vertexData) is np.ndarray:
                vertexData = builder.CreateNumpyVector(self.vertexData)
            else:
                FloatMaskStartVertexDataVector(builder, len(self.vertexData))
                for i in reversed(range(len(self.vertexData))):
                    builder.PrependFloat32(self.vertexData[i])
                vertexData = builder.EndVector(len(self.vertexData))
        FloatMaskStart(builder)
        if self.triangles is not None:
            FloatMaskAddTriangles(builder, triangles)
        if self.vertexData is not None:
            FloatMaskAddVertexData(builder, vertexData)
        floatMask = FloatMaskEnd(builder)
        return floatMask