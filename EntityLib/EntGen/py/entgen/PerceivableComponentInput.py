
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentInput import *
from entgen.isPerceivable import *
from entgen.isPerceivableForEnemies import *
from entgen.soundEmissionStrength import *

from EntityLibPy import Node

class PerceivableComponentInput(HelperObject):
    schema_name = "PerceivableComponentInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PerceivableComponentInput
        return PerceivableComponentInput(entlib.load_node_file(sourcefile, entlib.get_schema(PerceivableComponentInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PerceivableComponentInput
        return PerceivableComponentInput(entlib.make_node(PerceivableComponentInput.schema_name))
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
    def isPerceivable(self):  # type: ()->isPerceivable
        return isPerceivable(self._node.at("isPerceivable"))
    @property
    def isPerceivableForEnemies(self):  # type: ()->isPerceivableForEnemies
        return isPerceivableForEnemies(self._node.at("isPerceivableForEnemies"))
    @property
    def soundEmissionStrength(self):  # type: ()->soundEmissionStrength
        return soundEmissionStrength(self._node.at("soundEmissionStrength"))
    pass




