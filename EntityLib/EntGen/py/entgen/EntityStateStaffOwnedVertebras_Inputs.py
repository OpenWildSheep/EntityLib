
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *

from EntityLibPy import Node

class EntityStateStaffOwnedVertebras_Inputs(HelperObject):
    schema_name = "EntityStateStaffOwnedVertebras::Inputs"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateStaffOwnedVertebras_Inputs
        return EntityStateStaffOwnedVertebras_Inputs(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateStaffOwnedVertebras_Inputs.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateStaffOwnedVertebras_Inputs
        return EntityStateStaffOwnedVertebras_Inputs(entlib.make_node(EntityStateStaffOwnedVertebras_Inputs.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def ownedVertebrasNumber(self):  # type: ()->Int
        return Int(self._node.at("ownedVertebrasNumber"))
    @ownedVertebrasNumber.setter
    def ownedVertebrasNumber(self, val): self.ownedVertebrasNumber.set(val)
    pass




