
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class sBoneInfluenceDataTemplate(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sBoneInfluenceDataTemplate"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sBoneInfluenceDataTemplate
        return sBoneInfluenceDataTemplate(entlib.load_node_file(sourcefile, entlib.get_schema(sBoneInfluenceDataTemplate.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sBoneInfluenceDataTemplate
        return sBoneInfluenceDataTemplate(entlib.make_node(sBoneInfluenceDataTemplate.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BoneName(self):  # type: ()->String
        return String(self._node.at("BoneName"))
    @BoneName.setter
    def BoneName(self, val): self.BoneName.set(val)
    @property
    def Influence(self):  # type: ()->Float
        return Float(self._node.at("Influence"))
    @Influence.setter
    def Influence(self, val): self.Influence.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




