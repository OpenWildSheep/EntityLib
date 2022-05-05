
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.ScaleConverter import *

from EntityLibPy import Node

class GrasperInteractionData(HelperObject):
    schema_name = "GrasperInteractionData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GrasperInteractionData
        return GrasperInteractionData(entlib.load_node_file(sourcefile, entlib.get_schema(GrasperInteractionData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GrasperInteractionData
        return GrasperInteractionData(entlib.make_node(GrasperInteractionData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def anticipationSpeedFactor(self):  # type: ()->Float
        return Float(self._node.at("anticipationSpeedFactor"))
    @anticipationSpeedFactor.setter
    def anticipationSpeedFactor(self, val): self.anticipationSpeedFactor.set(val)
    @property
    def deltaAngleMax(self):  # type: ()->Float
        return Float(self._node.at("deltaAngleMax"))
    @deltaAngleMax.setter
    def deltaAngleMax(self, val): self.deltaAngleMax.set(val)
    @property
    def distanceHysteris(self):  # type: ()->Float
        return Float(self._node.at("distanceHysteris"))
    @distanceHysteris.setter
    def distanceHysteris(self, val): self.distanceHysteris.set(val)
    @property
    def distanceMax(self):  # type: ()->Float
        return Float(self._node.at("distanceMax"))
    @distanceMax.setter
    def distanceMax(self, val): self.distanceMax.set(val)
    @property
    def interactableBoneName(self):  # type: ()->String
        return String(self._node.at("interactableBoneName"))
    @interactableBoneName.setter
    def interactableBoneName(self, val): self.interactableBoneName.set(val)
    @property
    def syncDeltaRotationDuration(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("syncDeltaRotationDuration"))
    @property
    def syncDeltaTranslationDuration(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("syncDeltaTranslationDuration"))
    pass




