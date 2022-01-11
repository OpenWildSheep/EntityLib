
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.ResponsiblePointer_ActorState_ import *

from EntityLibPy import Node

class StrongAttackGD(HelperObject):
    schema_name = "StrongAttackGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->StrongAttackGD
        return StrongAttackGD(entlib.load_node_file(sourcefile, entlib.get_schema(StrongAttackGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->StrongAttackGD
        return StrongAttackGD(entlib.make_node(StrongAttackGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def strongAttackState(self):  # type: ()->ResponsiblePointer_ActorState_
        return ResponsiblePointer_ActorState_(self._node.at("strongAttackState"))
    pass




