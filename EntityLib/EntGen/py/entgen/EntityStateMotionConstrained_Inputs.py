
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *

from EntityLibPy import Node

class EntityStateMotionConstrained_Inputs(HelperObject):
    schema_name = "EntityStateMotionConstrained::Inputs"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateMotionConstrained_Inputs
        return EntityStateMotionConstrained_Inputs(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateMotionConstrained_Inputs.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateMotionConstrained_Inputs
        return EntityStateMotionConstrained_Inputs(entlib.make_node(EntityStateMotionConstrained_Inputs.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ConstrainedLanding(self):  # type: ()->Bool
        return Bool(self._node.at("ConstrainedLanding"))
    @ConstrainedLanding.setter
    def ConstrainedLanding(self, val): self.ConstrainedLanding.set(val)
    @property
    def InputCorrection(self):  # type: ()->Bool
        return Bool(self._node.at("InputCorrection"))
    @InputCorrection.setter
    def InputCorrection(self, val): self.InputCorrection.set(val)
    @property
    def StayOnCurve(self):  # type: ()->Bool
        return Bool(self._node.at("StayOnCurve"))
    @StayOnCurve.setter
    def StayOnCurve(self, val): self.StayOnCurve.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




