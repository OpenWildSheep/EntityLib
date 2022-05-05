
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.EntityRef import *
from entgen.Float import *
from entgen.Position import *
from entgen.EntityRef import *

from EntityLibPy import Node

class EntityStateBridgeAttracted(HelperObject):
    schema_name = "EntityStateBridgeAttracted"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateBridgeAttracted
        return EntityStateBridgeAttracted(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateBridgeAttracted.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateBridgeAttracted
        return EntityStateBridgeAttracted(entlib.make_node(EntityStateBridgeAttracted.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AttachPointsRef(self):  # type: ()->PrimArray[EntityRef]
        return (lambda n: PrimArray(EntityRef, n))(self._node.at("AttachPointsRef"))
    @AttachPointsRef.setter
    def AttachPointsRef(self, val): self.AttachPointsRef.set(val)
    @property
    def AttachTime(self):  # type: ()->Float
        return Float(self._node.at("AttachTime"))
    @AttachTime.setter
    def AttachTime(self, val): self.AttachTime.set(val)
    @property
    def AttractionTarget(self):  # type: ()->Position
        return Position(self._node.at("AttractionTarget"))
    @property
    def BridgeLinkRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("BridgeLinkRef"))
    @BridgeLinkRef.setter
    def BridgeLinkRef(self, val): self.BridgeLinkRef.set(val)
    @property
    def GroundAttachRaycastLength(self):  # type: ()->Float
        return Float(self._node.at("GroundAttachRaycastLength"))
    @GroundAttachRaycastLength.setter
    def GroundAttachRaycastLength(self, val): self.GroundAttachRaycastLength.set(val)
    @property
    def HotspotName(self):  # type: ()->String
        return String(self._node.at("HotspotName"))
    @HotspotName.setter
    def HotspotName(self, val): self.HotspotName.set(val)
    @property
    def MaximalAttachDistance(self):  # type: ()->Float
        return Float(self._node.at("MaximalAttachDistance"))
    @MaximalAttachDistance.setter
    def MaximalAttachDistance(self, val): self.MaximalAttachDistance.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




