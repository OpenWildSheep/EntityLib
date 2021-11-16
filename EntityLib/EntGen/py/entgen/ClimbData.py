
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class ClimbData(HelperObject):
    schema_name = "ClimbData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ClimbData
        return ClimbData(entlib.load_node_file(sourcefile, entlib.get_schema(ClimbData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ClimbData
        return ClimbData(entlib.make_node(ClimbData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def climbTreeSelectionAngle(self):  # type: ()->Float
        return Float(self._node.at("climbTreeSelectionAngle"))
    @climbTreeSelectionAngle.setter
    def climbTreeSelectionAngle(self, val): self.climbTreeSelectionAngle.set(val)
    @property
    def climbTreeSelectionBlindAngle(self):  # type: ()->Float
        return Float(self._node.at("climbTreeSelectionBlindAngle"))
    @climbTreeSelectionBlindAngle.setter
    def climbTreeSelectionBlindAngle(self, val): self.climbTreeSelectionBlindAngle.set(val)
    @property
    def climbTreeSelectionDistance(self):  # type: ()->Float
        return Float(self._node.at("climbTreeSelectionDistance"))
    @climbTreeSelectionDistance.setter
    def climbTreeSelectionDistance(self, val): self.climbTreeSelectionDistance.set(val)
    @property
    def climbTreeSelectionOffset(self):  # type: ()->Float
        return Float(self._node.at("climbTreeSelectionOffset"))
    @climbTreeSelectionOffset.setter
    def climbTreeSelectionOffset(self, val): self.climbTreeSelectionOffset.set(val)
    pass




