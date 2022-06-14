
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.ResponsiblePointer_ActorState_ import *

from EntityLibPy import Node

class AerialAttackData(HelperObject):
    schema_name = "AerialAttackData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AerialAttackData
        return AerialAttackData(entlib.load_node_file(sourcefile, entlib.get_schema(AerialAttackData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AerialAttackData
        return AerialAttackData(entlib.make_node(AerialAttackData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AerialAttackState(self):  # type: ()->ResponsiblePointer_ActorState_
        return ResponsiblePointer_ActorState_(self._node.at("AerialAttackState"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def attackOrientationRate(self):  # type: ()->Float
        return Float(self._node.at("attackOrientationRate"))
    @attackOrientationRate.setter
    def attackOrientationRate(self, val): self.attackOrientationRate.set(val)
    pass




