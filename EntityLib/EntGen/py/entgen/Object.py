
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.Object_MaxActivationLevel import *
from entgen.String import *
from entgen.ActorStates import *
from entgen.Bool import *
from entgen.Color import *
from entgen.Object_Components import *

from EntityLibPy import Node

class Object(HelperObject):
    schema_name = "Object"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Object
        return Object(entlib.load_node_file(sourcefile, entlib.get_schema(Object.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Object
        return Object(entlib.make_node(Object.schema_name))
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
    def Components(self):  # type: ()->Object_Components
        return Object_Components(self._node.at("Components"))
    @property
    def MaxActivationLevel(self):  # type: ()->Object_MaxActivationLevel
        return Object_MaxActivationLevel(self._node.at("MaxActivationLevel"))
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
    def __removed__(self):  # type: ()->Bool
        return Bool(self._node.at("__removed__"))
    @__removed__.setter
    def __removed__(self, val): self.__removed__.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




