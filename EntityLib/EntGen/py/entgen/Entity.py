
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.MaxActivationLevel import *
from entgen.String import *
from entgen.ActorStates import *
from entgen.Color import *
from entgen.Components import *

from EntityLibPy import Node

class Entity(HelperObject):
    schema_name = "Entity"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Entity
        return Entity(entlib.load_node_file(sourcefile, entlib.get_schema(Entity.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Entity
        return Entity(entlib.make_node(Entity.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ActorStates(self):  # type: ()->ActorStates
        return ActorStates(self._node.at("ActorStates"))
    @property
    def Color(self):  # type: ()->Color
        return Color(self._node.at("Color"))
    @Color.setter
    def Color(self, val): self.Color.set(val)
    @property
    def Components(self):  # type: ()->Components
        return Components(self._node.at("Components"))
    @property
    def InstanceOf(self):  # type: ()->String
        return String(self._node.at("InstanceOf"))
    @InstanceOf.setter
    def InstanceOf(self, val): self.InstanceOf.set(val)
    @property
    def MaxActivationLevel(self):  # type: ()->MaxActivationLevel
        return MaxActivationLevel(self._node.at("MaxActivationLevel"))
    @MaxActivationLevel.setter
    def MaxActivationLevel(self, val): self.MaxActivationLevel.set(val)
    @property
    def Name(self):  # type: ()->String
        return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def Thumbnail(self):  # type: ()->String
        return String(self._node.at("Thumbnail"))
    @Thumbnail.setter
    def Thumbnail(self, val): self.Thumbnail.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




