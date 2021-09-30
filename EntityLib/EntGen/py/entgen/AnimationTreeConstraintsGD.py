
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.AnimationTreeConstraintsGD_BendData import *
from entgen.AnimationTreeConstraintsGD_ForceData import *
from entgen.AnimationTreeConstraintsGD_GrowData import *
from entgen.ComponentGD import *


class AnimationTreeConstraintsGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimationTreeConstraintsGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(AnimationTreeConstraintsGD.schema_name))
    @property
    def BendData(self): return AnimationTreeConstraintsGD_BendData(self._node.at("BendData"))
    @property
    def ForceData(self): return AnimationTreeConstraintsGD_ForceData(self._node.at("ForceData"))
    @property
    def GrowData(self): return AnimationTreeConstraintsGD_GrowData(self._node.at("GrowData"))
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




