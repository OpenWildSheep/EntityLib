
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.ReviveSide import *
from entgen.String import *
from entgen.ActorState import *
from entgen.Float import *
from entgen.StunGauge import *

from EntityLibPy import Node

class ActorStateAlive(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ActorStateAlive"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateAlive
        return ActorStateAlive(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateAlive.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateAlive
        return ActorStateAlive(entlib.make_node(ActorStateAlive.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Life(self):  # type: ()->Float
        return Float(self._node.at("Life"))
    @Life.setter
    def Life(self, val): self.Life.set(val)
    @property
    def ReviveSide(self):  # type: ()->ReviveSide
        return ReviveSide(self._node.at("ReviveSide"))
    @ReviveSide.setter
    def ReviveSide(self, val): self.ReviveSide.set(val)
    @property
    def StunGauge(self):  # type: ()->StunGauge
        return StunGauge(self._node.at("StunGauge"))
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




