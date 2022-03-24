
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.OwnershipModuleDebugWindow import *

from EntityLibPy import Node

class Game_OwnershipDebugger(HelperObject):
    schema_name = "Game::OwnershipDebugger"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Game_OwnershipDebugger
        return Game_OwnershipDebugger(entlib.load_node_file(sourcefile, entlib.get_schema(Game_OwnershipDebugger.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Game_OwnershipDebugger
        return Game_OwnershipDebugger(entlib.make_node(Game_OwnershipDebugger.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Display(self):  # type: ()->PrimArray[OwnershipModuleDebugWindow]
        return (lambda n: PrimArray(OwnershipModuleDebugWindow, n))(self._node.at("Display"))
    @Display.setter
    def Display(self, val): self.Display.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




