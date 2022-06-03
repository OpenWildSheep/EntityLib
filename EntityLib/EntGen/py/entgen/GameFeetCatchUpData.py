
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ScaleConverter import *
from entgen.Bool import *
from entgen.Size import *

from EntityLibPy import Node

class GameFeetCatchUpData(HelperObject):
    schema_name = "GameFeetCatchUpData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameFeetCatchUpData
        return GameFeetCatchUpData(entlib.load_node_file(sourcefile, entlib.get_schema(GameFeetCatchUpData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameFeetCatchUpData
        return GameFeetCatchUpData(entlib.make_node(GameFeetCatchUpData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def aerialRate(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("aerialRate"))
    @property
    def groundRate(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("groundRate"))
    @property
    def useHeightmapPerSize(self):  # type: ()->Map[SizeEnum, Bool]
        return (lambda n: Map(SizeEnum, Bool, n))(self._node.at("useHeightmapPerSize"))
    pass




