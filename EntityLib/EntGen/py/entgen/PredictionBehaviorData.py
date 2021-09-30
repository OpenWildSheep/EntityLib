
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.PredictionBehaviorDuration import *


class PredictionBehaviorData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PredictionBehaviorData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(PredictionBehaviorData.schema_name))
    @property
    def Duration(self): return PredictionBehaviorDuration(self._node.at("Duration"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




