
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.BiomeSoundBank_sBiomeEnv import *

from EntityLibPy import Node

class BiomeSoundBank_sBiomeSound(HelperObject):
    schema_name = "BiomeSoundBank::sBiomeSound"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BiomeSoundBank_sBiomeSound
        return BiomeSoundBank_sBiomeSound(entlib.load_node_file(sourcefile, entlib.get_schema(BiomeSoundBank_sBiomeSound.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BiomeSoundBank_sBiomeSound
        return BiomeSoundBank_sBiomeSound(entlib.make_node(BiomeSoundBank_sBiomeSound.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AuxSend(self):  # type: ()->String
        return String(self._node.at("AuxSend"))
    @AuxSend.setter
    def AuxSend(self, val): self.AuxSend.set(val)
    @property
    def Bank(self):  # type: ()->String
        return String(self._node.at("Bank"))
    @Bank.setter
    def Bank(self, val): self.Bank.set(val)
    @property
    def Event(self):  # type: ()->String
        return String(self._node.at("Event"))
    @Event.setter
    def Event(self, val): self.Event.set(val)
    @property
    def Event_Stop(self):  # type: ()->String
        return String(self._node.at("Event_Stop"))
    @Event_Stop.setter
    def Event_Stop(self, val): self.Event_Stop.set(val)
    @property
    def MainState(self):  # type: ()->String
        return String(self._node.at("MainState"))
    @MainState.setter
    def MainState(self, val): self.MainState.set(val)
    @property
    def Super(self):  # type: ()->BiomeSoundBank_sBiomeEnv
        return BiomeSoundBank_sBiomeEnv(self._node.at("Super"))
    @property
    def Tag(self):  # type: ()->String
        return String(self._node.at("Tag"))
    @Tag.setter
    def Tag(self, val): self.Tag.set(val)
    @property
    def Volume(self):  # type: ()->String
        return String(self._node.at("Volume"))
    @Volume.setter
    def Volume(self, val): self.Volume.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




