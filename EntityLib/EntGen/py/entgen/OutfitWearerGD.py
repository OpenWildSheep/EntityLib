
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.EntityRef import *
from entgen.Float import *

from EntityLibPy import Node

class OutfitWearerGD(HelperObject):
    schema_name = "OutfitWearerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->OutfitWearerGD
        return OutfitWearerGD(entlib.load_node_file(sourcefile, entlib.get_schema(OutfitWearerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->OutfitWearerGD
        return OutfitWearerGD(entlib.make_node(OutfitWearerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def InventoryEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("InventoryEntityRef"))
    @InventoryEntityRef.setter
    def InventoryEntityRef(self, val): self.InventoryEntityRef.set(val)
    @property
    def OutfitFadeDelay(self):  # type: ()->Float
        return Float(self._node.at("OutfitFadeDelay"))
    @OutfitFadeDelay.setter
    def OutfitFadeDelay(self, val): self.OutfitFadeDelay.set(val)
    @property
    def OutfitFadeDuration(self):  # type: ()->Float
        return Float(self._node.at("OutfitFadeDuration"))
    @OutfitFadeDuration.setter
    def OutfitFadeDuration(self, val): self.OutfitFadeDuration.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




