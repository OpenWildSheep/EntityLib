
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.PrimitiveData import *

from EntityLibPy import Node

class LDPrimitive(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/LDPrimitive"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->LDPrimitive
        return LDPrimitive(entlib.load_node_file(sourcefile, entlib.get_schema(LDPrimitive.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->LDPrimitive
        return LDPrimitive(entlib.make_node(LDPrimitive.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def NonDisuptive(self):  # type: ()->Bool
        return Bool(self._node.at("NonDisuptive"))
    @NonDisuptive.setter
    def NonDisuptive(self, val): self.NonDisuptive.set(val)
    @property
    def PrimitiveData(self):  # type: ()->PrimitiveData
        return PrimitiveData(self._node.at("PrimitiveData"))
    @property
    def PrimitiveType(self):  # type: ()->String
        return String(self._node.at("PrimitiveType"))
    @PrimitiveType.setter
    def PrimitiveType(self, val): self.PrimitiveType.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




