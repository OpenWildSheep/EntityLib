
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.ScaleConverter import *


class ConditionalRigidityAttribute_RigidityParameter(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ConditionalRigidityAttribute::RigidityParameter"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(ConditionalRigidityAttribute_RigidityParameter.schema_name))
    @property
    def Rigidity(self): return ScaleConverter(self._node.at("Rigidity"))
    @property
    def SpeedDown(self): return Float(self._node.at("SpeedDown"))
    @SpeedDown.setter
    def SpeedDown(self, val): self.SpeedDown.set(val)
    @property
    def SpeedUp(self): return Float(self._node.at("SpeedUp"))
    @SpeedUp.setter
    def SpeedUp(self, val): self.SpeedUp.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




