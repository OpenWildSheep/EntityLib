
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ConditionalRigidityAttribute_RigidityParameter import *


class ConditionalRigidityAttribute_Attributes(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ConditionalRigidityAttribute::Attributes"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(ConditionalRigidityAttribute_Attributes.schema_name))
    @property
    def DirectionAngular(self): return ConditionalRigidityAttribute_RigidityParameter(self._node.at("DirectionAngular"))
    @property
    def DirectionLinear(self): return ConditionalRigidityAttribute_RigidityParameter(self._node.at("DirectionLinear"))
    @property
    def OscillationAngular(self): return ConditionalRigidityAttribute_RigidityParameter(self._node.at("OscillationAngular"))
    @property
    def OscillationLinear(self): return ConditionalRigidityAttribute_RigidityParameter(self._node.at("OscillationLinear"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




