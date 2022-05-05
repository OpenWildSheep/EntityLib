
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentInput import *
from entgen.jumpPower import *

from EntityLibPy import Node

class ChargedJumpComponentInput(HelperObject):
    schema_name = "ChargedJumpComponentInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ChargedJumpComponentInput
        return ChargedJumpComponentInput(entlib.load_node_file(sourcefile, entlib.get_schema(ChargedJumpComponentInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ChargedJumpComponentInput
        return ChargedJumpComponentInput(entlib.make_node(ChargedJumpComponentInput.schema_name))
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
    @property
    def jumpPower(self):  # type: ()->jumpPower
        return jumpPower(self._node.at("jumpPower"))
    pass




