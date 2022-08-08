# automatically generated by the FlatBuffers compiler, do not modify

# namespace: WBIN

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class RuntimePointCloud(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAs(cls, buf, offset=0):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = RuntimePointCloud()
        x.Init(buf, n + offset)
        return x

    @classmethod
    def GetRootAsRuntimePointCloud(cls, buf, offset=0):
        """This method is deprecated. Please switch to GetRootAs."""
        return cls.GetRootAs(buf, offset)
    # RuntimePointCloud
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # RuntimePointCloud
    def ChunkSize(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            return self._tab.Get(flatbuffers.number_types.Float32Flags, o + self._tab.Pos)
        return 0.0

    # RuntimePointCloud
    def Names(self, j):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        if o != 0:
            a = self._tab.Vector(o)
            return self._tab.String(a + flatbuffers.number_types.UOffsetTFlags.py_type(j * 4))
        return ""

    # RuntimePointCloud
    def NamesLength(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        if o != 0:
            return self._tab.VectorLen(o)
        return 0

    # RuntimePointCloud
    def NamesIsNone(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        return o == 0

    # RuntimePointCloud
    def Chunks(self, j):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(8))
        if o != 0:
            x = self._tab.Vector(o)
            x += flatbuffers.number_types.UOffsetTFlags.py_type(j) * 4
            x = self._tab.Indirect(x)
            from WBIN.CloudPointsChunk import CloudPointsChunk
            obj = CloudPointsChunk()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # RuntimePointCloud
    def ChunksLength(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(8))
        if o != 0:
            return self._tab.VectorLen(o)
        return 0

    # RuntimePointCloud
    def ChunksIsNone(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(8))
        return o == 0

def Start(builder): builder.StartObject(3)
def RuntimePointCloudStart(builder):
    """This method is deprecated. Please switch to Start."""
    return Start(builder)
def AddChunkSize(builder, chunkSize): builder.PrependFloat32Slot(0, chunkSize, 0.0)
def RuntimePointCloudAddChunkSize(builder, chunkSize):
    """This method is deprecated. Please switch to AddChunkSize."""
    return AddChunkSize(builder, chunkSize)
def AddNames(builder, names): builder.PrependUOffsetTRelativeSlot(1, flatbuffers.number_types.UOffsetTFlags.py_type(names), 0)
def RuntimePointCloudAddNames(builder, names):
    """This method is deprecated. Please switch to AddNames."""
    return AddNames(builder, names)
def StartNamesVector(builder, numElems): return builder.StartVector(4, numElems, 4)
def RuntimePointCloudStartNamesVector(builder, numElems):
    """This method is deprecated. Please switch to Start."""
    return StartNamesVector(builder, numElems)
def AddChunks(builder, chunks): builder.PrependUOffsetTRelativeSlot(2, flatbuffers.number_types.UOffsetTFlags.py_type(chunks), 0)
def RuntimePointCloudAddChunks(builder, chunks):
    """This method is deprecated. Please switch to AddChunks."""
    return AddChunks(builder, chunks)
def StartChunksVector(builder, numElems): return builder.StartVector(4, numElems, 4)
def RuntimePointCloudStartChunksVector(builder, numElems):
    """This method is deprecated. Please switch to Start."""
    return StartChunksVector(builder, numElems)
def End(builder): return builder.EndObject()
def RuntimePointCloudEnd(builder):
    """This method is deprecated. Please switch to End."""
    return End(builder)
import WBIN.CloudPointsChunk
try:
    from typing import List
except:
    pass

class RuntimePointCloudT(object):

    # RuntimePointCloudT
    def __init__(self):
        self.chunkSize = 0.0  # type: float
        self.names = None  # type: List[str]
        self.chunks = None  # type: List[WBIN.CloudPointsChunk.CloudPointsChunkT]

    @classmethod
    def InitFromBuf(cls, buf, pos):
        runtimePointCloud = RuntimePointCloud()
        runtimePointCloud.Init(buf, pos)
        return cls.InitFromObj(runtimePointCloud)

    @classmethod
    def InitFromObj(cls, runtimePointCloud):
        x = RuntimePointCloudT()
        x._UnPack(runtimePointCloud)
        return x

    # RuntimePointCloudT
    def _UnPack(self, runtimePointCloud):
        if runtimePointCloud is None:
            return
        self.chunkSize = runtimePointCloud.ChunkSize()
        if not runtimePointCloud.NamesIsNone():
            self.names = []
            for i in range(runtimePointCloud.NamesLength()):
                self.names.append(runtimePointCloud.Names(i))
        if not runtimePointCloud.ChunksIsNone():
            self.chunks = []
            for i in range(runtimePointCloud.ChunksLength()):
                if runtimePointCloud.Chunks(i) is None:
                    self.chunks.append(None)
                else:
                    cloudPointsChunk_ = WBIN.CloudPointsChunk.CloudPointsChunkT.InitFromObj(runtimePointCloud.Chunks(i))
                    self.chunks.append(cloudPointsChunk_)

    # RuntimePointCloudT
    def Pack(self, builder):
        if self.names is not None:
            nameslist = []
            for i in range(len(self.names)):
                nameslist.append(builder.CreateString(self.names[i]))
            StartNamesVector(builder, len(self.names))
            for i in reversed(range(len(self.names))):
                builder.PrependUOffsetTRelative(nameslist[i])
            names = builder.EndVector()
        if self.chunks is not None:
            chunkslist = []
            for i in range(len(self.chunks)):
                chunkslist.append(self.chunks[i].Pack(builder))
            StartChunksVector(builder, len(self.chunks))
            for i in reversed(range(len(self.chunks))):
                builder.PrependUOffsetTRelative(chunkslist[i])
            chunks = builder.EndVector()
        Start(builder)
        AddChunkSize(builder, self.chunkSize)
        if self.names is not None:
            AddNames(builder, names)
        if self.chunks is not None:
            AddChunks(builder, chunks)
        runtimePointCloud = End(builder)
        return runtimePointCloud
