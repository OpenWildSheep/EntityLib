
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class ConditionalRigidityAttribute_RigidityParameter(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ConditionalRigidityAttribute::RigidityParameter"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ConditionalRigidityAttribute_RigidityParameter
        return ConditionalRigidityAttribute_RigidityParameter(entlib.load_node_file(sourcefile, entlib.get_schema(ConditionalRigidityAttribute_RigidityParameter.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ConditionalRigidityAttribute_RigidityParameter
        return ConditionalRigidityAttribute_RigidityParameter(entlib.make_node(ConditionalRigidityAttribute_RigidityParameter.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Rigidity(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("Rigidity"))
    @property
    def SpeedDown(self):  # type: ()->Float
        return Float(self._node.at("SpeedDown"))
    @SpeedDown.setter
    def SpeedDown(self, val): self.SpeedDown.set(val)
    @property
    def SpeedUp(self):  # type: ()->Float
        return Float(self._node.at("SpeedUp"))
    @SpeedUp.setter
    def SpeedUp(self, val): self.SpeedUp.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




