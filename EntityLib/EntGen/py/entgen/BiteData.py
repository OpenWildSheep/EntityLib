
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *


class BiteData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/BiteData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(BiteData.schema_name))
    @property
    def CanBiteBiped(self): return Bool(self._node.at("CanBiteBiped"))
    @CanBiteBiped.setter
    def CanBiteBiped(self, val): self.CanBiteBiped.set(val)
    @property
    def CanBiteFriends(self): return Bool(self._node.at("CanBiteFriends"))
    @CanBiteFriends.setter
    def CanBiteFriends(self, val): self.CanBiteFriends.set(val)
    @property
    def CheckHotspotOrientation(self): return Bool(self._node.at("CheckHotspotOrientation"))
    @CheckHotspotOrientation.setter
    def CheckHotspotOrientation(self, val): self.CheckHotspotOrientation.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def bezierMove(self): return Bool(self._node.at("bezierMove"))
    @bezierMove.setter
    def bezierMove(self, val): self.bezierMove.set(val)
    @property
    def biteDamagePerSec(self): return Float(self._node.at("biteDamagePerSec"))
    @biteDamagePerSec.setter
    def biteDamagePerSec(self, val): self.biteDamagePerSec.set(val)
    @property
    def biteDefenseDamages(self): return Float(self._node.at("biteDefenseDamages"))
    @biteDefenseDamages.setter
    def biteDefenseDamages(self, val): self.biteDefenseDamages.set(val)
    @property
    def biteDuration(self): return Float(self._node.at("biteDuration"))
    @biteDuration.setter
    def biteDuration(self, val): self.biteDuration.set(val)
    @property
    def biteMaxRange(self): return Float(self._node.at("biteMaxRange"))
    @biteMaxRange.setter
    def biteMaxRange(self, val): self.biteMaxRange.set(val)
    pass




