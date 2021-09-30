
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.RegenSwitchBehavior import *
from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.RegenData import *


class RegenSwitcherGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/RegenSwitcherGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(RegenSwitcherGD.schema_name))
    @property
    def ParentTransforms(self): return Bool(self._node.at("ParentTransforms"))
    @ParentTransforms.setter
    def ParentTransforms(self, val): self.ParentTransforms.set(val)
    @property
    def RegenData(self): return (lambda n: Array(RegenData, n))(self._node.at("RegenData"))
    @property
    def RegenSwitchBehavior(self): return RegenSwitchBehavior(self._node.at("RegenSwitchBehavior"))
    @RegenSwitchBehavior.setter
    def RegenSwitchBehavior(self, val): self.RegenSwitchBehavior.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




