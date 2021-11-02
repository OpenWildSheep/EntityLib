
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *

from EntityLibPy import Node

class ActionShakeOffInputs(HelperObject):
    schema_name = "ActionShakeOffInputs"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionShakeOffInputs
        return ActionShakeOffInputs(entlib.load_node_file(sourcefile, entlib.get_schema(ActionShakeOffInputs.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionShakeOffInputs
        return ActionShakeOffInputs(entlib.make_node(ActionShakeOffInputs.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def TryEjectAllBiters(self):  # type: ()->Bool
        return Bool(self._node.at("TryEjectAllBiters"))
    @TryEjectAllBiters.setter
    def TryEjectAllBiters(self, val): self.TryEjectAllBiters.set(val)
    @property
    def UseRandomDirection(self):  # type: ()->Bool
        return Bool(self._node.at("UseRandomDirection"))
    @UseRandomDirection.setter
    def UseRandomDirection(self, val): self.UseRandomDirection.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




