
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentInput import *

from EntityLibPy import Node

class VelocityObstacleComponentInput(HelperObject):
    schema_name = "VelocityObstacleComponentInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->VelocityObstacleComponentInput
        return VelocityObstacleComponentInput(entlib.load_node_file(sourcefile, entlib.get_schema(VelocityObstacleComponentInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->VelocityObstacleComponentInput
        return VelocityObstacleComponentInput(entlib.make_node(VelocityObstacleComponentInput.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentInput
        return ComponentInput(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




