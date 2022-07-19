
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.SoundOpportunityRangeDescription import *

from EntityLibPy import Node

class SoundOpportunityComponentGD(HelperObject):
    schema_name = "SoundOpportunityComponentGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SoundOpportunityComponentGD
        return SoundOpportunityComponentGD(entlib.load_node_file(sourcefile, entlib.get_schema(SoundOpportunityComponentGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SoundOpportunityComponentGD
        return SoundOpportunityComponentGD(entlib.make_node(SoundOpportunityComponentGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EDITOR_FilterTag(self):  # type: ()->String
        return String(self._node.at("EDITOR_FilterTag"))
    @EDITOR_FilterTag.setter
    def EDITOR_FilterTag(self, val): self.EDITOR_FilterTag.set(val)
    @property
    def RangeDescriptions(self):  # type: ()->Array[SoundOpportunityRangeDescription]
        return (lambda n: Array(SoundOpportunityRangeDescription, n))(self._node.at("RangeDescriptions"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




