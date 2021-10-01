
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.HotSpotType import *
from entgen.String import *
from entgen.EntityRef import *

from EntityLibPy import Node

class PickableDistributorComponentData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PickableDistributorComponentData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PickableDistributorComponentData
        return PickableDistributorComponentData(entlib.load_node_file(sourcefile, entlib.get_schema(PickableDistributorComponentData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PickableDistributorComponentData
        return PickableDistributorComponentData(entlib.make_node(PickableDistributorComponentData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("EntityRef"))
    @EntityRef.setter
    def EntityRef(self, val): self.EntityRef.set(val)
    @property
    def HotspotType(self):  # type: ()->HotSpotType
        return HotSpotType(self._node.at("HotspotType"))
    @HotspotType.setter
    def HotspotType(self, val): self.HotspotType.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




