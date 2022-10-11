
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class CharacterControllerAnticipationData(HelperObject):
    schema_name = "CharacterControllerAnticipationData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CharacterControllerAnticipationData
        return CharacterControllerAnticipationData(entlib.load_node_file(sourcefile, entlib.get_schema(CharacterControllerAnticipationData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CharacterControllerAnticipationData
        return CharacterControllerAnticipationData(entlib.make_node(CharacterControllerAnticipationData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def anticipationDuration(self):  # type: ()->Float
        return Float(self._node.at("anticipationDuration"))
    @anticipationDuration.setter
    def anticipationDuration(self, val): self.anticipationDuration.set(val)
    @property
    def groundNormalPercentageEdgeTolerance(self):  # type: ()->Float
        return Float(self._node.at("groundNormalPercentageEdgeTolerance"))
    @groundNormalPercentageEdgeTolerance.setter
    def groundNormalPercentageEdgeTolerance(self, val): self.groundNormalPercentageEdgeTolerance.set(val)
    @property
    def rigidBodySpeedMaxFactor(self):  # type: ()->Float
        return Float(self._node.at("rigidBodySpeedMaxFactor"))
    @rigidBodySpeedMaxFactor.setter
    def rigidBodySpeedMaxFactor(self, val): self.rigidBodySpeedMaxFactor.set(val)
    @property
    def rigidBodySpeedMin(self):  # type: ()->Float
        return Float(self._node.at("rigidBodySpeedMin"))
    @rigidBodySpeedMin.setter
    def rigidBodySpeedMin(self, val): self.rigidBodySpeedMin.set(val)
    pass




