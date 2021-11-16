
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Manager import *

from EntityLibPy import Node

class AnimalManager(HelperObject):
    schema_name = "AnimalManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimalManager
        return AnimalManager(entlib.load_node_file(sourcefile, entlib.get_schema(AnimalManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimalManager
        return AnimalManager(entlib.make_node(AnimalManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def animalName(self):  # type: ()->String
        return String(self._node.at("animalName"))
    @animalName.setter
    def animalName(self, val): self.animalName.set(val)
    pass




