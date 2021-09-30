
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Object import *
from entgen.Position import *
from entgen.ReviveSide import *


class UnitTestComponent(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/UnitTestComponent"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(UnitTestComponent.schema_name))
    @property
    def Entity(self): return Object(self._node.at("Entity"))
    @property
    def EnumSet(self): return (lambda n: PrimitiveSet(ReviveSideEnum, n))(self._node.at("EnumSet"))
    @property
    def Position(self): return Position(self._node.at("Position"))
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




