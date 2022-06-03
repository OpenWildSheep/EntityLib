
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.GameEffect import *

from EntityLibPy import Node

class RepulseEffect(HelperObject):
    schema_name = "RepulseEffect"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RepulseEffect
        return RepulseEffect(entlib.load_node_file(sourcefile, entlib.get_schema(RepulseEffect.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RepulseEffect
        return RepulseEffect(entlib.make_node(RepulseEffect.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ApplyOnTrees(self):  # type: ()->Bool
        return Bool(self._node.at("ApplyOnTrees"))
    @ApplyOnTrees.setter
    def ApplyOnTrees(self, val): self.ApplyOnTrees.set(val)
    @property
    def DistanceAttenuation(self):  # type: ()->Float
        return Float(self._node.at("DistanceAttenuation"))
    @DistanceAttenuation.setter
    def DistanceAttenuation(self, val): self.DistanceAttenuation.set(val)
    @property
    def Strength(self):  # type: ()->Float
        return Float(self._node.at("Strength"))
    @Strength.setter
    def Strength(self, val): self.Strength.set(val)
    @property
    def Super(self):  # type: ()->GameEffect
        return GameEffect(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




