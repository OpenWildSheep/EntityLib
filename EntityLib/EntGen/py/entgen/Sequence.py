
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.CinematicSlot import *

from EntityLibPy import Node

class Sequence(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/Sequence"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Sequence
        return Sequence(entlib.load_node_file(sourcefile, entlib.get_schema(Sequence.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Sequence
        return Sequence(entlib.make_node(Sequence.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ActivationDelay(self):  # type: ()->Float
        return Float(self._node.at("ActivationDelay"))
    @ActivationDelay.setter
    def ActivationDelay(self, val): self.ActivationDelay.set(val)
    @property
    def AutoSwitchToNextSequence(self):  # type: ()->Bool
        return Bool(self._node.at("AutoSwitchToNextSequence"))
    @AutoSwitchToNextSequence.setter
    def AutoSwitchToNextSequence(self, val): self.AutoSwitchToNextSequence.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def actors(self):  # type: ()->Array[CinematicSlot]
        return (lambda n: Array(CinematicSlot, n))(self._node.at("actors"))
    @property
    def loop(self):  # type: ()->Bool
        return Bool(self._node.at("loop"))
    @loop.setter
    def loop(self, val): self.loop.set(val)
    @property
    def name(self):  # type: ()->String
        return String(self._node.at("name"))
    @name.setter
    def name(self, val): self.name.set(val)
    pass




