
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.RegenSwitchBehavior import *
from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.RegenData import *

from EntityLibPy import Node

class RegenSwitcherGD(HelperObject):
    schema_name = "RegenSwitcherGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RegenSwitcherGD
        return RegenSwitcherGD(entlib.load_node_file(sourcefile, entlib.get_schema(RegenSwitcherGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RegenSwitcherGD
        return RegenSwitcherGD(entlib.make_node(RegenSwitcherGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ParentTransforms(self):  # type: ()->Bool
        return Bool(self._node.at("ParentTransforms"))
    @ParentTransforms.setter
    def ParentTransforms(self, val): self.ParentTransforms.set(val)
    @property
    def RegenData(self):  # type: ()->Array[RegenData]
        return (lambda n: Array(RegenData, n))(self._node.at("RegenData"))
    @property
    def RegenSwitchBehavior(self):  # type: ()->RegenSwitchBehavior
        return RegenSwitchBehavior(self._node.at("RegenSwitchBehavior"))
    @RegenSwitchBehavior.setter
    def RegenSwitchBehavior(self, val): self.RegenSwitchBehavior.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




