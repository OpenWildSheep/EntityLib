
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *


class SpawningParameter(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/SpawningParameter"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(SpawningParameter.schema_name))
    @property
    def EntityName(self): return String(self._node.at("EntityName"))
    @EntityName.setter
    def EntityName(self, val): self.EntityName.set(val)
    @property
    def MinimumDepth(self): return Float(self._node.at("MinimumDepth"))
    @MinimumDepth.setter
    def MinimumDepth(self, val): self.MinimumDepth.set(val)
    @property
    def PeriodRandomness(self): return Float(self._node.at("PeriodRandomness"))
    @PeriodRandomness.setter
    def PeriodRandomness(self, val): self.PeriodRandomness.set(val)
    @property
    def SpawningPeriod(self): return Float(self._node.at("SpawningPeriod"))
    @SpawningPeriod.setter
    def SpawningPeriod(self, val): self.SpawningPeriod.set(val)
    @property
    def State(self): return String(self._node.at("State"))
    @State.setter
    def State(self, val): self.State.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




