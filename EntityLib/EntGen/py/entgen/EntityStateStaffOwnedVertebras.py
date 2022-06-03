
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorState import *
from entgen.EntityStateStaffOwnedVertebras_Inputs import *

from EntityLibPy import Node

class EntityStateStaffOwnedVertebras(HelperObject):
    schema_name = "EntityStateStaffOwnedVertebras"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateStaffOwnedVertebras
        return EntityStateStaffOwnedVertebras(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateStaffOwnedVertebras.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateStaffOwnedVertebras
        return EntityStateStaffOwnedVertebras(entlib.make_node(EntityStateStaffOwnedVertebras.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Inputs(self):  # type: ()->EntityStateStaffOwnedVertebras_Inputs
        return EntityStateStaffOwnedVertebras_Inputs(self._node.at("Inputs"))
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




