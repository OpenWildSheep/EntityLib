
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentInput import *
from entgen.resetCreatureRequest import *
from entgen.usePerception import *

from EntityLibPy import Node

class CreatureAIComponentInput(HelperObject):
    schema_name = "CreatureAIComponentInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CreatureAIComponentInput
        return CreatureAIComponentInput(entlib.load_node_file(sourcefile, entlib.get_schema(CreatureAIComponentInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CreatureAIComponentInput
        return CreatureAIComponentInput(entlib.make_node(CreatureAIComponentInput.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentInput
        return ComponentInput(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def resetCreatureRequest(self):  # type: ()->resetCreatureRequest
        return resetCreatureRequest(self._node.at("resetCreatureRequest"))
    @property
    def usePerception(self):  # type: ()->usePerception
        return usePerception(self._node.at("usePerception"))
    pass




