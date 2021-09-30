
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *


class sGameEffectTemplate(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sGameEffectTemplate"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(sGameEffectTemplate.schema_name))
    @property
    def BoneID(self): return Int(self._node.at("BoneID"))
    @BoneID.setter
    def BoneID(self, val): self.BoneID.set(val)
    @property
    def BoneName(self): return String(self._node.at("BoneName"))
    @BoneName.setter
    def BoneName(self, val): self.BoneName.set(val)
    @property
    def EffectName(self): return String(self._node.at("EffectName"))
    @EffectName.setter
    def EffectName(self, val): self.EffectName.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




