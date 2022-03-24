
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.ChargedJumpAnimation import *

from EntityLibPy import Node

class ChargedJumpGD(HelperObject):
    schema_name = "ChargedJumpGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ChargedJumpGD
        return ChargedJumpGD(entlib.load_node_file(sourcefile, entlib.get_schema(ChargedJumpGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ChargedJumpGD
        return ChargedJumpGD(entlib.make_node(ChargedJumpGD.schema_name))
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
    def chargedJumpAnimations(self):  # type: ()->Array[ChargedJumpAnimation]
        return (lambda n: Array(ChargedJumpAnimation, n))(self._node.at("chargedJumpAnimations"))
    @property
    def chargingDecelerationFactor(self):  # type: ()->Float
        return Float(self._node.at("chargingDecelerationFactor"))
    @chargingDecelerationFactor.setter
    def chargingDecelerationFactor(self, val): self.chargingDecelerationFactor.set(val)
    pass




