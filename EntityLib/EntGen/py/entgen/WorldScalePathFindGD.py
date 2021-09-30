
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.NavmeshGenerationParameters import *


class WorldScalePathFindGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/WorldScalePathFindGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(WorldScalePathFindGD.schema_name))
    @property
    def FilePath(self): return String(self._node.at("FilePath"))
    @FilePath.setter
    def FilePath(self, val): self.FilePath.set(val)
    @property
    def GenerationParameters(self): return (lambda n: Array(NavmeshGenerationParameters, n))(self._node.at("GenerationParameters"))
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




