
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Float import *

from EntityLibPy import Node

class DisplaceNoiseListItem(HelperObject):

    @property
    def DisplaceDistance(self):  # type: ()->Float
        return Float(self._node.at("DisplaceDistance"))
    @DisplaceDistance.setter
    def DisplaceDistance(self, val): self.DisplaceDistance.set(val)
    @property
    def LuminanceCenter(self):  # type: ()->Float
        return Float(self._node.at("LuminanceCenter"))
    @LuminanceCenter.setter
    def LuminanceCenter(self, val): self.LuminanceCenter.set(val)
    @property
    def MapChannel(self):  # type: ()->Int
        return Int(self._node.at("MapChannel"))
    @MapChannel.setter
    def MapChannel(self, val): self.MapChannel.set(val)
    @property
    def MotifName(self):  # type: ()->String
        return String(self._node.at("MotifName"))
    @MotifName.setter
    def MotifName(self, val): self.MotifName.set(val)
    @property
    def MotifOffsetX(self):  # type: ()->Float
        return Float(self._node.at("MotifOffsetX"))
    @MotifOffsetX.setter
    def MotifOffsetX(self, val): self.MotifOffsetX.set(val)
    @property
    def MotifOffsetY(self):  # type: ()->Float
        return Float(self._node.at("MotifOffsetY"))
    @MotifOffsetY.setter
    def MotifOffsetY(self, val): self.MotifOffsetY.set(val)
    @property
    def MotifRotationZ(self):  # type: ()->Float
        return Float(self._node.at("MotifRotationZ"))
    @MotifRotationZ.setter
    def MotifRotationZ(self, val): self.MotifRotationZ.set(val)
    @property
    def MotifSizeX(self):  # type: ()->Float
        return Float(self._node.at("MotifSizeX"))
    @MotifSizeX.setter
    def MotifSizeX(self, val): self.MotifSizeX.set(val)
    @property
    def MotifSizeY(self):  # type: ()->Float
        return Float(self._node.at("MotifSizeY"))
    @MotifSizeY.setter
    def MotifSizeY(self, val): self.MotifSizeY.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




