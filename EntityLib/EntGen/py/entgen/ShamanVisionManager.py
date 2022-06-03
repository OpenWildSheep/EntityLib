
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.Manager import *

from EntityLibPy import Node

class ShamanVisionManager(HelperObject):
    schema_name = "ShamanVisionManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ShamanVisionManager
        return ShamanVisionManager(entlib.load_node_file(sourcefile, entlib.get_schema(ShamanVisionManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ShamanVisionManager
        return ShamanVisionManager(entlib.make_node(ShamanVisionManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def HighlightFactorGoddess(self):  # type: ()->Float
        return Float(self._node.at("HighlightFactorGoddess"))
    @HighlightFactorGoddess.setter
    def HighlightFactorGoddess(self, val): self.HighlightFactorGoddess.set(val)
    @property
    def HighlightFactorPlayer(self):  # type: ()->Float
        return Float(self._node.at("HighlightFactorPlayer"))
    @HighlightFactorPlayer.setter
    def HighlightFactorPlayer(self, val): self.HighlightFactorPlayer.set(val)
    @property
    def HighlightFactorSpecie(self):  # type: ()->Float
        return Float(self._node.at("HighlightFactorSpecie"))
    @HighlightFactorSpecie.setter
    def HighlightFactorSpecie(self, val): self.HighlightFactorSpecie.set(val)
    @property
    def ShowEnemiesState(self):  # type: ()->Bool
        return Bool(self._node.at("ShowEnemiesState"))
    @ShowEnemiesState.setter
    def ShowEnemiesState(self, val): self.ShowEnemiesState.set(val)
    @property
    def ShowInjuredState(self):  # type: ()->Bool
        return Bool(self._node.at("ShowInjuredState"))
    @ShowInjuredState.setter
    def ShowInjuredState(self, val): self.ShowInjuredState.set(val)
    @property
    def ShowPlayersState(self):  # type: ()->Bool
        return Bool(self._node.at("ShowPlayersState"))
    @ShowPlayersState.setter
    def ShowPlayersState(self, val): self.ShowPlayersState.set(val)
    @property
    def ShowPrisonersState(self):  # type: ()->Bool
        return Bool(self._node.at("ShowPrisonersState"))
    @ShowPrisonersState.setter
    def ShowPrisonersState(self, val): self.ShowPrisonersState.set(val)
    @property
    def ShowSpecieIcons(self):  # type: ()->Bool
        return Bool(self._node.at("ShowSpecieIcons"))
    @ShowSpecieIcons.setter
    def ShowSpecieIcons(self, val): self.ShowSpecieIcons.set(val)
    @property
    def StateMinSizeDistance(self):  # type: ()->Float
        return Float(self._node.at("StateMinSizeDistance"))
    @StateMinSizeDistance.setter
    def StateMinSizeDistance(self, val): self.StateMinSizeDistance.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def TimerFactorGoddess(self):  # type: ()->Float
        return Float(self._node.at("TimerFactorGoddess"))
    @TimerFactorGoddess.setter
    def TimerFactorGoddess(self, val): self.TimerFactorGoddess.set(val)
    @property
    def TimerFactorPlayer(self):  # type: ()->Float
        return Float(self._node.at("TimerFactorPlayer"))
    @TimerFactorPlayer.setter
    def TimerFactorPlayer(self, val): self.TimerFactorPlayer.set(val)
    @property
    def TimerFactorSpecie(self):  # type: ()->Float
        return Float(self._node.at("TimerFactorSpecie"))
    @TimerFactorSpecie.setter
    def TimerFactorSpecie(self, val): self.TimerFactorSpecie.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




