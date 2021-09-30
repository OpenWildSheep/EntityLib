
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.PrimitiveData import *


class LDPrimitive(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/LDPrimitive"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(LDPrimitive.schema_name))
    @property
    def NonDisuptive(self): return Bool(self._node.at("NonDisuptive"))
    @NonDisuptive.setter
    def NonDisuptive(self, val): self.NonDisuptive.set(val)
    @property
    def PrimitiveData(self): return PrimitiveData(self._node.at("PrimitiveData"))
    @property
    def PrimitiveType(self): return String(self._node.at("PrimitiveType"))
    @PrimitiveType.setter
    def PrimitiveType(self, val): self.PrimitiveType.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




