
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Entity import *

from EntityLibPy import Node

class SubScene(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/SubScene"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SubScene
        return SubScene(entlib.load_node_file(sourcefile, entlib.get_schema(SubScene.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SubScene
        return SubScene(entlib.make_node(SubScene.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Embedded(self):  # type: ()->ObjectSet[Entity]
        return (lambda n: ObjectSet(Entity, n))(self._node.at("Embedded"))
    @property
    def File(self):  # type: ()->String
        return String(self._node.at("File"))
    @File.setter
    def File(self, val): self.File.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def isEmbedded(self):  # type: ()->Bool
        return Bool(self._node.at("isEmbedded"))
    @isEmbedded.setter
    def isEmbedded(self, val): self.isEmbedded.set(val)
    pass




