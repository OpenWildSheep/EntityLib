
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.SoundEmissionStrength import *
from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.String import *

from EntityLibPy import Node

class PerceivableGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PerceivableGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PerceivableGD
        return PerceivableGD(entlib.load_node_file(sourcefile, entlib.get_schema(PerceivableGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PerceivableGD
        return PerceivableGD(entlib.make_node(PerceivableGD.schema_name))
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
    def m_perceivedDistanceMultiplier(self):  # type: ()->Float
        return Float(self._node.at("m_perceivedDistanceMultiplier"))
    @m_perceivedDistanceMultiplier.setter
    def m_perceivedDistanceMultiplier(self, val): self.m_perceivedDistanceMultiplier.set(val)
    @property
    def m_soundCrouch(self):  # type: ()->SoundEmissionStrength
        return SoundEmissionStrength(self._node.at("m_soundCrouch"))
    @m_soundCrouch.setter
    def m_soundCrouch(self, val): self.m_soundCrouch.set(val)
    @property
    def m_soundImmobile(self):  # type: ()->SoundEmissionStrength
        return SoundEmissionStrength(self._node.at("m_soundImmobile"))
    @m_soundImmobile.setter
    def m_soundImmobile(self, val): self.m_soundImmobile.set(val)
    @property
    def m_soundRun(self):  # type: ()->SoundEmissionStrength
        return SoundEmissionStrength(self._node.at("m_soundRun"))
    @m_soundRun.setter
    def m_soundRun(self, val): self.m_soundRun.set(val)
    @property
    def m_soundWalk(self):  # type: ()->SoundEmissionStrength
        return SoundEmissionStrength(self._node.at("m_soundWalk"))
    @m_soundWalk.setter
    def m_soundWalk(self, val): self.m_soundWalk.set(val)
    @property
    def m_tags(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("m_tags"))
    @m_tags.setter
    def m_tags(self, val): self.m_tags.set(val)
    pass




