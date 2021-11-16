
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentInput import *

from EntityLibPy import Node

class MountIKControllerComponentInput(HelperObject):
    schema_name = "MountIKControllerComponentInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MountIKControllerComponentInput
        return MountIKControllerComponentInput(entlib.load_node_file(sourcefile, entlib.get_schema(MountIKControllerComponentInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MountIKControllerComponentInput
        return MountIKControllerComponentInput(entlib.make_node(MountIKControllerComponentInput.schema_name))
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




