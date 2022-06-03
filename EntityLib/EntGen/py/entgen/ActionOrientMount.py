
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.Vector3 import *

from EntityLibPy import Node

class ActionOrientMount(HelperObject):
    schema_name = "ActionOrientMount"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionOrientMount
        return ActionOrientMount(entlib.load_node_file(sourcefile, entlib.get_schema(ActionOrientMount.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionOrientMount
        return ActionOrientMount(entlib.make_node(ActionOrientMount.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def m_direction(self):  # type: ()->Vector3
        return Vector3(self._node.at("m_direction"))
    @m_direction.setter
    def m_direction(self, val): self.m_direction.set(val)
    pass




