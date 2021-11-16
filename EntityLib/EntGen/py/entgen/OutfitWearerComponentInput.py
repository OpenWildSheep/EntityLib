
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentInput import *
from entgen.FadeDuration import *
from entgen.OutfitWearerComponentInput_ReviveSide import *
from entgen.OutfitWearerComponentInput_ReviveState import *
from entgen.InventoryTags import *

from EntityLibPy import Node

class OutfitWearerComponentInput(HelperObject):
    schema_name = "OutfitWearerComponentInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->OutfitWearerComponentInput
        return OutfitWearerComponentInput(entlib.load_node_file(sourcefile, entlib.get_schema(OutfitWearerComponentInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->OutfitWearerComponentInput
        return OutfitWearerComponentInput(entlib.make_node(OutfitWearerComponentInput.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def FadeDuration(self):  # type: ()->FadeDuration
        return FadeDuration(self._node.at("FadeDuration"))
    @property
    def OutfitTags(self):  # type: ()->PrimArray[InventoryTags]
        return (lambda n: PrimArray(InventoryTags, n))(self._node.at("OutfitTags"))
    @OutfitTags.setter
    def OutfitTags(self, val): self.OutfitTags.set(val)
    @property
    def ReviveSide(self):  # type: ()->OutfitWearerComponentInput_ReviveSide
        return OutfitWearerComponentInput_ReviveSide(self._node.at("ReviveSide"))
    @property
    def ReviveState(self):  # type: ()->OutfitWearerComponentInput_ReviveState
        return OutfitWearerComponentInput_ReviveState(self._node.at("ReviveState"))
    @property
    def Super(self):  # type: ()->ComponentInput
        return ComponentInput(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




