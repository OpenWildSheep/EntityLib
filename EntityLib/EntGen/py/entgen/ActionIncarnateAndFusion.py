
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Bool import *
from entgen.Float import *

from EntityLibPy import Node

class ActionIncarnateAndFusion(HelperObject):
    schema_name = "ActionIncarnateAndFusion"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionIncarnateAndFusion
        return ActionIncarnateAndFusion(entlib.load_node_file(sourcefile, entlib.get_schema(ActionIncarnateAndFusion.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionIncarnateAndFusion
        return ActionIncarnateAndFusion(entlib.make_node(ActionIncarnateAndFusion.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def FusionEndOutfitChangeDuration(self):  # type: ()->Float
        return Float(self._node.at("FusionEndOutfitChangeDuration"))
    @FusionEndOutfitChangeDuration.setter
    def FusionEndOutfitChangeDuration(self, val): self.FusionEndOutfitChangeDuration.set(val)
    @property
    def FusionEndRequested(self):  # type: ()->Bool
        return Bool(self._node.at("FusionEndRequested"))
    @FusionEndRequested.setter
    def FusionEndRequested(self, val): self.FusionEndRequested.set(val)
    @property
    def FusionStartRequested(self):  # type: ()->Bool
        return Bool(self._node.at("FusionStartRequested"))
    @FusionStartRequested.setter
    def FusionStartRequested(self, val): self.FusionStartRequested.set(val)
    @property
    def GameEffectHash(self):  # type: ()->String
        return String(self._node.at("GameEffectHash"))
    @GameEffectHash.setter
    def GameEffectHash(self, val): self.GameEffectHash.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




