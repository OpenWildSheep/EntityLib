
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class GameDodgeData(HelperObject):
    schema_name = "GameDodgeData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameDodgeData
        return GameDodgeData(entlib.load_node_file(sourcefile, entlib.get_schema(GameDodgeData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameDodgeData
        return GameDodgeData(entlib.make_node(GameDodgeData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Cooldown(self):  # type: ()->Float
        return Float(self._node.at("Cooldown"))
    @Cooldown.setter
    def Cooldown(self, val): self.Cooldown.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




