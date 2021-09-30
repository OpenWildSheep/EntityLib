
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ConditionalRigidityAttribute_Attributes import *
from entgen.ConditionalRigidityAttribute_Conditions import *


class ConditionalRigidityAttribute(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ConditionalRigidityAttribute"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(ConditionalRigidityAttribute.schema_name))
    @property
    def Attributes(self): return ConditionalRigidityAttribute_Attributes(self._node.at("Attributes"))
    @property
    def Conditions(self): return ConditionalRigidityAttribute_Conditions(self._node.at("Conditions"))
    @property
    def Default(self): return Bool(self._node.at("Default"))
    @Default.setter
    def Default(self, val): self.Default.set(val)
    @property
    def Name(self): return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




