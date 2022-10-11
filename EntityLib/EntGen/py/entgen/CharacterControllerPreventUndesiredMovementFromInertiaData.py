
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class CharacterControllerPreventUndesiredMovementFromInertiaData(HelperObject):
    schema_name = "CharacterControllerPreventUndesiredMovementFromInertiaData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CharacterControllerPreventUndesiredMovementFromInertiaData
        return CharacterControllerPreventUndesiredMovementFromInertiaData(entlib.load_node_file(sourcefile, entlib.get_schema(CharacterControllerPreventUndesiredMovementFromInertiaData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CharacterControllerPreventUndesiredMovementFromInertiaData
        return CharacterControllerPreventUndesiredMovementFromInertiaData(entlib.make_node(CharacterControllerPreventUndesiredMovementFromInertiaData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def brakeAnalogicalSpeed(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("brakeAnalogicalSpeed"))
    @property
    def brakeAnimationSpeed(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("brakeAnimationSpeed"))
    @property
    def retimingInertia(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("retimingInertia"))
    @property
    def retimingPlayRatio(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("retimingPlayRatio"))
    @property
    def retimingPosition(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("retimingPosition"))
    @property
    def slopeAngleMaxInDegree(self):  # type: ()->Float
        return Float(self._node.at("slopeAngleMaxInDegree"))
    @slopeAngleMaxInDegree.setter
    def slopeAngleMaxInDegree(self, val): self.slopeAngleMaxInDegree.set(val)
    pass




