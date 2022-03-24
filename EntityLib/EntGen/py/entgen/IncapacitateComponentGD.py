
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.ScaleConverter import *
from entgen.HitStyle import *

from EntityLibPy import Node

class IncapacitateComponentGD(HelperObject):
    schema_name = "IncapacitateComponentGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->IncapacitateComponentGD
        return IncapacitateComponentGD(entlib.load_node_file(sourcefile, entlib.get_schema(IncapacitateComponentGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->IncapacitateComponentGD
        return IncapacitateComponentGD(entlib.make_node(IncapacitateComponentGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def HitStyleTriggers(self):  # type: ()->PrimArray[HitStyle]
        return (lambda n: PrimArray(HitStyle, n))(self._node.at("HitStyleTriggers"))
    @HitStyleTriggers.setter
    def HitStyleTriggers(self, val): self.HitStyleTriggers.set(val)
    @property
    def ImpactMultiplierCurve(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("ImpactMultiplierCurve"))
    @property
    def IncapacitateTimeCurve(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("IncapacitateTimeCurve"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




