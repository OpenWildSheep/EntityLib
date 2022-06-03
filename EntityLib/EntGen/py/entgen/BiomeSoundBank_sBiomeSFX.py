
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.BiomeSoundBank_sBiomeEnv import *

from EntityLibPy import Node

class BiomeSoundBank_sBiomeSFX(HelperObject):
    schema_name = "BiomeSoundBank::sBiomeSFX"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BiomeSoundBank_sBiomeSFX
        return BiomeSoundBank_sBiomeSFX(entlib.load_node_file(sourcefile, entlib.get_schema(BiomeSoundBank_sBiomeSFX.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BiomeSoundBank_sBiomeSFX
        return BiomeSoundBank_sBiomeSFX(entlib.make_node(BiomeSoundBank_sBiomeSFX.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Rtpc(self):  # type: ()->String
        return String(self._node.at("Rtpc"))
    @Rtpc.setter
    def Rtpc(self, val): self.Rtpc.set(val)
    @property
    def SFX(self):  # type: ()->String
        return String(self._node.at("SFX"))
    @SFX.setter
    def SFX(self, val): self.SFX.set(val)
    @property
    def Super(self):  # type: ()->BiomeSoundBank_sBiomeEnv
        return BiomeSoundBank_sBiomeEnv(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




