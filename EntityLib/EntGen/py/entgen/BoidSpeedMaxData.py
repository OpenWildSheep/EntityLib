
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class BoidSpeedMaxData(HelperObject):
    schema_name = "BoidSpeedMaxData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BoidSpeedMaxData
        return BoidSpeedMaxData(entlib.load_node_file(sourcefile, entlib.get_schema(BoidSpeedMaxData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BoidSpeedMaxData
        return BoidSpeedMaxData(entlib.make_node(BoidSpeedMaxData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Duration(self):  # type: ()->Float
        return Float(self._node.at("Duration"))
    @Duration.setter
    def Duration(self, val): self.Duration.set(val)
    @property
    def SpeedMax(self):  # type: ()->Float
        return Float(self._node.at("SpeedMax"))
    @SpeedMax.setter
    def SpeedMax(self, val): self.SpeedMax.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




