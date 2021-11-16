
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class GameFallData(HelperObject):
    schema_name = "GameFallData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameFallData
        return GameFallData(entlib.load_node_file(sourcefile, entlib.get_schema(GameFallData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameFallData
        return GameFallData(entlib.make_node(GameFallData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Acceleration(self):  # type: ()->Float
        return Float(self._node.at("Acceleration"))
    @Acceleration.setter
    def Acceleration(self, val): self.Acceleration.set(val)
    @property
    def ControlAcceleration(self):  # type: ()->Float
        return Float(self._node.at("ControlAcceleration"))
    @ControlAcceleration.setter
    def ControlAcceleration(self, val): self.ControlAcceleration.set(val)
    @property
    def Friction(self):  # type: ()->Float
        return Float(self._node.at("Friction"))
    @Friction.setter
    def Friction(self, val): self.Friction.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




