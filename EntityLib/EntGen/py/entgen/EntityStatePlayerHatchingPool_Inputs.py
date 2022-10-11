
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class EntityStatePlayerHatchingPool_Inputs(HelperObject):
    schema_name = "EntityStatePlayerHatchingPool::Inputs"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStatePlayerHatchingPool_Inputs
        return EntityStatePlayerHatchingPool_Inputs(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStatePlayerHatchingPool_Inputs.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStatePlayerHatchingPool_Inputs
        return EntityStatePlayerHatchingPool_Inputs(entlib.make_node(EntityStatePlayerHatchingPool_Inputs.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DistanceFromPoolToPlayAnim(self):  # type: ()->Float
        return Float(self._node.at("DistanceFromPoolToPlayAnim"))
    @DistanceFromPoolToPlayAnim.setter
    def DistanceFromPoolToPlayAnim(self, val): self.DistanceFromPoolToPlayAnim.set(val)
    @property
    def HatchingDuration(self):  # type: ()->Float
        return Float(self._node.at("HatchingDuration"))
    @HatchingDuration.setter
    def HatchingDuration(self, val): self.HatchingDuration.set(val)
    @property
    def WalkSpeed(self):  # type: ()->Float
        return Float(self._node.at("WalkSpeed"))
    @WalkSpeed.setter
    def WalkSpeed(self, val): self.WalkSpeed.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




