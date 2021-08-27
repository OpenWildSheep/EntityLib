# automatically generated by the FlatBuffers compiler, do not modify

# namespace: WBIN

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class HeightObj(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAs(cls, buf, offset=0):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = HeightObj()
        x.Init(buf, n + offset)
        return x

    @classmethod
    def GetRootAsHeightObj(cls, buf, offset=0):
        """This method is deprecated. Please switch to GetRootAs."""
        return cls.GetRootAs(buf, offset)
    # HeightObj
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # HeightObj
    def Aabb(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            x = o + self._tab.Pos
            from WBIN.AABB import AABB
            obj = AABB()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # HeightObj
    def Position(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        if o != 0:
            x = self._tab.Indirect(o + self._tab.Pos)
            from WBIN.Float3Channel import Float3Channel
            obj = Float3Channel()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # HeightObj
    def EdgeVisibility(self, j):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(8))
        if o != 0:
            x = self._tab.Vector(o)
            x += flatbuffers.number_types.UOffsetTFlags.py_type(j) * 3
            from WBIN.Bool3 import Bool3
            obj = Bool3()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # HeightObj
    def EdgeVisibilityLength(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(8))
        if o != 0:
            return self._tab.VectorLen(o)
        return 0

    # HeightObj
    def EdgeVisibilityIsNone(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(8))
        return o == 0

    # HeightObj
    def Materials(self, j):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(10))
        if o != 0:
            a = self._tab.Vector(o)
            return self._tab.Get(flatbuffers.number_types.Uint32Flags, a + flatbuffers.number_types.UOffsetTFlags.py_type(j * 4))
        return 0

    # HeightObj
    def MaterialsAsNumpy(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(10))
        if o != 0:
            return self._tab.GetVectorAsNumpy(flatbuffers.number_types.Uint32Flags, o)
        return 0

    # HeightObj
    def MaterialsLength(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(10))
        if o != 0:
            return self._tab.VectorLen(o)
        return 0

    # HeightObj
    def MaterialsIsNone(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(10))
        return o == 0

    # HeightObj
    def Hardness(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(12))
        if o != 0:
            x = self._tab.Indirect(o + self._tab.Pos)
            from WBIN.FloatMask import FloatMask
            obj = FloatMask()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # HeightObj
    def ErosionMask(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(14))
        if o != 0:
            x = self._tab.Indirect(o + self._tab.Pos)
            from WBIN.FloatMask import FloatMask
            obj = FloatMask()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # HeightObj
    def DetailMask(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(16))
        if o != 0:
            x = self._tab.Indirect(o + self._tab.Pos)
            from WBIN.FloatMask import FloatMask
            obj = FloatMask()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # HeightObj
    def DetailType(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(18))
        if o != 0:
            x = self._tab.Indirect(o + self._tab.Pos)
            from WBIN.FloatMask import FloatMask
            obj = FloatMask()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # HeightObj
    def MotifMask(self, j):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(20))
        if o != 0:
            x = self._tab.Vector(o)
            x += flatbuffers.number_types.UOffsetTFlags.py_type(j) * 4
            x = self._tab.Indirect(x)
            from WBIN.FloatMask import FloatMask
            obj = FloatMask()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # HeightObj
    def MotifMaskLength(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(20))
        if o != 0:
            return self._tab.VectorLen(o)
        return 0

    # HeightObj
    def MotifMaskIsNone(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(20))
        return o == 0

    # HeightObj
    def SourceFileInf(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(22))
        if o != 0:
            x = self._tab.Indirect(o + self._tab.Pos)
            from WBIN.SourceFileInf import SourceFileInf
            obj = SourceFileInf()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # HeightObj
    def Influence(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(24))
        if o != 0:
            x = self._tab.Indirect(o + self._tab.Pos)
            from WBIN.FloatMask import FloatMask
            obj = FloatMask()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

def Start(builder): builder.StartObject(11)
def HeightObjStart(builder):
    """This method is deprecated. Please switch to Start."""
    return Start(builder)
def AddAabb(builder, aabb): builder.PrependStructSlot(0, flatbuffers.number_types.UOffsetTFlags.py_type(aabb), 0)
def HeightObjAddAabb(builder, aabb):
    """This method is deprecated. Please switch to AddAabb."""
    return AddAabb(builder, aabb)
def AddPosition(builder, position): builder.PrependUOffsetTRelativeSlot(1, flatbuffers.number_types.UOffsetTFlags.py_type(position), 0)
def HeightObjAddPosition(builder, position):
    """This method is deprecated. Please switch to AddPosition."""
    return AddPosition(builder, position)
def AddEdgeVisibility(builder, edgeVisibility): builder.PrependUOffsetTRelativeSlot(2, flatbuffers.number_types.UOffsetTFlags.py_type(edgeVisibility), 0)
def HeightObjAddEdgeVisibility(builder, edgeVisibility):
    """This method is deprecated. Please switch to AddEdgeVisibility."""
    return AddEdgeVisibility(builder, edgeVisibility)
def StartEdgeVisibilityVector(builder, numElems): return builder.StartVector(3, numElems, 1)
def HeightObjStartEdgeVisibilityVector(builder, numElems):
    """This method is deprecated. Please switch to Start."""
    return StartEdgeVisibilityVector(builder, numElems)
def AddMaterials(builder, materials): builder.PrependUOffsetTRelativeSlot(3, flatbuffers.number_types.UOffsetTFlags.py_type(materials), 0)
def HeightObjAddMaterials(builder, materials):
    """This method is deprecated. Please switch to AddMaterials."""
    return AddMaterials(builder, materials)
def StartMaterialsVector(builder, numElems): return builder.StartVector(4, numElems, 4)
def HeightObjStartMaterialsVector(builder, numElems):
    """This method is deprecated. Please switch to Start."""
    return StartMaterialsVector(builder, numElems)
def AddHardness(builder, hardness): builder.PrependUOffsetTRelativeSlot(4, flatbuffers.number_types.UOffsetTFlags.py_type(hardness), 0)
def HeightObjAddHardness(builder, hardness):
    """This method is deprecated. Please switch to AddHardness."""
    return AddHardness(builder, hardness)
def AddErosionMask(builder, erosionMask): builder.PrependUOffsetTRelativeSlot(5, flatbuffers.number_types.UOffsetTFlags.py_type(erosionMask), 0)
def HeightObjAddErosionMask(builder, erosionMask):
    """This method is deprecated. Please switch to AddErosionMask."""
    return AddErosionMask(builder, erosionMask)
def AddDetailMask(builder, detailMask): builder.PrependUOffsetTRelativeSlot(6, flatbuffers.number_types.UOffsetTFlags.py_type(detailMask), 0)
def HeightObjAddDetailMask(builder, detailMask):
    """This method is deprecated. Please switch to AddDetailMask."""
    return AddDetailMask(builder, detailMask)
def AddDetailType(builder, detailType): builder.PrependUOffsetTRelativeSlot(7, flatbuffers.number_types.UOffsetTFlags.py_type(detailType), 0)
def HeightObjAddDetailType(builder, detailType):
    """This method is deprecated. Please switch to AddDetailType."""
    return AddDetailType(builder, detailType)
def AddMotifMask(builder, motifMask): builder.PrependUOffsetTRelativeSlot(8, flatbuffers.number_types.UOffsetTFlags.py_type(motifMask), 0)
def HeightObjAddMotifMask(builder, motifMask):
    """This method is deprecated. Please switch to AddMotifMask."""
    return AddMotifMask(builder, motifMask)
def StartMotifMaskVector(builder, numElems): return builder.StartVector(4, numElems, 4)
def HeightObjStartMotifMaskVector(builder, numElems):
    """This method is deprecated. Please switch to Start."""
    return StartMotifMaskVector(builder, numElems)
def AddSourceFileInf(builder, sourceFileInf): builder.PrependUOffsetTRelativeSlot(9, flatbuffers.number_types.UOffsetTFlags.py_type(sourceFileInf), 0)
def HeightObjAddSourceFileInf(builder, sourceFileInf):
    """This method is deprecated. Please switch to AddSourceFileInf."""
    return AddSourceFileInf(builder, sourceFileInf)
def AddInfluence(builder, influence): builder.PrependUOffsetTRelativeSlot(10, flatbuffers.number_types.UOffsetTFlags.py_type(influence), 0)
def HeightObjAddInfluence(builder, influence):
    """This method is deprecated. Please switch to AddInfluence."""
    return AddInfluence(builder, influence)
def End(builder): return builder.EndObject()
def HeightObjEnd(builder):
    """This method is deprecated. Please switch to End."""
    return End(builder)
import WBIN.AABB
import WBIN.Bool3
import WBIN.Float3Channel
import WBIN.FloatMask
import WBIN.SourceFileInf
try:
    from typing import List, Optional
except:
    pass

class HeightObjT(object):

    # HeightObjT
    def __init__(self):
        self.aabb = None  # type: Optional[WBIN.AABB.AABBT]
        self.position = None  # type: Optional[WBIN.Float3Channel.Float3ChannelT]
        self.edgeVisibility = None  # type: List[WBIN.Bool3.Bool3T]
        self.materials = None  # type: List[int]
        self.hardness = None  # type: Optional[WBIN.FloatMask.FloatMaskT]
        self.erosionMask = None  # type: Optional[WBIN.FloatMask.FloatMaskT]
        self.detailMask = None  # type: Optional[WBIN.FloatMask.FloatMaskT]
        self.detailType = None  # type: Optional[WBIN.FloatMask.FloatMaskT]
        self.motifMask = None  # type: List[WBIN.FloatMask.FloatMaskT]
        self.sourceFileInf = None  # type: Optional[WBIN.SourceFileInf.SourceFileInfT]
        self.influence = None  # type: Optional[WBIN.FloatMask.FloatMaskT]

    @classmethod
    def InitFromBuf(cls, buf, pos):
        heightObj = HeightObj()
        heightObj.Init(buf, pos)
        return cls.InitFromObj(heightObj)

    @classmethod
    def InitFromObj(cls, heightObj):
        x = HeightObjT()
        x._UnPack(heightObj)
        return x

    # HeightObjT
    def _UnPack(self, heightObj):
        if heightObj is None:
            return
        if heightObj.Aabb() is not None:
            self.aabb = WBIN.AABB.AABBT.InitFromObj(heightObj.Aabb())
        if heightObj.Position() is not None:
            self.position = WBIN.Float3Channel.Float3ChannelT.InitFromObj(heightObj.Position())
        if not heightObj.EdgeVisibilityIsNone():
            self.edgeVisibility = []
            for i in range(heightObj.EdgeVisibilityLength()):
                if heightObj.EdgeVisibility(i) is None:
                    self.edgeVisibility.append(None)
                else:
                    bool3_ = WBIN.Bool3.Bool3T.InitFromObj(heightObj.EdgeVisibility(i))
                    self.edgeVisibility.append(bool3_)
        if not heightObj.MaterialsIsNone():
            if np is None:
                self.materials = []
                for i in range(heightObj.MaterialsLength()):
                    self.materials.append(heightObj.Materials(i))
            else:
                self.materials = heightObj.MaterialsAsNumpy()
        if heightObj.Hardness() is not None:
            self.hardness = WBIN.FloatMask.FloatMaskT.InitFromObj(heightObj.Hardness())
        if heightObj.ErosionMask() is not None:
            self.erosionMask = WBIN.FloatMask.FloatMaskT.InitFromObj(heightObj.ErosionMask())
        if heightObj.DetailMask() is not None:
            self.detailMask = WBIN.FloatMask.FloatMaskT.InitFromObj(heightObj.DetailMask())
        if heightObj.DetailType() is not None:
            self.detailType = WBIN.FloatMask.FloatMaskT.InitFromObj(heightObj.DetailType())
        if not heightObj.MotifMaskIsNone():
            self.motifMask = []
            for i in range(heightObj.MotifMaskLength()):
                if heightObj.MotifMask(i) is None:
                    self.motifMask.append(None)
                else:
                    floatMask_ = WBIN.FloatMask.FloatMaskT.InitFromObj(heightObj.MotifMask(i))
                    self.motifMask.append(floatMask_)
        if heightObj.SourceFileInf() is not None:
            self.sourceFileInf = WBIN.SourceFileInf.SourceFileInfT.InitFromObj(heightObj.SourceFileInf())
        if heightObj.Influence() is not None:
            self.influence = WBIN.FloatMask.FloatMaskT.InitFromObj(heightObj.Influence())

    # HeightObjT
    def Pack(self, builder):
        if self.position is not None:
            position = self.position.Pack(builder)
        if self.edgeVisibility is not None:
            StartEdgeVisibilityVector(builder, len(self.edgeVisibility))
            for i in reversed(range(len(self.edgeVisibility))):
                self.edgeVisibility[i].Pack(builder)
            edgeVisibility = builder.EndVector()
        if self.materials is not None:
            if np is not None and type(self.materials) is np.ndarray:
                materials = builder.CreateNumpyVector(self.materials)
            else:
                StartMaterialsVector(builder, len(self.materials))
                for i in reversed(range(len(self.materials))):
                    builder.PrependUint32(self.materials[i])
                materials = builder.EndVector()
        if self.hardness is not None:
            hardness = self.hardness.Pack(builder)
        if self.erosionMask is not None:
            erosionMask = self.erosionMask.Pack(builder)
        if self.detailMask is not None:
            detailMask = self.detailMask.Pack(builder)
        if self.detailType is not None:
            detailType = self.detailType.Pack(builder)
        if self.motifMask is not None:
            motifMasklist = []
            for i in range(len(self.motifMask)):
                motifMasklist.append(self.motifMask[i].Pack(builder))
            StartMotifMaskVector(builder, len(self.motifMask))
            for i in reversed(range(len(self.motifMask))):
                builder.PrependUOffsetTRelative(motifMasklist[i])
            motifMask = builder.EndVector()
        if self.sourceFileInf is not None:
            sourceFileInf = self.sourceFileInf.Pack(builder)
        if self.influence is not None:
            influence = self.influence.Pack(builder)
        Start(builder)
        if self.aabb is not None:
            aabb = self.aabb.Pack(builder)
            AddAabb(builder, aabb)
        if self.position is not None:
            AddPosition(builder, position)
        if self.edgeVisibility is not None:
            AddEdgeVisibility(builder, edgeVisibility)
        if self.materials is not None:
            AddMaterials(builder, materials)
        if self.hardness is not None:
            AddHardness(builder, hardness)
        if self.erosionMask is not None:
            AddErosionMask(builder, erosionMask)
        if self.detailMask is not None:
            AddDetailMask(builder, detailMask)
        if self.detailType is not None:
            AddDetailType(builder, detailType)
        if self.motifMask is not None:
            AddMotifMask(builder, motifMask)
        if self.sourceFileInf is not None:
            AddSourceFileInf(builder, sourceFileInf)
        if self.influence is not None:
            AddInfluence(builder, influence)
        heightObj = End(builder)
        return heightObj