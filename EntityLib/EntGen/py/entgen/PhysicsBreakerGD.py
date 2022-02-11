
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class PhysicsBreakerGD(HelperObject):
    schema_name = "PhysicsBreakerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PhysicsBreakerGD
        return PhysicsBreakerGD(entlib.load_node_file(sourcefile, entlib.get_schema(PhysicsBreakerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PhysicsBreakerGD
        return PhysicsBreakerGD(entlib.make_node(PhysicsBreakerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BreakEverything(self):  # type: ()->Bool
        return Bool(self._node.at("BreakEverything"))
    @BreakEverything.setter
    def BreakEverything(self, val): self.BreakEverything.set(val)
    @property
    def ForceBySpeed(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("ForceBySpeed"))
    @property
    def SmoothedSpeedControlRate(self):  # type: ()->Float
        return Float(self._node.at("SmoothedSpeedControlRate"))
    @SmoothedSpeedControlRate.setter
    def SmoothedSpeedControlRate(self, val): self.SmoothedSpeedControlRate.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




