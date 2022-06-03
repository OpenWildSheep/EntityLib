
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.String import *
from entgen.String import *

from EntityLibPy import Node

class PhysicsMaterial(HelperObject):
    schema_name = "PhysicsMaterial"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PhysicsMaterial
        return PhysicsMaterial(entlib.load_node_file(sourcefile, entlib.get_schema(PhysicsMaterial.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PhysicsMaterial
        return PhysicsMaterial(entlib.make_node(PhysicsMaterial.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ClimbablePerSize(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("ClimbablePerSize"))
    @ClimbablePerSize.setter
    def ClimbablePerSize(self, val): self.ClimbablePerSize.set(val)
    @property
    def MaterialId(self):  # type: ()->Int
        return Int(self._node.at("MaterialId"))
    @MaterialId.setter
    def MaterialId(self, val): self.MaterialId.set(val)
    @property
    def Name(self):  # type: ()->String
        return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def Tags(self):  # type: ()->PrimitiveSet[str]
        return (lambda n: PrimitiveSet(str, n))(self._node.at("Tags"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




