
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.SpeedMode import *
from entgen.String import *
from entgen.ActorState import *
from entgen.Bool import *
from entgen.MountableData import *
from entgen.Vector3 import *

from EntityLibPy import Node

class ActionUnmount(HelperObject):
    schema_name = "ActionUnmount"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionUnmount
        return ActionUnmount(entlib.load_node_file(sourcefile, entlib.get_schema(ActionUnmount.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionUnmount
        return ActionUnmount(entlib.make_node(ActionUnmount.schema_name))
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
    @property
    def acrobaticDirection(self):  # type: ()->Vector3
        return Vector3(self._node.at("acrobaticDirection"))
    @acrobaticDirection.setter
    def acrobaticDirection(self, val): self.acrobaticDirection.set(val)
    @property
    def acrobaticUnmount(self):  # type: ()->Bool
        return Bool(self._node.at("acrobaticUnmount"))
    @acrobaticUnmount.setter
    def acrobaticUnmount(self, val): self.acrobaticUnmount.set(val)
    @property
    def speedMode(self):  # type: ()->SpeedMode
        return SpeedMode(self._node.at("speedMode"))
    @speedMode.setter
    def speedMode(self, val): self.speedMode.set(val)
    pass




