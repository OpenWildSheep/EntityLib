
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *


class sBoneInfluenceDataTemplate(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sBoneInfluenceDataTemplate"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(sBoneInfluenceDataTemplate.schema_name))
    @property
    def BoneName(self): return String(self._node.at("BoneName"))
    @BoneName.setter
    def BoneName(self, val): self.BoneName.set(val)
    @property
    def Influence(self): return Float(self._node.at("Influence"))
    @Influence.setter
    def Influence(self, val): self.Influence.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




