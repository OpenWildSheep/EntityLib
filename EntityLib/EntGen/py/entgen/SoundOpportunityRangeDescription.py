
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class SoundOpportunityRangeDescription(HelperObject):
    schema_name = "SoundOpportunityRangeDescription"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SoundOpportunityRangeDescription
        return SoundOpportunityRangeDescription(entlib.load_node_file(sourcefile, entlib.get_schema(SoundOpportunityRangeDescription.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SoundOpportunityRangeDescription
        return SoundOpportunityRangeDescription(entlib.make_node(SoundOpportunityRangeDescription.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ChunkSize(self):  # type: ()->Float
        return Float(self._node.at("ChunkSize"))
    @ChunkSize.setter
    def ChunkSize(self, val): self.ChunkSize.set(val)
    @property
    def EDITOR_SelectionProbabilityFactor(self):  # type: ()->Float
        return Float(self._node.at("EDITOR_SelectionProbabilityFactor"))
    @EDITOR_SelectionProbabilityFactor.setter
    def EDITOR_SelectionProbabilityFactor(self, val): self.EDITOR_SelectionProbabilityFactor.set(val)
    @property
    def MaxDistance(self):  # type: ()->Float
        return Float(self._node.at("MaxDistance"))
    @MaxDistance.setter
    def MaxDistance(self, val): self.MaxDistance.set(val)
    @property
    def PCloudPath(self):  # type: ()->String
        return String(self._node.at("PCloudPath"))
    @PCloudPath.setter
    def PCloudPath(self, val): self.PCloudPath.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




