
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.GameTimeInMs import *

from EntityLibPy import Node

class CreatureProfile__CreatureProfileFact(HelperObject):
    schema_name = "CreatureProfile::_CreatureProfileFact"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CreatureProfile__CreatureProfileFact
        return CreatureProfile__CreatureProfileFact(entlib.load_node_file(sourcefile, entlib.get_schema(CreatureProfile__CreatureProfileFact.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CreatureProfile__CreatureProfileFact
        return CreatureProfile__CreatureProfileFact(entlib.make_node(CreatureProfile__CreatureProfileFact.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def TimeOfCreation(self):  # type: ()->GameTimeInMs
        return GameTimeInMs(self._node.at("TimeOfCreation"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




