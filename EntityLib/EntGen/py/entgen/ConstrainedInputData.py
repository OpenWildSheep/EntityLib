
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class ConstrainedInputData(HelperObject):
    schema_name = "ConstrainedInputData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ConstrainedInputData
        return ConstrainedInputData(entlib.load_node_file(sourcefile, entlib.get_schema(ConstrainedInputData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ConstrainedInputData
        return ConstrainedInputData(entlib.make_node(ConstrainedInputData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ConstrainedDirectionCoeff(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("ConstrainedDirectionCoeff"))
    @property
    def DiagonalSpeedFactor(self):  # type: ()->Float
        return Float(self._node.at("DiagonalSpeedFactor"))
    @DiagonalSpeedFactor.setter
    def DiagonalSpeedFactor(self, val): self.DiagonalSpeedFactor.set(val)
    @property
    def DirectionHysteresisAngle(self):  # type: ()->Float
        return Float(self._node.at("DirectionHysteresisAngle"))
    @DirectionHysteresisAngle.setter
    def DirectionHysteresisAngle(self, val): self.DirectionHysteresisAngle.set(val)
    @property
    def LateralSpeedFactor(self):  # type: ()->Float
        return Float(self._node.at("LateralSpeedFactor"))
    @LateralSpeedFactor.setter
    def LateralSpeedFactor(self, val): self.LateralSpeedFactor.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




