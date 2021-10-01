
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.sBoneInfluenceDataTemplate import *

from EntityLibPy import Node

class sNodeBoneInfluenceDataTemplate(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sNodeBoneInfluenceDataTemplate"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sNodeBoneInfluenceDataTemplate
        return sNodeBoneInfluenceDataTemplate(entlib.load_node_file(sourcefile, entlib.get_schema(sNodeBoneInfluenceDataTemplate.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sNodeBoneInfluenceDataTemplate
        return sNodeBoneInfluenceDataTemplate(entlib.make_node(sNodeBoneInfluenceDataTemplate.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Data(self):  # type: ()->Array[sBoneInfluenceDataTemplate]
        return (lambda n: Array(sBoneInfluenceDataTemplate, n))(self._node.at("Data"))
    @property
    def NodeName(self):  # type: ()->String
        return String(self._node.at("NodeName"))
    @NodeName.setter
    def NodeName(self, val): self.NodeName.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




