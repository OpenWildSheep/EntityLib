
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class BiomeSoundBank_sBiomeEnv(HelperObject):
    schema_name = "BiomeSoundBank::sBiomeEnv"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BiomeSoundBank_sBiomeEnv
        return BiomeSoundBank_sBiomeEnv(entlib.load_node_file(sourcefile, entlib.get_schema(BiomeSoundBank_sBiomeEnv.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BiomeSoundBank_sBiomeEnv
        return BiomeSoundBank_sBiomeEnv(entlib.make_node(BiomeSoundBank_sBiomeEnv.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Name(self):  # type: ()->String
        return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def Spread(self):  # type: ()->Float
        return Float(self._node.at("Spread"))
    @Spread.setter
    def Spread(self, val): self.Spread.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




