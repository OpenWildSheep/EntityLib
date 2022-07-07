# automatically generated by the FlatBuffers compiler, do not modify

# namespace: WBIN

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class Skl(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAs(cls, buf, offset=0):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = Skl()
        x.Init(buf, n + offset)
        return x

    @classmethod
    def GetRootAsSkl(cls, buf, offset=0):
        """This method is deprecated. Please switch to GetRootAs."""
        return cls.GetRootAs(buf, offset)
    # Skl
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # Skl
    def Skeleton(self, j):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            x = self._tab.Vector(o)
            x += flatbuffers.number_types.UOffsetTFlags.py_type(j) * 4
            x = self._tab.Indirect(x)
            from WBIN.BoneData import BoneData
            obj = BoneData()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # Skl
    def SkeletonLength(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            return self._tab.VectorLen(o)
        return 0

    # Skl
    def SkeletonIsNone(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        return o == 0

    # Skl
    def SourceFileInf(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        if o != 0:
            x = self._tab.Indirect(o + self._tab.Pos)
            from WBIN.SourceFileInf import SourceFileInf
            obj = SourceFileInf()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # Skl
    def BlendShapes(self, j):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(8))
        if o != 0:
            x = self._tab.Vector(o)
            x += flatbuffers.number_types.UOffsetTFlags.py_type(j) * 4
            x = self._tab.Indirect(x)
            from WBIN.BlendShapeData import BlendShapeData
            obj = BlendShapeData()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # Skl
    def BlendShapesLength(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(8))
        if o != 0:
            return self._tab.VectorLen(o)
        return 0

    # Skl
    def BlendShapesIsNone(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(8))
        return o == 0

    # Skl
    def BindPose(self, j):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(10))
        if o != 0:
            x = self._tab.Vector(o)
            x += flatbuffers.number_types.UOffsetTFlags.py_type(j) * 64
            from WBIN.BoneMatrix import BoneMatrix
            obj = BoneMatrix()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # Skl
    def BindPoseLength(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(10))
        if o != 0:
            return self._tab.VectorLen(o)
        return 0

    # Skl
    def BindPoseIsNone(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(10))
        return o == 0

def Start(builder): builder.StartObject(4)
def SklStart(builder):
    """This method is deprecated. Please switch to Start."""
    return Start(builder)
def AddSkeleton(builder, skeleton): builder.PrependUOffsetTRelativeSlot(0, flatbuffers.number_types.UOffsetTFlags.py_type(skeleton), 0)
def SklAddSkeleton(builder, skeleton):
    """This method is deprecated. Please switch to AddSkeleton."""
    return AddSkeleton(builder, skeleton)
def StartSkeletonVector(builder, numElems): return builder.StartVector(4, numElems, 4)
def SklStartSkeletonVector(builder, numElems):
    """This method is deprecated. Please switch to Start."""
    return StartSkeletonVector(builder, numElems)
def AddSourceFileInf(builder, sourceFileInf): builder.PrependUOffsetTRelativeSlot(1, flatbuffers.number_types.UOffsetTFlags.py_type(sourceFileInf), 0)
def SklAddSourceFileInf(builder, sourceFileInf):
    """This method is deprecated. Please switch to AddSourceFileInf."""
    return AddSourceFileInf(builder, sourceFileInf)
def AddBlendShapes(builder, blendShapes): builder.PrependUOffsetTRelativeSlot(2, flatbuffers.number_types.UOffsetTFlags.py_type(blendShapes), 0)
def SklAddBlendShapes(builder, blendShapes):
    """This method is deprecated. Please switch to AddBlendShapes."""
    return AddBlendShapes(builder, blendShapes)
def StartBlendShapesVector(builder, numElems): return builder.StartVector(4, numElems, 4)
def SklStartBlendShapesVector(builder, numElems):
    """This method is deprecated. Please switch to Start."""
    return StartBlendShapesVector(builder, numElems)
def AddBindPose(builder, bindPose): builder.PrependUOffsetTRelativeSlot(3, flatbuffers.number_types.UOffsetTFlags.py_type(bindPose), 0)
def SklAddBindPose(builder, bindPose):
    """This method is deprecated. Please switch to AddBindPose."""
    return AddBindPose(builder, bindPose)
def StartBindPoseVector(builder, numElems): return builder.StartVector(64, numElems, 4)
def SklStartBindPoseVector(builder, numElems):
    """This method is deprecated. Please switch to Start."""
    return StartBindPoseVector(builder, numElems)
def End(builder): return builder.EndObject()
def SklEnd(builder):
    """This method is deprecated. Please switch to End."""
    return End(builder)
import WBIN.BlendShapeData
import WBIN.BoneData
import WBIN.BoneMatrix
import WBIN.SourceFileInf
try:
    from typing import List, Optional
except:
    pass

class SklT(object):

    # SklT
    def __init__(self):
        self.skeleton = None  # type: List[WBIN.BoneData.BoneDataT]
        self.sourceFileInf = None  # type: Optional[WBIN.SourceFileInf.SourceFileInfT]
        self.blendShapes = None  # type: List[WBIN.BlendShapeData.BlendShapeDataT]
        self.bindPose = None  # type: List[WBIN.BoneMatrix.BoneMatrixT]

    @classmethod
    def InitFromBuf(cls, buf, pos):
        skl = Skl()
        skl.Init(buf, pos)
        return cls.InitFromObj(skl)

    @classmethod
    def InitFromObj(cls, skl):
        x = SklT()
        x._UnPack(skl)
        return x

    # SklT
    def _UnPack(self, skl):
        if skl is None:
            return
        if not skl.SkeletonIsNone():
            self.skeleton = []
            for i in range(skl.SkeletonLength()):
                if skl.Skeleton(i) is None:
                    self.skeleton.append(None)
                else:
                    boneData_ = WBIN.BoneData.BoneDataT.InitFromObj(skl.Skeleton(i))
                    self.skeleton.append(boneData_)
        if skl.SourceFileInf() is not None:
            self.sourceFileInf = WBIN.SourceFileInf.SourceFileInfT.InitFromObj(skl.SourceFileInf())
        if not skl.BlendShapesIsNone():
            self.blendShapes = []
            for i in range(skl.BlendShapesLength()):
                if skl.BlendShapes(i) is None:
                    self.blendShapes.append(None)
                else:
                    blendShapeData_ = WBIN.BlendShapeData.BlendShapeDataT.InitFromObj(skl.BlendShapes(i))
                    self.blendShapes.append(blendShapeData_)
        if not skl.BindPoseIsNone():
            self.bindPose = []
            for i in range(skl.BindPoseLength()):
                if skl.BindPose(i) is None:
                    self.bindPose.append(None)
                else:
                    boneMatrix_ = WBIN.BoneMatrix.BoneMatrixT.InitFromObj(skl.BindPose(i))
                    self.bindPose.append(boneMatrix_)

    # SklT
    def Pack(self, builder):
        if self.skeleton is not None:
            skeletonlist = []
            for i in range(len(self.skeleton)):
                skeletonlist.append(self.skeleton[i].Pack(builder))
            StartSkeletonVector(builder, len(self.skeleton))
            for i in reversed(range(len(self.skeleton))):
                builder.PrependUOffsetTRelative(skeletonlist[i])
            skeleton = builder.EndVector()
        if self.sourceFileInf is not None:
            sourceFileInf = self.sourceFileInf.Pack(builder)
        if self.blendShapes is not None:
            blendShapeslist = []
            for i in range(len(self.blendShapes)):
                blendShapeslist.append(self.blendShapes[i].Pack(builder))
            StartBlendShapesVector(builder, len(self.blendShapes))
            for i in reversed(range(len(self.blendShapes))):
                builder.PrependUOffsetTRelative(blendShapeslist[i])
            blendShapes = builder.EndVector()
        if self.bindPose is not None:
            StartBindPoseVector(builder, len(self.bindPose))
            for i in reversed(range(len(self.bindPose))):
                self.bindPose[i].Pack(builder)
            bindPose = builder.EndVector()
        Start(builder)
        if self.skeleton is not None:
            AddSkeleton(builder, skeleton)
        if self.sourceFileInf is not None:
            AddSourceFileInf(builder, sourceFileInf)
        if self.blendShapes is not None:
            AddBlendShapes(builder, blendShapes)
        if self.bindPose is not None:
            AddBindPose(builder, bindPose)
        skl = End(builder)
        return skl
