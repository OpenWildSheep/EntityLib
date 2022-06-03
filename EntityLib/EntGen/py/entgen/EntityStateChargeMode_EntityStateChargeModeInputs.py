
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.MoveCapacityData_OrientationSpeed import *

from EntityLibPy import Node

class EntityStateChargeMode_EntityStateChargeModeInputs(HelperObject):
    schema_name = "EntityStateChargeMode::EntityStateChargeModeInputs"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateChargeMode_EntityStateChargeModeInputs
        return EntityStateChargeMode_EntityStateChargeModeInputs(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateChargeMode_EntityStateChargeModeInputs.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateChargeMode_EntityStateChargeModeInputs
        return EntityStateChargeMode_EntityStateChargeModeInputs(entlib.make_node(EntityStateChargeMode_EntityStateChargeModeInputs.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AngularSpeed(self):  # type: ()->MoveCapacityData_OrientationSpeed
        return MoveCapacityData_OrientationSpeed(self._node.at("AngularSpeed"))
    @property
    def ForceMultiplier(self):  # type: ()->Float
        return Float(self._node.at("ForceMultiplier"))
    @ForceMultiplier.setter
    def ForceMultiplier(self, val): self.ForceMultiplier.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




