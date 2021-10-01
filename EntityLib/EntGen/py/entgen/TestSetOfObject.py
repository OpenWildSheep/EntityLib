
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.SetOfObjectItem import *
from entgen.MapOfObjectItem_A import *
from entgen.String import *

from EntityLibPy import Node

class TestSetOfObject(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/TestSetOfObject"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TestSetOfObject
        return TestSetOfObject(entlib.load_node_file(sourcefile, entlib.get_schema(TestSetOfObject.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TestSetOfObject
        return TestSetOfObject(entlib.make_node(TestSetOfObject.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def MapOfObject(self):  # type: ()->Map[str, MapOfObjectItem_A]
        return (lambda n: Map(str, MapOfObjectItem_A, n))(self._node.at("MapOfObject"))
    @property
    def SetOfObject(self):  # type: ()->ObjectSet[SetOfObjectItem]
        return (lambda n: ObjectSet(SetOfObjectItem, n))(self._node.at("SetOfObject"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




