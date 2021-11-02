
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *

from EntityLibPy import Node

class AIAggroInitAndDecValue(HelperObject):
    schema_name = "AIAggroInitAndDecValue"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AIAggroInitAndDecValue
        return AIAggroInitAndDecValue(entlib.load_node_file(sourcefile, entlib.get_schema(AIAggroInitAndDecValue.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AIAggroInitAndDecValue
        return AIAggroInitAndDecValue(entlib.make_node(AIAggroInitAndDecValue.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DecrementValue(self):  # type: ()->Int
        return Int(self._node.at("DecrementValue"))
    @DecrementValue.setter
    def DecrementValue(self, val): self.DecrementValue.set(val)
    @property
    def InitValue(self):  # type: ()->Int
        return Int(self._node.at("InitValue"))
    @InitValue.setter
    def InitValue(self, val): self.InitValue.set(val)
    @property
    def MaxValue(self):  # type: ()->Int
        return Int(self._node.at("MaxValue"))
    @MaxValue.setter
    def MaxValue(self, val): self.MaxValue.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




