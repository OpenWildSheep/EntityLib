# automatically generated by the FlatBuffers compiler, do not modify

# namespace: WBIN

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class BoneMatrix(object):
    __slots__ = ['_tab']

    @classmethod
    def SizeOf(cls):
        return 64

    # BoneMatrix
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # BoneMatrix
    def Matrix4(self): return [self._tab.Get(flatbuffers.number_types.Float32Flags, self._tab.Pos + flatbuffers.number_types.UOffsetTFlags.py_type(0 + i * 4)) for i in range(16)]
    # BoneMatrix
    def Matrix4Length(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(0))
        if o != 0:
            return self._tab.VectorLen(o)
        return 0

    # BoneMatrix
    def Matrix4IsNone(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(0))
        return o == 0


def CreateBoneMatrix(builder, matrix4):
    builder.Prep(4, 64)
    for _idx0 in range(16 , 0, -1):
        builder.PrependFloat32(matrix4[_idx0-1])
    return builder.Offset()

try:
    from typing import List
except:
    pass

class BoneMatrixT(object):

    # BoneMatrixT
    def __init__(self):
        self.matrix4 = None  # type: List[float]

    @classmethod
    def InitFromBuf(cls, buf, pos):
        boneMatrix = BoneMatrix()
        boneMatrix.Init(buf, pos)
        return cls.InitFromObj(boneMatrix)

    @classmethod
    def InitFromObj(cls, boneMatrix):
        x = BoneMatrixT()
        x._UnPack(boneMatrix)
        return x

    # BoneMatrixT
    def _UnPack(self, boneMatrix):
        if boneMatrix is None:
            return
        if not boneMatrix.Matrix4IsNone():
            if np is None:
                self.matrix4 = []
                for i in range(boneMatrix.Matrix4Length()):
                    self.matrix4.append(boneMatrix.Matrix4(i))
            else:
                self.matrix4 = boneMatrix.Matrix4AsNumpy()

    # BoneMatrixT
    def Pack(self, builder):
        return CreateBoneMatrix(builder, self.matrix4)
