
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Entity import *


class SubScene(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/SubScene"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(SubScene.schema_name))
    @property
    def Embedded(self): return (lambda n: ObjectSet(Entity, n))(self._node.at("Embedded"))
    @property
    def File(self): return String(self._node.at("File"))
    @File.setter
    def File(self, val): self.File.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def isEmbedded(self): return Bool(self._node.at("isEmbedded"))
    @isEmbedded.setter
    def isEmbedded(self, val): self.isEmbedded.set(val)
    pass




