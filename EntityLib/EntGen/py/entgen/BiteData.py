
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *

from EntityLibPy import Node

class BiteData(HelperObject):
    schema_name = "BiteData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BiteData
        return BiteData(entlib.load_node_file(sourcefile, entlib.get_schema(BiteData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BiteData
        return BiteData(entlib.make_node(BiteData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CanBiteBiped(self):  # type: ()->Bool
        return Bool(self._node.at("CanBiteBiped"))
    @CanBiteBiped.setter
    def CanBiteBiped(self, val): self.CanBiteBiped.set(val)
    @property
    def CanBiteFriends(self):  # type: ()->Bool
        return Bool(self._node.at("CanBiteFriends"))
    @CanBiteFriends.setter
    def CanBiteFriends(self, val): self.CanBiteFriends.set(val)
    @property
    def CheckHotspotOrientation(self):  # type: ()->Bool
        return Bool(self._node.at("CheckHotspotOrientation"))
    @CheckHotspotOrientation.setter
    def CheckHotspotOrientation(self, val): self.CheckHotspotOrientation.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def bezierMove(self):  # type: ()->Bool
        return Bool(self._node.at("bezierMove"))
    @bezierMove.setter
    def bezierMove(self, val): self.bezierMove.set(val)
    @property
    def biteDamagePerSec(self):  # type: ()->Float
        return Float(self._node.at("biteDamagePerSec"))
    @biteDamagePerSec.setter
    def biteDamagePerSec(self, val): self.biteDamagePerSec.set(val)
    @property
    def biteDefenseDamages(self):  # type: ()->Float
        return Float(self._node.at("biteDefenseDamages"))
    @biteDefenseDamages.setter
    def biteDefenseDamages(self, val): self.biteDefenseDamages.set(val)
    @property
    def biteDuration(self):  # type: ()->Float
        return Float(self._node.at("biteDuration"))
    @biteDuration.setter
    def biteDuration(self, val): self.biteDuration.set(val)
    @property
    def biteMaxRange(self):  # type: ()->Float
        return Float(self._node.at("biteMaxRange"))
    @biteMaxRange.setter
    def biteMaxRange(self, val): self.biteMaxRange.set(val)
    pass




