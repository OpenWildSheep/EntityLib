
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class GroundTypeData(HelperObject):
    schema_name = "GroundTypeData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GroundTypeData
        return GroundTypeData(entlib.load_node_file(sourcefile, entlib.get_schema(GroundTypeData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GroundTypeData
        return GroundTypeData(entlib.make_node(GroundTypeData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def GrainRangeMax(self):  # type: ()->Float
        return Float(self._node.at("GrainRangeMax"))
    @GrainRangeMax.setter
    def GrainRangeMax(self, val): self.GrainRangeMax.set(val)
    @property
    def GrainRangeMin(self):  # type: ()->Float
        return Float(self._node.at("GrainRangeMin"))
    @GrainRangeMin.setter
    def GrainRangeMin(self, val): self.GrainRangeMin.set(val)
    @property
    def Name(self):  # type: ()->String
        return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def RegenRangeMax(self):  # type: ()->Float
        return Float(self._node.at("RegenRangeMax"))
    @RegenRangeMax.setter
    def RegenRangeMax(self, val): self.RegenRangeMax.set(val)
    @property
    def RegenRangeMin(self):  # type: ()->Float
        return Float(self._node.at("RegenRangeMin"))
    @RegenRangeMin.setter
    def RegenRangeMin(self, val): self.RegenRangeMin.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




