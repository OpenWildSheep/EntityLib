
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentInput import *
from entgen.DamageGauge import *

from EntityLibPy import Node

class LifeComponentInput(HelperObject):
    schema_name = "LifeComponentInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->LifeComponentInput
        return LifeComponentInput(entlib.load_node_file(sourcefile, entlib.get_schema(LifeComponentInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->LifeComponentInput
        return LifeComponentInput(entlib.make_node(LifeComponentInput.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DamageGauge(self):  # type: ()->DamageGauge
        return DamageGauge(self._node.at("DamageGauge"))
    @property
    def Super(self):  # type: ()->ComponentInput
        return ComponentInput(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




