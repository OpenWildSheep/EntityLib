
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *

from EntityLibPy import Node

class TargetCollision(HelperObject):
    schema_name = "TargetCollision"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TargetCollision
        return TargetCollision(entlib.load_node_file(sourcefile, entlib.get_schema(TargetCollision.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TargetCollision
        return TargetCollision(entlib.make_node(TargetCollision.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def count(self):  # type: ()->Int
        return Int(self._node.at("count"))
    @count.setter
    def count(self, val): self.count.set(val)
    pass




