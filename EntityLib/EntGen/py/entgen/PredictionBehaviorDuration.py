
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *


class PredictionBehaviorDuration(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PredictionBehaviorDuration"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(PredictionBehaviorDuration.schema_name))
    @property
    def Locked(self): return Float(self._node.at("Locked"))
    @Locked.setter
    def Locked(self, val): self.Locked.set(val)
    @property
    def Step(self): return Float(self._node.at("Step"))
    @Step.setter
    def Step(self, val): self.Step.set(val)
    @property
    def Total(self): return Float(self._node.at("Total"))
    @Total.setter
    def Total(self, val): self.Total.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




