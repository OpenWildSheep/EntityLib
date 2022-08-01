# automatically generated by the FlatBuffers compiler, do not modify

# namespace: WBIN

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class HeightMapLayer(object):
    __slots__ = ['_tab']

    @classmethod
    def SizeOf(cls):
        return 20

    # HeightMapLayer
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # HeightMapLayer
    def Normal(self, obj):
        obj.Init(self._tab.Bytes, self._tab.Pos + 0)
        return obj

    # HeightMapLayer
    def Height(self): return self._tab.Get(flatbuffers.number_types.Float32Flags, self._tab.Pos + flatbuffers.number_types.UOffsetTFlags.py_type(12))
    # HeightMapLayer
    def Physicsmaterialid(self): return self._tab.Get(flatbuffers.number_types.Uint8Flags, self._tab.Pos + flatbuffers.number_types.UOffsetTFlags.py_type(16))

def CreateHeightMapLayer(builder, normal_x, normal_y, normal_z, height, physicsmaterialid):
    builder.Prep(4, 20)
    builder.Pad(3)
    builder.PrependUint8(physicsmaterialid)
    builder.PrependFloat32(height)
    builder.Prep(4, 12)
    builder.PrependFloat32(normal_z)
    builder.PrependFloat32(normal_y)
    builder.PrependFloat32(normal_x)
    return builder.Offset()

import WBIN.Float3
try:
    from typing import Optional
except:
    pass

class HeightMapLayerT(object):

    # HeightMapLayerT
    def __init__(self):
        self.normal = None  # type: Optional[WBIN.Float3.Float3T]
        self.height = 0.0  # type: float
        self.physicsmaterialid = 0  # type: int

    @classmethod
    def InitFromBuf(cls, buf, pos):
        heightMapLayer = HeightMapLayer()
        heightMapLayer.Init(buf, pos)
        return cls.InitFromObj(heightMapLayer)

    @classmethod
    def InitFromObj(cls, heightMapLayer):
        x = HeightMapLayerT()
        x._UnPack(heightMapLayer)
        return x

    # HeightMapLayerT
    def _UnPack(self, heightMapLayer):
        if heightMapLayer is None:
            return
        if heightMapLayer.Normal(WBIN.Float3.Float3()) is not None:
            self.normal = WBIN.Float3.Float3T.InitFromObj(heightMapLayer.Normal(WBIN.Float3.Float3()))
        self.height = heightMapLayer.Height()
        self.physicsmaterialid = heightMapLayer.Physicsmaterialid()

    # HeightMapLayerT
    def Pack(self, builder):
        return CreateHeightMapLayer(builder, self.normal.x, self.normal.y, self.normal.z, self.height, self.physicsmaterialid)
