
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ConditionalRigidityAttribute_Attributes import *
from entgen.ConditionalRigidityAttribute_Conditions import *

from EntityLibPy import Node

class ConditionalRigidityAttribute(HelperObject):
    schema_name = "ConditionalRigidityAttribute"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ConditionalRigidityAttribute
        return ConditionalRigidityAttribute(entlib.load_node_file(sourcefile, entlib.get_schema(ConditionalRigidityAttribute.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ConditionalRigidityAttribute
        return ConditionalRigidityAttribute(entlib.make_node(ConditionalRigidityAttribute.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Attributes(self):  # type: ()->ConditionalRigidityAttribute_Attributes
        return ConditionalRigidityAttribute_Attributes(self._node.at("Attributes"))
    @property
    def Conditions(self):  # type: ()->ConditionalRigidityAttribute_Conditions
        return ConditionalRigidityAttribute_Conditions(self._node.at("Conditions"))
    @property
    def Default(self):  # type: ()->Bool
        return Bool(self._node.at("Default"))
    @Default.setter
    def Default(self, val): self.Default.set(val)
    @property
    def Name(self):  # type: ()->String
        return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




