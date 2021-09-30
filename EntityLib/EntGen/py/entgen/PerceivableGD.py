
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.SoundEmissionStrength import *
from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.String import *


class PerceivableGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PerceivableGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(PerceivableGD.schema_name))
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def m_perceivedDistanceMultiplier(self): return Float(self._node.at("m_perceivedDistanceMultiplier"))
    @m_perceivedDistanceMultiplier.setter
    def m_perceivedDistanceMultiplier(self, val): self.m_perceivedDistanceMultiplier.set(val)
    @property
    def m_soundCrouch(self): return SoundEmissionStrength(self._node.at("m_soundCrouch"))
    @m_soundCrouch.setter
    def m_soundCrouch(self, val): self.m_soundCrouch.set(val)
    @property
    def m_soundImmobile(self): return SoundEmissionStrength(self._node.at("m_soundImmobile"))
    @m_soundImmobile.setter
    def m_soundImmobile(self, val): self.m_soundImmobile.set(val)
    @property
    def m_soundRun(self): return SoundEmissionStrength(self._node.at("m_soundRun"))
    @m_soundRun.setter
    def m_soundRun(self, val): self.m_soundRun.set(val)
    @property
    def m_soundWalk(self): return SoundEmissionStrength(self._node.at("m_soundWalk"))
    @m_soundWalk.setter
    def m_soundWalk(self, val): self.m_soundWalk.set(val)
    @property
    def m_tags(self): return (lambda n: PrimArray(String, n))(self._node.at("m_tags"))
    @m_tags.setter
    def m_tags(self, val): self.m_tags.set(val)
    pass




