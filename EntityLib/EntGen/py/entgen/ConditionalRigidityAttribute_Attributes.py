
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ConditionalRigidityAttribute_RigidityParameter import *

from EntityLibPy import Node

class ConditionalRigidityAttribute_Attributes(HelperObject):
    schema_name = "ConditionalRigidityAttribute::Attributes"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ConditionalRigidityAttribute_Attributes
        return ConditionalRigidityAttribute_Attributes(entlib.load_node_file(sourcefile, entlib.get_schema(ConditionalRigidityAttribute_Attributes.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ConditionalRigidityAttribute_Attributes
        return ConditionalRigidityAttribute_Attributes(entlib.make_node(ConditionalRigidityAttribute_Attributes.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DirectionAngular(self):  # type: ()->ConditionalRigidityAttribute_RigidityParameter
        return ConditionalRigidityAttribute_RigidityParameter(self._node.at("DirectionAngular"))
    @property
    def DirectionLinear(self):  # type: ()->ConditionalRigidityAttribute_RigidityParameter
        return ConditionalRigidityAttribute_RigidityParameter(self._node.at("DirectionLinear"))
    @property
    def OscillationAngular(self):  # type: ()->ConditionalRigidityAttribute_RigidityParameter
        return ConditionalRigidityAttribute_RigidityParameter(self._node.at("OscillationAngular"))
    @property
    def OscillationLinear(self):  # type: ()->ConditionalRigidityAttribute_RigidityParameter
        return ConditionalRigidityAttribute_RigidityParameter(self._node.at("OscillationLinear"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




