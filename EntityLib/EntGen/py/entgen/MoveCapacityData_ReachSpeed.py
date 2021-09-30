
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.LocomotionMode import *
from entgen.String import *
from entgen.Float import *


class MoveCapacityData_ReachSpeed(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/MoveCapacityData::ReachSpeed"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(MoveCapacityData_ReachSpeed.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def acceleration(self): return Float(self._node.at("acceleration"))
    @acceleration.setter
    def acceleration(self, val): self.acceleration.set(val)
    @property
    def deceleration(self): return Float(self._node.at("deceleration"))
    @deceleration.setter
    def deceleration(self, val): self.deceleration.set(val)
    @property
    def name(self): return LocomotionMode(self._node.at("name"))
    @name.setter
    def name(self, val): self.name.set(val)
    pass




