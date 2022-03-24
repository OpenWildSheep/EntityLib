
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Object import *
from entgen.Position import *
from entgen.ReviveSide import *

from EntityLibPy import Node

class UnitTestComponent(HelperObject):
    schema_name = "UnitTestComponent"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->UnitTestComponent
        return UnitTestComponent(entlib.load_node_file(sourcefile, entlib.get_schema(UnitTestComponent.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->UnitTestComponent
        return UnitTestComponent(entlib.make_node(UnitTestComponent.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Entity(self):  # type: ()->Object
        return Object(self._node.at("Entity"))
    @property
    def EnumSet(self):  # type: ()->PrimitiveSet[ReviveSideEnum]
        return (lambda n: PrimitiveSet(ReviveSideEnum, n))(self._node.at("EnumSet"))
    @property
    def Position(self):  # type: ()->Position
        return Position(self._node.at("Position"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




