
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.Float import *
from entgen.SpeedMode import *

from EntityLibPy import Node

class MoveCapacityData_TurnJump(HelperObject):
    schema_name = "MoveCapacityData::TurnJump"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MoveCapacityData_TurnJump
        return MoveCapacityData_TurnJump(entlib.load_node_file(sourcefile, entlib.get_schema(MoveCapacityData_TurnJump.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MoveCapacityData_TurnJump
        return MoveCapacityData_TurnJump(entlib.make_node(MoveCapacityData_TurnJump.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def isAllowed(self):  # type: ()->Bool
        return Bool(self._node.at("isAllowed"))
    @isAllowed.setter
    def isAllowed(self, val): self.isAllowed.set(val)
    @property
    def jumpReleaseToApexRatio(self):  # type: ()->Float
        return Float(self._node.at("jumpReleaseToApexRatio"))
    @jumpReleaseToApexRatio.setter
    def jumpReleaseToApexRatio(self, val): self.jumpReleaseToApexRatio.set(val)
    @property
    def orientationYawRateFactorPerSpeed(self):  # type: ()->Map[SpeedModeEnum, Float]
        return (lambda n: Map(SpeedModeEnum, Float, n))(self._node.at("orientationYawRateFactorPerSpeed"))
    pass




