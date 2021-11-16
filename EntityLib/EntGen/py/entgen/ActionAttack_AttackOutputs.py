
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.AnimTags import *
from entgen.Vector3 import *

from EntityLibPy import Node

class ActionAttack_AttackOutputs(HelperObject):
    schema_name = "ActionAttack::AttackOutputs"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionAttack_AttackOutputs
        return ActionAttack_AttackOutputs(entlib.load_node_file(sourcefile, entlib.get_schema(ActionAttack_AttackOutputs.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionAttack_AttackOutputs
        return ActionAttack_AttackOutputs(entlib.make_node(ActionAttack_AttackOutputs.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AnimTags(self):  # type: ()->AnimTags
        return AnimTags(self._node.at("AnimTags"))
    @property
    def Direction(self):  # type: ()->Vector3
        return Vector3(self._node.at("Direction"))
    @Direction.setter
    def Direction(self, val): self.Direction.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




