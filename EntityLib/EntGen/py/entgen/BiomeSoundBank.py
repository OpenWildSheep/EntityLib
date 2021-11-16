
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.BiomeSoundBank_sBiomeSFX import *
from entgen.BiomeSoundBank_sBiomeSound import *

from EntityLibPy import Node

class BiomeSoundBank(HelperObject):
    schema_name = "BiomeSoundBank"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BiomeSoundBank
        return BiomeSoundBank(entlib.load_node_file(sourcefile, entlib.get_schema(BiomeSoundBank.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BiomeSoundBank
        return BiomeSoundBank(entlib.make_node(BiomeSoundBank.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BiomeSFX(self):  # type: ()->Array[BiomeSoundBank_sBiomeSFX]
        return (lambda n: Array(BiomeSoundBank_sBiomeSFX, n))(self._node.at("BiomeSFX"))
    @property
    def BiomeSounds(self):  # type: ()->Array[BiomeSoundBank_sBiomeSound]
        return (lambda n: Array(BiomeSoundBank_sBiomeSound, n))(self._node.at("BiomeSounds"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




