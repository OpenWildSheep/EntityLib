
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class SpawningParameter(HelperObject):
    schema_name = "SpawningParameter"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SpawningParameter
        return SpawningParameter(entlib.load_node_file(sourcefile, entlib.get_schema(SpawningParameter.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SpawningParameter
        return SpawningParameter(entlib.make_node(SpawningParameter.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EntityName(self):  # type: ()->String
        return String(self._node.at("EntityName"))
    @EntityName.setter
    def EntityName(self, val): self.EntityName.set(val)
    @property
    def MinimumDepth(self):  # type: ()->Float
        return Float(self._node.at("MinimumDepth"))
    @MinimumDepth.setter
    def MinimumDepth(self, val): self.MinimumDepth.set(val)
    @property
    def PeriodRandomness(self):  # type: ()->Float
        return Float(self._node.at("PeriodRandomness"))
    @PeriodRandomness.setter
    def PeriodRandomness(self, val): self.PeriodRandomness.set(val)
    @property
    def SpawningPeriod(self):  # type: ()->Float
        return Float(self._node.at("SpawningPeriod"))
    @SpawningPeriod.setter
    def SpawningPeriod(self, val): self.SpawningPeriod.set(val)
    @property
    def State(self):  # type: ()->String
        return String(self._node.at("State"))
    @State.setter
    def State(self, val): self.State.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




