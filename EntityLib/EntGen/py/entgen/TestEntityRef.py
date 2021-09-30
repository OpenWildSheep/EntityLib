
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.EntityRef import *


class TestEntityRef(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/TestEntityRef"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(TestEntityRef.schema_name))
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def TestRef(self): return EntityRef(self._node.at("TestRef"))
    @TestRef.setter
    def TestRef(self, val): self.TestRef.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




