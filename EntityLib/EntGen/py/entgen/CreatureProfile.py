
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.String import *
from entgen.CreatureProfile__CreatureProfileFact import *

from EntityLibPy import Node

class CreatureProfile(HelperObject):
    schema_name = "CreatureProfile"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CreatureProfile
        return CreatureProfile(entlib.load_node_file(sourcefile, entlib.get_schema(CreatureProfile.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CreatureProfile
        return CreatureProfile(entlib.make_node(CreatureProfile.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Facts(self):  # type: ()->Array[Array[CreatureProfile__CreatureProfileFact]]
        return (lambda n: Array((lambda n: Array(CreatureProfile__CreatureProfileFact, n)), n))(self._node.at("Facts"))
    @property
    def ValueMap(self):  # type: ()->Map[str, Float]
        return (lambda n: Map(str, Float, n))(self._node.at("ValueMap"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




