
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Float import *

from EntityLibPy import Node

class CreatureDangerousness(HelperObject):
    schema_name = "CreatureDangerousness"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CreatureDangerousness
        return CreatureDangerousness(entlib.load_node_file(sourcefile, entlib.get_schema(CreatureDangerousness.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CreatureDangerousness
        return CreatureDangerousness(entlib.make_node(CreatureDangerousness.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def dangerousness(self):  # type: ()->Int
        return Int(self._node.at("dangerousness"))
    @dangerousness.setter
    def dangerousness(self, val): self.dangerousness.set(val)
    @property
    def multiplierWhenInjured(self):  # type: ()->Float
        return Float(self._node.at("multiplierWhenInjured"))
    @multiplierWhenInjured.setter
    def multiplierWhenInjured(self, val): self.multiplierWhenInjured.set(val)
    pass




