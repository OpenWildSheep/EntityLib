
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.HotSpotType import *
from entgen.String import *
from entgen.EntityRef import *
from entgen.Float import *
from entgen.Quat import *
from entgen.Vector3 import *
from entgen.String import *

from EntityLibPy import Node

class HotspotData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/HotspotData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->HotspotData
        return HotspotData(entlib.load_node_file(sourcefile, entlib.get_schema(HotspotData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->HotspotData
        return HotspotData(entlib.make_node(HotspotData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Bone(self):  # type: ()->String
        return String(self._node.at("Bone"))
    @Bone.setter
    def Bone(self, val): self.Bone.set(val)
    @property
    def Offset(self):  # type: ()->Vector3
        return Vector3(self._node.at("Offset"))
    @Offset.setter
    def Offset(self, val): self.Offset.set(val)
    @property
    def Orientation(self):  # type: ()->Quat
        return Quat(self._node.at("Orientation"))
    @Orientation.setter
    def Orientation(self, val): self.Orientation.set(val)
    @property
    def Scale(self):  # type: ()->Float
        return Float(self._node.at("Scale"))
    @Scale.setter
    def Scale(self, val): self.Scale.set(val)
    @property
    def Tags(self):  # type: ()->PrimitiveSet[str]
        return (lambda n: PrimitiveSet(str, n))(self._node.at("Tags"))
    @property
    def TargetEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("TargetEntityRef"))
    @TargetEntityRef.setter
    def TargetEntityRef(self, val): self.TargetEntityRef.set(val)
    @property
    def Type_(self):  # type: ()->HotSpotType
        return HotSpotType(self._node.at("Type_"))
    @Type_.setter
    def Type_(self, val): self.Type_.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




