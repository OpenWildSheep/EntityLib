
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.EntityRef import *
from entgen.Float import *


class OutfitWearerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/OutfitWearerGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(OutfitWearerGD.schema_name))
    @property
    def InventoryEntityRef(self): return EntityRef(self._node.at("InventoryEntityRef"))
    @InventoryEntityRef.setter
    def InventoryEntityRef(self, val): self.InventoryEntityRef.set(val)
    @property
    def OutfitFadeDelay(self): return Float(self._node.at("OutfitFadeDelay"))
    @OutfitFadeDelay.setter
    def OutfitFadeDelay(self, val): self.OutfitFadeDelay.set(val)
    @property
    def OutfitFadeDuration(self): return Float(self._node.at("OutfitFadeDuration"))
    @OutfitFadeDuration.setter
    def OutfitFadeDuration(self, val): self.OutfitFadeDuration.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




