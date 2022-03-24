
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Float import *

from EntityLibPy import Node

class PerceiverGD(HelperObject):
    schema_name = "PerceiverGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PerceiverGD
        return PerceiverGD(entlib.load_node_file(sourcefile, entlib.get_schema(PerceiverGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PerceiverGD
        return PerceiverGD(entlib.make_node(PerceiverGD.schema_name))
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
    def m_coneAngle(self):  # type: ()->Float
        return Float(self._node.at("m_coneAngle"))
    @m_coneAngle.setter
    def m_coneAngle(self, val): self.m_coneAngle.set(val)
    @property
    def m_farSoundDistance(self):  # type: ()->Float
        return Float(self._node.at("m_farSoundDistance"))
    @m_farSoundDistance.setter
    def m_farSoundDistance(self, val): self.m_farSoundDistance.set(val)
    @property
    def m_longRangeDistance(self):  # type: ()->Float
        return Float(self._node.at("m_longRangeDistance"))
    @m_longRangeDistance.setter
    def m_longRangeDistance(self, val): self.m_longRangeDistance.set(val)
    @property
    def m_lowRangeDistance(self):  # type: ()->Float
        return Float(self._node.at("m_lowRangeDistance"))
    @m_lowRangeDistance.setter
    def m_lowRangeDistance(self, val): self.m_lowRangeDistance.set(val)
    @property
    def m_middleRangeDistance(self):  # type: ()->Float
        return Float(self._node.at("m_middleRangeDistance"))
    @m_middleRangeDistance.setter
    def m_middleRangeDistance(self, val): self.m_middleRangeDistance.set(val)
    @property
    def m_middleSoundDistance(self):  # type: ()->Float
        return Float(self._node.at("m_middleSoundDistance"))
    @m_middleSoundDistance.setter
    def m_middleSoundDistance(self, val): self.m_middleSoundDistance.set(val)
    @property
    def m_nearSoundDistance(self):  # type: ()->Float
        return Float(self._node.at("m_nearSoundDistance"))
    @m_nearSoundDistance.setter
    def m_nearSoundDistance(self, val): self.m_nearSoundDistance.set(val)
    @property
    def m_perceptionHeightMultiplier(self):  # type: ()->Float
        return Float(self._node.at("m_perceptionHeightMultiplier"))
    @m_perceptionHeightMultiplier.setter
    def m_perceptionHeightMultiplier(self, val): self.m_perceptionHeightMultiplier.set(val)
    @property
    def m_perceptionHeightMultiplierHeightMax(self):  # type: ()->Float
        return Float(self._node.at("m_perceptionHeightMultiplierHeightMax"))
    @m_perceptionHeightMultiplierHeightMax.setter
    def m_perceptionHeightMultiplierHeightMax(self, val): self.m_perceptionHeightMultiplierHeightMax.set(val)
    @property
    def m_rayCastCheck(self):  # type: ()->Bool
        return Bool(self._node.at("m_rayCastCheck"))
    @m_rayCastCheck.setter
    def m_rayCastCheck(self, val): self.m_rayCastCheck.set(val)
    pass




