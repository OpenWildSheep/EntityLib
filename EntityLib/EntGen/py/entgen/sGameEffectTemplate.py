
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *

from EntityLibPy import Node

class sGameEffectTemplate(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sGameEffectTemplate"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sGameEffectTemplate
        return sGameEffectTemplate(entlib.load_node_file(sourcefile, entlib.get_schema(sGameEffectTemplate.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sGameEffectTemplate
        return sGameEffectTemplate(entlib.make_node(sGameEffectTemplate.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BoneID(self):  # type: ()->Int
        return Int(self._node.at("BoneID"))
    @BoneID.setter
    def BoneID(self, val): self.BoneID.set(val)
    @property
    def BoneName(self):  # type: ()->String
        return String(self._node.at("BoneName"))
    @BoneName.setter
    def BoneName(self, val): self.BoneName.set(val)
    @property
    def EffectName(self):  # type: ()->String
        return String(self._node.at("EffectName"))
    @EffectName.setter
    def EffectName(self, val): self.EffectName.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




