
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.SetOfObjectItem import *
from entgen.MapOfObjectItem_A import *
from entgen.String import *


class TestSetOfObject(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/TestSetOfObject"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(TestSetOfObject.schema_name))
    @property
    def MapOfObject(self): return (lambda n: Map(str, MapOfObjectItem_A, n))(self._node.at("MapOfObject"))
    @property
    def SetOfObject(self): return (lambda n: ObjectSet(SetOfObjectItem, n))(self._node.at("SetOfObject"))
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




