
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class PredictionBehaviorDuration(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PredictionBehaviorDuration"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PredictionBehaviorDuration
        return PredictionBehaviorDuration(entlib.load_node_file(sourcefile, entlib.get_schema(PredictionBehaviorDuration.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PredictionBehaviorDuration
        return PredictionBehaviorDuration(entlib.make_node(PredictionBehaviorDuration.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Locked(self):  # type: ()->Float
        return Float(self._node.at("Locked"))
    @Locked.setter
    def Locked(self, val): self.Locked.set(val)
    @property
    def Step(self):  # type: ()->Float
        return Float(self._node.at("Step"))
    @Step.setter
    def Step(self, val): self.Step.set(val)
    @property
    def Total(self):  # type: ()->Float
        return Float(self._node.at("Total"))
    @Total.setter
    def Total(self, val): self.Total.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




