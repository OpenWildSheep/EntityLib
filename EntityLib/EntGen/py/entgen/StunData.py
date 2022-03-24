
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Float import *

from EntityLibPy import Node

class StunData(HelperObject):
    schema_name = "StunData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->StunData
        return StunData(entlib.load_node_file(sourcefile, entlib.get_schema(StunData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->StunData
        return StunData(entlib.make_node(StunData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def damageHitBig(self):  # type: ()->Int
        return Int(self._node.at("damageHitBig"))
    @damageHitBig.setter
    def damageHitBig(self, val): self.damageHitBig.set(val)
    @property
    def damageHitBite(self):  # type: ()->Int
        return Int(self._node.at("damageHitBite"))
    @damageHitBite.setter
    def damageHitBite(self, val): self.damageHitBite.set(val)
    @property
    def damageHitEject(self):  # type: ()->Int
        return Int(self._node.at("damageHitEject"))
    @damageHitEject.setter
    def damageHitEject(self, val): self.damageHitEject.set(val)
    @property
    def damageHitEjectFar(self):  # type: ()->Int
        return Int(self._node.at("damageHitEjectFar"))
    @damageHitEjectFar.setter
    def damageHitEjectFar(self, val): self.damageHitEjectFar.set(val)
    @property
    def damageHitLight(self):  # type: ()->Int
        return Int(self._node.at("damageHitLight"))
    @damageHitLight.setter
    def damageHitLight(self, val): self.damageHitLight.set(val)
    @property
    def damageHitMedium(self):  # type: ()->Int
        return Int(self._node.at("damageHitMedium"))
    @damageHitMedium.setter
    def damageHitMedium(self, val): self.damageHitMedium.set(val)
    @property
    def malus(self):  # type: ()->Int
        return Int(self._node.at("malus"))
    @malus.setter
    def malus(self, val): self.malus.set(val)
    @property
    def orientHitBig(self):  # type: ()->Float
        return Float(self._node.at("orientHitBig"))
    @orientHitBig.setter
    def orientHitBig(self, val): self.orientHitBig.set(val)
    @property
    def orientHitEject(self):  # type: ()->Float
        return Float(self._node.at("orientHitEject"))
    @orientHitEject.setter
    def orientHitEject(self, val): self.orientHitEject.set(val)
    @property
    def orientHitEjectFar(self):  # type: ()->Float
        return Float(self._node.at("orientHitEjectFar"))
    @orientHitEjectFar.setter
    def orientHitEjectFar(self, val): self.orientHitEjectFar.set(val)
    @property
    def orientHitLight(self):  # type: ()->Float
        return Float(self._node.at("orientHitLight"))
    @orientHitLight.setter
    def orientHitLight(self, val): self.orientHitLight.set(val)
    @property
    def orientHitMedium(self):  # type: ()->Float
        return Float(self._node.at("orientHitMedium"))
    @orientHitMedium.setter
    def orientHitMedium(self, val): self.orientHitMedium.set(val)
    @property
    def recoverTime(self):  # type: ()->Float
        return Float(self._node.at("recoverTime"))
    @recoverTime.setter
    def recoverTime(self, val): self.recoverTime.set(val)
    @property
    def resistance(self):  # type: ()->Int
        return Int(self._node.at("resistance"))
    @resistance.setter
    def resistance(self, val): self.resistance.set(val)
    @property
    def stunTime(self):  # type: ()->Float
        return Float(self._node.at("stunTime"))
    @stunTime.setter
    def stunTime(self, val): self.stunTime.set(val)
    pass




