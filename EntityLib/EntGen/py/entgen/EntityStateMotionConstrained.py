
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.EntityStateMotionConstrained_Inputs import *

from EntityLibPy import Node

class EntityStateMotionConstrained(HelperObject):
    schema_name = "EntityStateMotionConstrained"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateMotionConstrained
        return EntityStateMotionConstrained(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateMotionConstrained.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateMotionConstrained
        return EntityStateMotionConstrained(entlib.make_node(EntityStateMotionConstrained.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Inputs(self):  # type: ()->EntityStateMotionConstrained_Inputs
        return EntityStateMotionConstrained_Inputs(self._node.at("Inputs"))
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




