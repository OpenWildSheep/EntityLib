
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.EntityRef import *

from EntityLibPy import Node

class TestEntityRef(HelperObject):
    schema_name = "TestEntityRef"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TestEntityRef
        return TestEntityRef(entlib.load_node_file(sourcefile, entlib.get_schema(TestEntityRef.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TestEntityRef
        return TestEntityRef(entlib.make_node(TestEntityRef.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def TestRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("TestRef"))
    @TestRef.setter
    def TestRef(self, val): self.TestRef.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




