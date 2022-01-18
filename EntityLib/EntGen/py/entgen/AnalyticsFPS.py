
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class AnalyticsFPS(HelperObject):
    schema_name = "AnalyticsFPS"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnalyticsFPS
        return AnalyticsFPS(entlib.load_node_file(sourcefile, entlib.get_schema(AnalyticsFPS.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnalyticsFPS
        return AnalyticsFPS(entlib.make_node(AnalyticsFPS.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def TeleportationDistance(self):  # type: ()->Float
        return Float(self._node.at("TeleportationDistance"))
    @TeleportationDistance.setter
    def TeleportationDistance(self, val): self.TeleportationDistance.set(val)
    @property
    def TeleportationInterval(self):  # type: ()->Float
        return Float(self._node.at("TeleportationInterval"))
    @TeleportationInterval.setter
    def TeleportationInterval(self, val): self.TeleportationInterval.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




