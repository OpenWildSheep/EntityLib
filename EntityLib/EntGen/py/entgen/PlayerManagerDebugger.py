
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class PlayerManagerDebugger(HelperObject):
    schema_name = "PlayerManagerDebugger"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PlayerManagerDebugger
        return PlayerManagerDebugger(entlib.load_node_file(sourcefile, entlib.get_schema(PlayerManagerDebugger.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PlayerManagerDebugger
        return PlayerManagerDebugger(entlib.make_node(PlayerManagerDebugger.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def SaveServerURL(self):  # type: ()->String
        return String(self._node.at("SaveServerURL"))
    @SaveServerURL.setter
    def SaveServerURL(self, val): self.SaveServerURL.set(val)
    @property
    def SelectionSpeed(self):  # type: ()->Float
        return Float(self._node.at("SelectionSpeed"))
    @SelectionSpeed.setter
    def SelectionSpeed(self, val): self.SelectionSpeed.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




