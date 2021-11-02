
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.LocomotionMode import *
from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class MoveCapacityData_ReachSpeed(HelperObject):
    schema_name = "MoveCapacityData::ReachSpeed"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MoveCapacityData_ReachSpeed
        return MoveCapacityData_ReachSpeed(entlib.load_node_file(sourcefile, entlib.get_schema(MoveCapacityData_ReachSpeed.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MoveCapacityData_ReachSpeed
        return MoveCapacityData_ReachSpeed(entlib.make_node(MoveCapacityData_ReachSpeed.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def acceleration(self):  # type: ()->Float
        return Float(self._node.at("acceleration"))
    @acceleration.setter
    def acceleration(self, val): self.acceleration.set(val)
    @property
    def deceleration(self):  # type: ()->Float
        return Float(self._node.at("deceleration"))
    @deceleration.setter
    def deceleration(self, val): self.deceleration.set(val)
    @property
    def name(self):  # type: ()->LocomotionMode
        return LocomotionMode(self._node.at("name"))
    @name.setter
    def name(self, val): self.name.set(val)
    pass




