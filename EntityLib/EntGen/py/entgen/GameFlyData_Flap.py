
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class GameFlyData_Flap(HelperObject):
    schema_name = "GameFlyData::Flap"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameFlyData_Flap
        return GameFlyData_Flap(entlib.load_node_file(sourcefile, entlib.get_schema(GameFlyData_Flap.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameFlyData_Flap
        return GameFlyData_Flap(entlib.make_node(GameFlyData_Flap.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def RollMin(self):  # type: ()->Float
        return Float(self._node.at("RollMin"))
    @RollMin.setter
    def RollMin(self, val): self.RollMin.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




