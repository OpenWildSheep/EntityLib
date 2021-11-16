
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class GameFlyData_Centrifugal(HelperObject):
    schema_name = "GameFlyData::Centrifugal"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameFlyData_Centrifugal
        return GameFlyData_Centrifugal(entlib.load_node_file(sourcefile, entlib.get_schema(GameFlyData_Centrifugal.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameFlyData_Centrifugal
        return GameFlyData_Centrifugal(entlib.make_node(GameFlyData_Centrifugal.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Acceleration(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("Acceleration"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




