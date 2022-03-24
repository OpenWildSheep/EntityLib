
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Entity import *

from EntityLibPy import Node

class Scene(HelperObject):
    schema_name = "Scene"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Scene
        return Scene(entlib.load_node_file(sourcefile, entlib.get_schema(Scene.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Scene
        return Scene(entlib.make_node(Scene.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Objects(self):  # type: ()->ObjectSet[Entity]
        return (lambda n: ObjectSet(Entity, n))(self._node.at("Objects"))
    @property
    def Version(self):  # type: ()->Int
        return Int(self._node.at("Version"))
    @Version.setter
    def Version(self, val): self.Version.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




