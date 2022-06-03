
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.MountableData import *

from EntityLibPy import Node

class ActorStateBeingOnMount(HelperObject):
    schema_name = "ActorStateBeingOnMount"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateBeingOnMount
        return ActorStateBeingOnMount(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateBeingOnMount.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateBeingOnMount
        return ActorStateBeingOnMount(entlib.make_node(ActorStateBeingOnMount.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def MountableData(self):  # type: ()->MountableData
        return MountableData(self._node.at("MountableData"))
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




