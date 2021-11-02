
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *

from EntityLibPy import Node

class AnimationTreeConstraintsGD_BendSoundEventData(HelperObject):
    schema_name = "AnimationTreeConstraintsGD::BendSoundEventData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationTreeConstraintsGD_BendSoundEventData
        return AnimationTreeConstraintsGD_BendSoundEventData(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationTreeConstraintsGD_BendSoundEventData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationTreeConstraintsGD_BendSoundEventData
        return AnimationTreeConstraintsGD_BendSoundEventData(entlib.make_node(AnimationTreeConstraintsGD_BendSoundEventData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BendStartEventName(self):  # type: ()->String
        return String(self._node.at("BendStartEventName"))
    @BendStartEventName.setter
    def BendStartEventName(self, val): self.BendStartEventName.set(val)
    @property
    def CatapultStartEventName(self):  # type: ()->String
        return String(self._node.at("CatapultStartEventName"))
    @CatapultStartEventName.setter
    def CatapultStartEventName(self, val): self.CatapultStartEventName.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




