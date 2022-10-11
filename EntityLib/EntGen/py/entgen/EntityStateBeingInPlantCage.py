
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.EntityRef import *
from entgen.String import *
from entgen.ActorState import *
from entgen.Float import *

from EntityLibPy import Node

class EntityStateBeingInPlantCage(HelperObject):
    schema_name = "EntityStateBeingInPlantCage"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateBeingInPlantCage
        return EntityStateBeingInPlantCage(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateBeingInPlantCage.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateBeingInPlantCage
        return EntityStateBeingInPlantCage(entlib.make_node(EntityStateBeingInPlantCage.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CageEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("CageEntityRef"))
    @CageEntityRef.setter
    def CageEntityRef(self, val): self.CageEntityRef.set(val)
    @property
    def MinProgressToFree(self):  # type: ()->Float
        return Float(self._node.at("MinProgressToFree"))
    @MinProgressToFree.setter
    def MinProgressToFree(self, val): self.MinProgressToFree.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




