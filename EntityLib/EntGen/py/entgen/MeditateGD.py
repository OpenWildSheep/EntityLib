
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.SpeedMode import *
from entgen.String import *
from entgen.ComponentGD import *
from entgen.String import *

from EntityLibPy import Node

class MeditateGD(HelperObject):
    schema_name = "MeditateGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MeditateGD
        return MeditateGD(entlib.load_node_file(sourcefile, entlib.get_schema(MeditateGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MeditateGD
        return MeditateGD(entlib.make_node(MeditateGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def GameEffectNames(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("GameEffectNames"))
    @GameEffectNames.setter
    def GameEffectNames(self, val): self.GameEffectNames.set(val)
    @property
    def MinSpeedToLeave(self):  # type: ()->SpeedMode
        return SpeedMode(self._node.at("MinSpeedToLeave"))
    @MinSpeedToLeave.setter
    def MinSpeedToLeave(self, val): self.MinSpeedToLeave.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




