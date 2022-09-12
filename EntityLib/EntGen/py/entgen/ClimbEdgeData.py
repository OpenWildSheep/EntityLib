
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ClimbEdgeData_LedgeData import *
from entgen.Float import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class ClimbEdgeData(HelperObject):
    schema_name = "ClimbEdgeData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ClimbEdgeData
        return ClimbEdgeData(entlib.load_node_file(sourcefile, entlib.get_schema(ClimbEdgeData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ClimbEdgeData
        return ClimbEdgeData(entlib.make_node(ClimbEdgeData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def IsAllowed(self):  # type: ()->Bool
        return Bool(self._node.at("IsAllowed"))
    @IsAllowed.setter
    def IsAllowed(self, val): self.IsAllowed.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def edgeDetectionAnticipation(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("edgeDetectionAnticipation"))
    @property
    def edgeDetectionMaxFlotation(self):  # type: ()->Float
        return Float(self._node.at("edgeDetectionMaxFlotation"))
    @edgeDetectionMaxFlotation.setter
    def edgeDetectionMaxFlotation(self, val): self.edgeDetectionMaxFlotation.set(val)
    @property
    def ledgeData(self):  # type: ()->ClimbEdgeData_LedgeData
        return ClimbEdgeData_LedgeData(self._node.at("ledgeData"))
    @property
    def ledgeDataImmersed(self):  # type: ()->ClimbEdgeData_LedgeData
        return ClimbEdgeData_LedgeData(self._node.at("ledgeDataImmersed"))
    pass




