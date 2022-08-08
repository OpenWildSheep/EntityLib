
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.Specie import *
from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *

from EntityLibPy import Node

class SpiritAnimalShrineGD(HelperObject):
    schema_name = "SpiritAnimalShrineGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SpiritAnimalShrineGD
        return SpiritAnimalShrineGD(entlib.load_node_file(sourcefile, entlib.get_schema(SpiritAnimalShrineGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SpiritAnimalShrineGD
        return SpiritAnimalShrineGD(entlib.make_node(SpiritAnimalShrineGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def InteractionDuration(self):  # type: ()->Float
        return Float(self._node.at("InteractionDuration"))
    @InteractionDuration.setter
    def InteractionDuration(self, val): self.InteractionDuration.set(val)
    @property
    def Specie(self):  # type: ()->Specie
        return Specie(self._node.at("Specie"))
    @Specie.setter
    def Specie(self, val): self.Specie.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def TimeHysteresis(self):  # type: ()->Float
        return Float(self._node.at("TimeHysteresis"))
    @TimeHysteresis.setter
    def TimeHysteresis(self, val): self.TimeHysteresis.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass



