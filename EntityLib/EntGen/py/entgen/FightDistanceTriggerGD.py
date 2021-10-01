
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.DistanceTriggerGD import *

from EntityLibPy import Node

class FightDistanceTriggerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FightDistanceTriggerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FightDistanceTriggerGD
        return FightDistanceTriggerGD(entlib.load_node_file(sourcefile, entlib.get_schema(FightDistanceTriggerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FightDistanceTriggerGD
        return FightDistanceTriggerGD(entlib.make_node(FightDistanceTriggerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->DistanceTriggerGD
        return DistanceTriggerGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




