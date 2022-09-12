
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Color import *
from entgen.ComponentGD import *
from entgen.String import *

from EntityLibPy import Node

class ReflectedMaterialGroup(HelperObject):
    schema_name = "ReflectedMaterialGroup"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ReflectedMaterialGroup
        return ReflectedMaterialGroup(entlib.load_node_file(sourcefile, entlib.get_schema(ReflectedMaterialGroup.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ReflectedMaterialGroup
        return ReflectedMaterialGroup(entlib.make_node(ReflectedMaterialGroup.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Color(self):  # type: ()->Color
        return Color(self._node.at("Color"))
    @Color.setter
    def Color(self, val): self.Color.set(val)
    @property
    def Materials(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("Materials"))
    @Materials.setter
    def Materials(self, val): self.Materials.set(val)
    @property
    def OverrideGroups(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("OverrideGroups"))
    @OverrideGroups.setter
    def OverrideGroups(self, val): self.OverrideGroups.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def Tags(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("Tags"))
    @Tags.setter
    def Tags(self, val): self.Tags.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




