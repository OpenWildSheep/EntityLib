
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.ShakeEffect import *

from EntityLibPy import Node

class BeamShakeEffect(HelperObject):
    schema_name = "BeamShakeEffect"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BeamShakeEffect
        return BeamShakeEffect(entlib.load_node_file(sourcefile, entlib.get_schema(BeamShakeEffect.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BeamShakeEffect
        return BeamShakeEffect(entlib.make_node(BeamShakeEffect.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Strength(self):  # type: ()->Float
        return Float(self._node.at("Strength"))
    @Strength.setter
    def Strength(self, val): self.Strength.set(val)
    @property
    def Super(self):  # type: ()->ShakeEffect
        return ShakeEffect(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




