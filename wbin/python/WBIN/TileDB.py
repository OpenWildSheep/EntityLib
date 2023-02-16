# automatically generated by the FlatBuffers compiler, do not modify

# namespace: WBIN

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class TileDB(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAs(cls, buf, offset=0):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = TileDB()
        x.Init(buf, n + offset)
        return x

    @classmethod
    def GetRootAsTileDB(cls, buf, offset=0):
        """This method is deprecated. Please switch to GetRootAs."""
        return cls.GetRootAs(buf, offset)
    # TileDB
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # TileDB
    def TileCount(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            x = o + self._tab.Pos
            from WBIN.UInt2 import UInt2
            obj = UInt2()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # TileDB
    def TileResolution(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        if o != 0:
            x = o + self._tab.Pos
            from WBIN.UInt2 import UInt2
            obj = UInt2()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # TileDB
    def TileMeterSize(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(8))
        if o != 0:
            x = o + self._tab.Pos
            from WBIN.Float2 import Float2
            obj = Float2()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # TileDB
    def Tiles(self, j):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(10))
        if o != 0:
            x = self._tab.Vector(o)
            x += flatbuffers.number_types.UOffsetTFlags.py_type(j) * 4
            x = self._tab.Indirect(x)
            from WBIN.TileRef import TileRef
            obj = TileRef()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # TileDB
    def TilesLength(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(10))
        if o != 0:
            return self._tab.VectorLen(o)
        return 0

    # TileDB
    def TilesIsNone(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(10))
        return o == 0

def Start(builder): builder.StartObject(4)
def TileDBStart(builder):
    """This method is deprecated. Please switch to Start."""
    return Start(builder)
def AddTileCount(builder, tileCount): builder.PrependStructSlot(0, flatbuffers.number_types.UOffsetTFlags.py_type(tileCount), 0)
def TileDBAddTileCount(builder, tileCount):
    """This method is deprecated. Please switch to AddTileCount."""
    return AddTileCount(builder, tileCount)
def AddTileResolution(builder, tileResolution): builder.PrependStructSlot(1, flatbuffers.number_types.UOffsetTFlags.py_type(tileResolution), 0)
def TileDBAddTileResolution(builder, tileResolution):
    """This method is deprecated. Please switch to AddTileResolution."""
    return AddTileResolution(builder, tileResolution)
def AddTileMeterSize(builder, tileMeterSize): builder.PrependStructSlot(2, flatbuffers.number_types.UOffsetTFlags.py_type(tileMeterSize), 0)
def TileDBAddTileMeterSize(builder, tileMeterSize):
    """This method is deprecated. Please switch to AddTileMeterSize."""
    return AddTileMeterSize(builder, tileMeterSize)
def AddTiles(builder, tiles): builder.PrependUOffsetTRelativeSlot(3, flatbuffers.number_types.UOffsetTFlags.py_type(tiles), 0)
def TileDBAddTiles(builder, tiles):
    """This method is deprecated. Please switch to AddTiles."""
    return AddTiles(builder, tiles)
def StartTilesVector(builder, numElems): return builder.StartVector(4, numElems, 4)
def TileDBStartTilesVector(builder, numElems):
    """This method is deprecated. Please switch to Start."""
    return StartTilesVector(builder, numElems)
def End(builder): return builder.EndObject()
def TileDBEnd(builder):
    """This method is deprecated. Please switch to End."""
    return End(builder)
import WBIN.Float2
import WBIN.TileRef
import WBIN.UInt2
try:
    from typing import List, Optional
except:
    pass

class TileDBT(object):

    # TileDBT
    def __init__(self):
        self.tileCount = None  # type: Optional[WBIN.UInt2.UInt2T]
        self.tileResolution = None  # type: Optional[WBIN.UInt2.UInt2T]
        self.tileMeterSize = None  # type: Optional[WBIN.Float2.Float2T]
        self.tiles = None  # type: List[WBIN.TileRef.TileRefT]

    @classmethod
    def InitFromBuf(cls, buf, pos):
        tileDB = TileDB()
        tileDB.Init(buf, pos)
        return cls.InitFromObj(tileDB)

    @classmethod
    def InitFromObj(cls, tileDB):
        x = TileDBT()
        x._UnPack(tileDB)
        return x

    # TileDBT
    def _UnPack(self, tileDB):
        if tileDB is None:
            return
        if tileDB.TileCount() is not None:
            self.tileCount = WBIN.UInt2.UInt2T.InitFromObj(tileDB.TileCount())
        if tileDB.TileResolution() is not None:
            self.tileResolution = WBIN.UInt2.UInt2T.InitFromObj(tileDB.TileResolution())
        if tileDB.TileMeterSize() is not None:
            self.tileMeterSize = WBIN.Float2.Float2T.InitFromObj(tileDB.TileMeterSize())
        if not tileDB.TilesIsNone():
            self.tiles = []
            for i in range(tileDB.TilesLength()):
                if tileDB.Tiles(i) is None:
                    self.tiles.append(None)
                else:
                    tileRef_ = WBIN.TileRef.TileRefT.InitFromObj(tileDB.Tiles(i))
                    self.tiles.append(tileRef_)

    # TileDBT
    def Pack(self, builder):
        if self.tiles is not None:
            tileslist = []
            for i in range(len(self.tiles)):
                tileslist.append(self.tiles[i].Pack(builder))
            StartTilesVector(builder, len(self.tiles))
            for i in reversed(range(len(self.tiles))):
                builder.PrependUOffsetTRelative(tileslist[i])
            tiles = builder.EndVector()
        Start(builder)
        if self.tileCount is not None:
            tileCount = self.tileCount.Pack(builder)
            AddTileCount(builder, tileCount)
        if self.tileResolution is not None:
            tileResolution = self.tileResolution.Pack(builder)
            AddTileResolution(builder, tileResolution)
        if self.tileMeterSize is not None:
            tileMeterSize = self.tileMeterSize.Pack(builder)
            AddTileMeterSize(builder, tileMeterSize)
        if self.tiles is not None:
            AddTiles(builder, tiles)
        tileDB = End(builder)
        return tileDB