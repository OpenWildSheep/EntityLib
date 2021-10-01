
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.StyleMode import *
from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.SoundEventMapping import *
from entgen.String import *
from entgen.MountableSnapLine_ControlPoint import *
from entgen.OutfitPiece import *

from EntityLibPy import Node

class OutfitGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/OutfitGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->OutfitGD
        return OutfitGD(entlib.load_node_file(sourcefile, entlib.get_schema(OutfitGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->OutfitGD
        return OutfitGD(entlib.make_node(OutfitGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def SnapLine(self):  # type: ()->Array[MountableSnapLine_ControlPoint]
        return (lambda n: Array(MountableSnapLine_ControlPoint, n))(self._node.at("SnapLine"))
    @property
    def SoundEventMappingRules(self):  # type: ()->SoundEventMapping
        return SoundEventMapping(self._node.at("SoundEventMappingRules"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def clothes(self):  # type: ()->Array[OutfitPiece]
        return (lambda n: Array(OutfitPiece, n))(self._node.at("clothes"))
    @property
    def faction(self):  # type: ()->String
        return String(self._node.at("faction"))
    @faction.setter
    def faction(self, val): self.faction.set(val)
    @property
    def overrideSpeciesAudioCategory(self):  # type: ()->String
        return String(self._node.at("overrideSpeciesAudioCategory"))
    @overrideSpeciesAudioCategory.setter
    def overrideSpeciesAudioCategory(self, val): self.overrideSpeciesAudioCategory.set(val)
    @property
    def soundBank(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("soundBank"))
    @soundBank.setter
    def soundBank(self, val): self.soundBank.set(val)
    @property
    def soundTag(self):  # type: ()->String
        return String(self._node.at("soundTag"))
    @soundTag.setter
    def soundTag(self, val): self.soundTag.set(val)
    @property
    def specialOutfitStyle(self):  # type: ()->StyleMode
        return StyleMode(self._node.at("specialOutfitStyle"))
    @specialOutfitStyle.setter
    def specialOutfitStyle(self, val): self.specialOutfitStyle.set(val)
    @property
    def spirit(self):  # type: ()->Bool
        return Bool(self._node.at("spirit"))
    @spirit.setter
    def spirit(self, val): self.spirit.set(val)
    pass




