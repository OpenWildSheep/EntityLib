
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.CanTakeHit import *
from entgen.ComponentInput import *
from entgen.DeltaTimeFactor import *
from entgen.Invincible import *
from entgen.Life import *

from EntityLibPy import Node

class CreatureComponentInput(HelperObject):
    schema_name = "CreatureComponentInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CreatureComponentInput
        return CreatureComponentInput(entlib.load_node_file(sourcefile, entlib.get_schema(CreatureComponentInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CreatureComponentInput
        return CreatureComponentInput(entlib.make_node(CreatureComponentInput.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CanTakeHit(self):  # type: ()->CanTakeHit
        return CanTakeHit(self._node.at("CanTakeHit"))
    @property
    def DeltaTimeFactor(self):  # type: ()->DeltaTimeFactor
        return DeltaTimeFactor(self._node.at("DeltaTimeFactor"))
    @property
    def Invincible(self):  # type: ()->Invincible
        return Invincible(self._node.at("Invincible"))
    @property
    def Life(self):  # type: ()->Life
        return Life(self._node.at("Life"))
    @property
    def Super(self):  # type: ()->ComponentInput
        return ComponentInput(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




