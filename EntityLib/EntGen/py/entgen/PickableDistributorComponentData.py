
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.HotSpotType import *
from entgen.String import *
from entgen.EntityRef import *


class PickableDistributorComponentData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PickableDistributorComponentData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(PickableDistributorComponentData.schema_name))
    @property
    def EntityRef(self): return EntityRef(self._node.at("EntityRef"))
    @EntityRef.setter
    def EntityRef(self, val): self.EntityRef.set(val)
    @property
    def HotspotType(self): return HotSpotType(self._node.at("HotspotType"))
    @HotspotType.setter
    def HotspotType(self, val): self.HotspotType.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




