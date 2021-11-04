
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.PredictionBehaviorDuration import *

from EntityLibPy import Node

class PredictionBehaviorData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PredictionBehaviorData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PredictionBehaviorData
        return PredictionBehaviorData(entlib.load_node_file(sourcefile, entlib.get_schema(PredictionBehaviorData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PredictionBehaviorData
        return PredictionBehaviorData(entlib.make_node(PredictionBehaviorData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Duration(self):  # type: ()->PredictionBehaviorDuration
        return PredictionBehaviorDuration(self._node.at("Duration"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




