
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.AnimationTreeConstraintsGD_BendData import *
from entgen.AnimationTreeConstraintsGD_ForceData import *
from entgen.AnimationTreeConstraintsGD_GrowData import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class AnimationTreeConstraintsGD(HelperObject):
    schema_name = "AnimationTreeConstraintsGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationTreeConstraintsGD
        return AnimationTreeConstraintsGD(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationTreeConstraintsGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationTreeConstraintsGD
        return AnimationTreeConstraintsGD(entlib.make_node(AnimationTreeConstraintsGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BendData(self):  # type: ()->AnimationTreeConstraintsGD_BendData
        return AnimationTreeConstraintsGD_BendData(self._node.at("BendData"))
    @property
    def ForceData(self):  # type: ()->AnimationTreeConstraintsGD_ForceData
        return AnimationTreeConstraintsGD_ForceData(self._node.at("ForceData"))
    @property
    def GrowData(self):  # type: ()->AnimationTreeConstraintsGD_GrowData
        return AnimationTreeConstraintsGD_GrowData(self._node.at("GrowData"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




