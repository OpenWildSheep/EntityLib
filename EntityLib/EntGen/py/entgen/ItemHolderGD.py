
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *


class ItemHolderGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ItemHolderGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(ItemHolderGD.schema_name))
    @property
    def HotspotDefault(self): return String(self._node.at("HotspotDefault"))
    @HotspotDefault.setter
    def HotspotDefault(self, val): self.HotspotDefault.set(val)
    @property
    def HotspotHandLeft(self): return String(self._node.at("HotspotHandLeft"))
    @HotspotHandLeft.setter
    def HotspotHandLeft(self, val): self.HotspotHandLeft.set(val)
    @property
    def HotspotHandRight(self): return String(self._node.at("HotspotHandRight"))
    @HotspotHandRight.setter
    def HotspotHandRight(self, val): self.HotspotHandRight.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def Visible(self): return Bool(self._node.at("Visible"))
    @Visible.setter
    def Visible(self, val): self.Visible.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




