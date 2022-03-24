
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class DamagesInstant(HelperObject):
    schema_name = "DamagesInstant"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->DamagesInstant
        return DamagesInstant(entlib.load_node_file(sourcefile, entlib.get_schema(DamagesInstant.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->DamagesInstant
        return DamagesInstant(entlib.make_node(DamagesInstant.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def damage(self):  # type: ()->Float
        return Float(self._node.at("damage"))
    @damage.setter
    def damage(self, val): self.damage.set(val)
    @property
    def impact(self):  # type: ()->Float
        return Float(self._node.at("impact"))
    @impact.setter
    def impact(self, val): self.impact.set(val)
    pass




