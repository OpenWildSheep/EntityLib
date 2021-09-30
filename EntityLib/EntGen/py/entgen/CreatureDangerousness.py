
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Float import *


class CreatureDangerousness(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CreatureDangerousness"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(CreatureDangerousness.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def dangerousness(self): return Int(self._node.at("dangerousness"))
    @dangerousness.setter
    def dangerousness(self, val): self.dangerousness.set(val)
    @property
    def multiplierWhenInjured(self): return Float(self._node.at("multiplierWhenInjured"))
    @multiplierWhenInjured.setter
    def multiplierWhenInjured(self, val): self.multiplierWhenInjured.set(val)
    pass




