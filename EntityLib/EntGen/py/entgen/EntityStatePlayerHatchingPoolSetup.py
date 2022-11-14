
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *

from EntityLibPy import Node

class EntityStatePlayerHatchingPoolSetup(HelperObject):
    schema_name = "EntityStatePlayerHatchingPoolSetup"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStatePlayerHatchingPoolSetup
        return EntityStatePlayerHatchingPoolSetup(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStatePlayerHatchingPoolSetup.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStatePlayerHatchingPoolSetup
        return EntityStatePlayerHatchingPoolSetup(entlib.make_node(EntityStatePlayerHatchingPoolSetup.schema_name))
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
    pass




