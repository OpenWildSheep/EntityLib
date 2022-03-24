
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.EnergySide import *
from entgen.EnergyValue import *
from entgen.RegenField import *
from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.GameEffect import *

from EntityLibPy import Node

class RegenEffect(HelperObject):
    schema_name = "RegenEffect"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RegenEffect
        return RegenEffect(entlib.load_node_file(sourcefile, entlib.get_schema(RegenEffect.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RegenEffect
        return RegenEffect(entlib.make_node(RegenEffect.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EnergyValue(self):  # type: ()->EnergyValue
        return EnergyValue(self._node.at("EnergyValue"))
    @EnergyValue.setter
    def EnergyValue(self, val): self.EnergyValue.set(val)
    @property
    def Field(self):  # type: ()->RegenField
        return RegenField(self._node.at("Field"))
    @Field.setter
    def Field(self, val): self.Field.set(val)
    @property
    def InnerMultiplier(self):  # type: ()->Float
        return Float(self._node.at("InnerMultiplier"))
    @InnerMultiplier.setter
    def InnerMultiplier(self, val): self.InnerMultiplier.set(val)
    @property
    def InnerRadius(self):  # type: ()->Float
        return Float(self._node.at("InnerRadius"))
    @InnerRadius.setter
    def InnerRadius(self, val): self.InnerRadius.set(val)
    @property
    def Margin(self):  # type: ()->Float
        return Float(self._node.at("Margin"))
    @Margin.setter
    def Margin(self, val): self.Margin.set(val)
    @property
    def OuterMultiplier(self):  # type: ()->Float
        return Float(self._node.at("OuterMultiplier"))
    @OuterMultiplier.setter
    def OuterMultiplier(self, val): self.OuterMultiplier.set(val)
    @property
    def State(self):  # type: ()->EnergySide
        return EnergySide(self._node.at("State"))
    @State.setter
    def State(self, val): self.State.set(val)
    @property
    def Super(self):  # type: ()->GameEffect
        return GameEffect(self._node.at("Super"))
    @property
    def UseNewRegen(self):  # type: ()->Bool
        return Bool(self._node.at("UseNewRegen"))
    @UseNewRegen.setter
    def UseNewRegen(self, val): self.UseNewRegen.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




